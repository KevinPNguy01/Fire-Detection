import cv2
from ultralytics import YOLO
from PIL import Image
import threading
import requests

latest_frame = None
lock = threading.Lock()

def capture_thread(url):
    global latest_frame
    cap = cv2.VideoCapture(url)
    while True:
        ret, frame = cap.read()
        if ret:
            with lock:
                latest_frame = frame

def predict_video():
    """
    Runs the model on the given video source, outputting its predictions in real time.

    Parameters:
    src (str or int): Video source — stream URL, file path, or 0 for webcam.
    output_path (str): Optional path to save annotated video.
    """
    global latest_frame

    model = YOLO("best.pt")
    
    while True:
        with lock:
            frame = latest_frame.copy() if latest_frame is not None else None
            
        if frame is None:
            continue
            
        results = model.predict(frame)
        
        annotated = results[0].plot()
        cv2.imshow("Inference", annotated)
        
        if cv2.waitKey(1) == 27:
            break
        
    cv2.destroyAllWindows()


if __name__ == "__main__":
    ip = "192.168.88.85"
    url = f"http://{ip}/stream"
    requests.post(f"http://{ip}/status", json={"fire": 0.9, "smoke": 0.3})

    #threading.Thread(target=capture_thread, args=(url,), daemon=True).start()
    predict_video()
