# Jetson Fire Detection Module

This folder contains the code for running fire detection on a Jetson Nano using video streamed from an ESP32 camera module. The Jetson Nano uses an Ultralytics YOLO model to detect fire in real time and POSTs the inference results back to the ESP32.

## Contents
- `main.py` — Main entry point for running fire detection and handling ESP32 discovery
- `fire_detection.py` — Contains the fire detection logic using Ultralytics YOLO and OpenCV
- `esp32_discovery.py` — Handles automatic discovery of the ESP32 camera using mDNS/zeroconf
- `requirements.txt` — Python dependencies for this module

## Requirements
- Python 3.8+
- Jetson Nano
- ESP32 camera module streaming video on the same network

### Python Dependencies
Install all dependencies with:
```sh
pip install -r requirements.txt
```

## Usage
1. Make sure your ESP32 camera is running and connected to the same network as the Jetson Nano.
2. Run the main script:
   ```sh
   python3 main.py [--display] [--ip <ESP32_IP>] [--weights <YOLO_WEIGHTS_PATH>]
   ```

### Arguments
- `--display` : (Optional) Show the video stream with fire detection results in a window.
- `--ip <ESP32_IP>` : (Optional) Manually specify the ESP32 camera's IP address. If not provided, the script will attempt to discover the ESP32 automatically using mDNS.
- `--weights <YOLO_WEIGHTS_PATH>` : (Optional) Path to the Ultralytics YOLO weights file. Defaults to `best.pt` in this folder if not specified.

**Examples:**
- Auto-discover ESP32 and display inference output:
  ```sh
  python3 main.py --display
  ```
- Specify ESP32 IP manually:
  ```sh
  python3 main.py --ip 192.168.x.x
  ```
- Use a custom YOLO weights file:
  ```sh
  python3 main.py --weights yolo11n.pt
  ```