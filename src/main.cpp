#include <Arduino.h>
#include "sensors.h"
#include "display.h"
#include "battery.h"
#include "led.h"
#include "sleep.h"
#include "button.h"

const unsigned long kSensorInterval = 2000;

unsigned long last_sensor_read = 0;

void processSensors() {
  float humidity = readHumidity();
  float temperatureF = readTemperatureF();
  int batteryPercent = getBatteryPercentage();
  int soilMoistureValue = readSoilMoisture();
  bool soilDry = isSoilDry(soilMoistureValue);
  int soil_sensor_threshold = getSoilSensorThreshold();

  DisplayData sensor_data = {
    humidity,
    temperatureF,
    batteryPercent,
    soilMoistureValue,
    soilDry,
    soil_sensor_threshold
  };

  if (!isButtonPressed()) {
    soilDry ? ledOn() : ledOff();
  }

  updateDisplay(sensor_data);
}

void readSensorsIfTime() {
  unsigned long now = millis();

  if (now - last_sensor_read < kSensorInterval) {
    return;
  }
  
  Serial.println("Reading sensors...");
  
  processSensors();

  last_sensor_read = now;
}

void setup() {
  Serial.begin(9600);
  initSensors();
  initDisplay();
  initButton();
  initLED();
}

void loop() {
  HandleButtonEvent();
  readSensorsIfTime();
}