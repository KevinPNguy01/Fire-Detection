#pragma once

// ===========================
// Enter your WiFi credentials
// ===========================
const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

const float FIRE_THRESHOLD = 0.35;   // Confidence threshold for YOLO fire detection
const int IR_SENSOR_PIN = 9;        // GPIO pin connected to infrared sensor