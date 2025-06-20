#include "config.h"

extern bool infrared;

void setupSensors() {
  pinMode(IR_SENSOR_PIN, INPUT);
}

void getSensorReadings() {
  infrared = !digitalRead(IR_SENSOR_PIN);  // Pin goes high when there is no detection, low otherwise
}