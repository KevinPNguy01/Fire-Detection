#include <Wire.h>
#include <Adafruit_LTR390.h>
#include <Adafruit_BME280.h>
#include <Adafruit_TSL2591.h>

#define SDA_PIN 5  // GPIO 5 for SDA
#define SCL_PIN 6  // GPIO 6 for SCL

#define BME280_ADDRESS 0x76
#define LTR390_ADDRESS 0x53

Adafruit_BME280 bme;
Adafruit_LTR390 ltr;
Adafruit_TSL2591 tsl;

extern float infrared;
extern uint32_t uv;

void setupSensors() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!bme.begin(BME280_ADDRESS, &Wire)) {
    Serial.println("BME280 not found!");
    while (1);
  }
  
  if (!ltr.begin()) {
    Serial.println("LTR390 not found!");
    while (1);
  }

  if (!tsl.begin()) {
    Serial.println("TSL2561 not found!");
    while (1);
  }

  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_9);
  ltr.setResolution(LTR390_RESOLUTION_18BIT);

  Serial.println("Both sensors initialized successfully.");
}

void getSensorReadings() {
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  infrared = lum >> 16;
  uv = ltr.readUVS();
}

void printSensorReadings() {
  float infrared = tsl.getFullLuminosity();
  float pressure = bme.readPressure() / 100.0F; // in hPa
  float humidity = bme.readHumidity();

  uint32_t uvs = ltr.readUVS();        // Raw UV reading

  Serial.println("BME280 Readings:");
  Serial.print("Infrared: ");
  Serial.print(infrared);
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println("LTR390 Readings:");
  Serial.print("UVS Raw: ");
  Serial.println(uvs);

  Serial.println();
}

void scanI2C() {
  Wire.begin(SDA_PIN, SCL_PIN);

  byte error, address;
  int nDevices;
  Serial.println("Scanning I2C devices...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.print("Found ");
    Serial.print(nDevices, DEC);
    Serial.println(" I2C devices.");
  }
}