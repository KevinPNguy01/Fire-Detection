
from esp32_discovery import find_esp32
from fire_detection import begin_fire_detection
import argparse
import ipaddress
from pathlib import Path

def main():
    parser = argparse.ArgumentParser(description="Run YOLO object detection on ESP32 camera stream.")
    parser.add_argument(
        "--ip",
        type=ipaddress.ip_address,
        help="ESP32 IPv4 address"
    )
    parser.add_argument(
        "--weights",
        type=str,
        help="Path to YOLO model weights file"
    )
    parser.add_argument(
        "--display",
        action="store_true",
        help="Display the annotated video frames and print output"
    )
    args = parser.parse_args()

    # Find the ESP32 device on the local network if no IP is provided
    ip = args.ip or find_esp32()
    if not ip:
        raise RuntimeError("ESP32 not found. Make sure it is connected to the network and broadcasting its service.")
    print(f"ESP32 found at {ip}")

    # Validate the weights file path
    weights = args.weights or str(Path(__file__).parent / "best.pt")
    try:
        weights = Path(weights).resolve(strict=True)
    except FileNotFoundError:
        raise RuntimeError(f"Model weights file not found: {weights}")
    
    begin_fire_detection(ip, weights, args.display)

if __name__ == "__main__":
    main()