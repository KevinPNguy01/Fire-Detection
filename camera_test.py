import cv2
from ultralytics import YOLO
from PIL import Image
import threading
import requests
import time

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

def predict_video(ip):
    global latest_frame

    model = YOLO("best.pt")
    
    while True:
        time.sleep(0.5)
        with lock:
            frame = latest_frame.copy() if latest_frame is not None else None
            
        if frame is None:
            continue

            
        results = model.predict(frame)
        annotated = results[0].plot()

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

        print("start")

        requests.post(f"http://{ip}/status", json={"fire": fire_conf, "smoke": smoke_conf})
        print("end")

        cv2.imshow("Inference", annotated)
        if cv2.waitKey(1) == 27:
            break

    cv2.destroyAllWindows()

if __name__ == "__main__":
    ip = "192.168.110.85"
    url = f"http://{ip}:81/stream"

    threading.Thread(target=capture_thread, args=(url,), daemon=True).start()
    predict_video(ip)
