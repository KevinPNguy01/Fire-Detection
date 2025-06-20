#include <WiFi.h>
#include <ESPmDNS.h>
#include "config.h"

void setupCameraWebServer();
void setupSensors();
void getSensorReadings();

// Confidence level between 0-1 of whether there is fire/smoke
float fire;
float smoke;

// Whether infrared is detected
bool infrared;

// Future logic to handle fire detection
void fireDetected() {
  Serial.println("FIRE DETECTED!!!");
}

void setup() {
  Serial.begin(115200);
  setupCameraWebServer();
  setupSensors();
}

void loop() {
  getSensorReadings();

  Serial.println("\nIP Address:");
  Serial.println(WiFi.localIP());
  Serial.println("Sensors:");
  Serial.print("Fire: ");
  Serial.println(fire);
  Serial.print("Smoke: ");
  Serial.println(smoke);
  Serial.print("Infrared: ");
  Serial.println(infrared);

  // Check if fire is detected based on the threshold and infrared sensor
  if (fire > FIRE_THRESHOLD && infrared) {
    fireDetected();
  }

  delay(500);
}
