void setupCameraWebServer();
void setupSensors();
void scanI2C();
void printSensorReadings();

void setup() {
  Serial.begin(115200);
  setupCameraWebServer();
  scanI2C();
  setupSensors();
}

void loop() {
  printSensorReadings();
  delay(500);
}
