#include "sensors.h"

#include <DHT.h>

#include "hardware_config.h"

namespace sensors {

// Threshold for dry soil
const int kDefaultSoilSensorThreshold = 2500;

int soil_sensor_threshold = kDefaultSoilSensorThreshold;

DHT dht(hardwareconfig::kDhtPin, hardwareconfig::kDhtType);

void init() { dht.begin(); }

float readHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    return NAN;
  }
  return dht.readHumidity();
}

float readTemperatureFahrenheit() {
  const float kCelsiusToFahrenheitNumerator = 9.0;
  const float kCelsiusToFahrenheitDenominator = 5.0;
  const int kCelsiusToFahrenheitOffset = 32;
  float temperature_celcius = dht.readTemperature();
  if (isnan(temperature_celcius)) {
    return NAN;
  }
  return (temperature_celcius * kCelsiusToFahrenheitNumerator / kCelsiusToFahrenheitDenominator) +
         kCelsiusToFahrenheitOffset;
}

int readSoilMoisture() { return analogRead(hardwareconfig::kSoilSensorPin); }

bool isSoilDry(int soil_moisture_value) { return soil_moisture_value > soil_sensor_threshold; }

void calibrateSoilThreshold() { soil_sensor_threshold = readSoilMoisture(); }

int getSoilThreshold() { return soil_sensor_threshold; }
}  // namespace sensors