#include <Wire.h>
#include <Adafruit_LTR390.h>
#include <Adafruit_BME280.h>

#define SDA_PIN 5  // GPIO 5 for SDA
#define SCL_PIN 6  // GPIO 6 for SCL

#define BME280_ADDRESS 0x76
#define LTR390_ADDRESS 0x53

Adafruit_BME280 bme;
Adafruit_LTR390 ltr;

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

  Serial.println("Both sensors initialized successfully.");
}

void printSensorReadings() {
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F; // in hPa
  float humidity = bme.readHumidity();

  ltr.setMode(LTR390_MODE_UVS);
  uint32_t uvs = ltr.readUVS();        // Raw UV reading

  uint32_t als = ltr.readALS();        // Raw ambient light reading

  Serial.println("BME280 Readings:");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println("LTR390 Readings:");
  Serial.print("Ambient Light (ALS): ");
  Serial.println(als);

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