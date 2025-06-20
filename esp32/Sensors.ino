#define INFRARED_PIN 9  // GPIO pin connected to IR sensor

extern bool infrared;

void setupSensors() {
  pinMode(INFRARED_PIN, INPUT);
}

void getSensorReadings() {
  infrared = !digitalRead(INFRARED_PIN);  // Pin goes high when there is no detection, low otherwise
}