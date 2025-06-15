const float FIRE_THRESHOLD = 0.5;
const float SMOKE_THRESHOLD = 0.5;
const float INFRARED_THRESHOLD = 50;
const uint32_t UV_THRESHOLD = 50;

void setupCameraWebServer();
void setupSensors();
void scanI2C();
void printSensorReadings();
void getSensorReadings();

float fire;
float smoke;
float infrared;
uint32_t uv;

/**
 * Future logic for what to do when fire is detected
 */
void fireDetected() {
  Serial.println("FIRE DETECTED!!!");
}

void setup() {
  Serial.begin(115200);
  setupCameraWebServer();
  scanI2C();
  setupSensors();
}

void loop() {
  getSensorReadings();

  Serial.println("\nSensors:");
  Serial.print("Fire: ");
  Serial.println(fire);
  Serial.print("Smoke: ");
  Serial.println(smoke);
  Serial.print("Infrared: ");
  Serial.println(infrared);
  Serial.print("UV: ");
  Serial.println(uv);

  if (fire > FIRE_THRESHOLD && smoke > SMOKE_THRESHOLD && infrared > INFRARED_THRESHOLD && uv > UV_THRESHOLD) {
    fireDetected();
  }
  delay(500);
}
