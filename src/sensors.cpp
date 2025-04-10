#include "sensors.h"
#include "hardware_config.h"
#include <DHT.h>

// Threshold for dry soil
int soil_sensor_threshold = 2500;

DHT dht(DHTPIN, DHTTYPE);

void initSensors() {
  dht.begin();
}

float readHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    return NAN;
  }
  return dht.readHumidity();
}

float readTemperatureF() {
  float temperatureC = dht.readTemperature();
  if (isnan(temperatureC)) {
    return NAN;
  }
  return (temperatureC * 9.0 / 5.0) + 32;
}

int readSoilMoisture() {
  return analogRead(SOIL_SENSOR_PIN);
}

bool isSoilDry(int soilMoistureValue) {
  return soilMoistureValue > soil_sensor_threshold;
}

void calibrateSoilSensorThreshold() {
  soil_sensor_threshold = readSoilMoisture();
}

int getSoilSensorThreshold() {
  return soil_sensor_threshold;
}