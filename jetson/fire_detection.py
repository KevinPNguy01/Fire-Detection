from ultralytics import YOLO
import threading
import requests
import time
import cv2

latest_frame = None     # Global variable to hold the latest frame captured from the ESP32 camera
lock = threading.Lock() # Thread lock for thread-safe access to latest_frame

def capture_thread(url: str, delay: float = 0.5) -> None:
    """
    Continuously captures frames from the ESP32 camera stream and updates the latest_frame variable.

    Args:
        url (str): The URL of the ESP32 camera stream.
        delay (float): Delay between frame captures in seconds.
    """

    global latest_frame
    cap = cv2.VideoCapture(url)
    while True:
        ret, frame = cap.read()
        if not ret:
            time.sleep(delay)
            continue
        with lock:
            latest_frame = frame

def begin_fire_detection(ip: str, weights_path: str, display: bool) -> None:
    """
    Captures frames from the ESP32 camera, runs object detection using YOLO,
    and posts the results back to the ESP32 device.

    Args:
        ip (str): The IP address of the ESP32 device.
        weights_path (str): Path to the YOLO model weights file.
        display (bool): Whether to display the annotated video frames and print output.
    """

    print(f"Starting fire detection on ESP32 at {ip}...")
    model = YOLO(weights_path)

    # Start a new thread to capture video frames from the ESP32 camera stream
    camera_stream_url = f"http://{ip}:81/stream"
    threading.Thread(target=capture_thread, args=(camera_stream_url,), daemon=True).start()
    
    while True:
        time.sleep(0.5)

        # Copy the latest frame from the camera stream with thread safety
        with lock:
            if latest_frame is None:
                continue
            frame = latest_frame.copy()

        results = model.predict(frame, verbose=display)

        # Extract the highest confidence scores for fire and smoke
        fire_conf = 0.0
        smoke_conf = 0.0
        for r in results[0].boxes:
            cls = int(r.cls[0])
            conf = float(r.conf[0])
            label = model.names[cls].lower()
            if label == "fire":
                fire_conf = max(fire_conf, conf)
            elif label == "smoke":
                smoke_conf = max(smoke_conf, conf)

        # Post inference results to ESP32
        requests.post(f"http://{ip}/status", json={"fire": fire_conf, "smoke": smoke_conf})

        # Display the results with annotations
        if display:
            annotated = results[0].plot()
            cv2.imshow("Inference", annotated)

        # Exit on ESC key
        if cv2.waitKey(1) == 27:
            break

    cv2.destroyAllWindows()