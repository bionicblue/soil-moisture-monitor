#include <Arduino.h>

#include "battery.h"
#include "button.h"
#include "display_manager.h"
#include "led.h"
#include "sensors.h"

const uint32_t kSensorInterval = 2000;
const int kSerialBaudRate = 9600;

uint32_t last_sensor_read = 0;

display::Manager display_manager;

void processSensors() {
  float humidity = sensors::readHumidity();
  float temperature_fahrenheit = sensors::readTemperatureFahrenheit();
  int soil_moisture_value = sensors::readSoilMoisture();
  bool is_soil_dry = sensors::isSoilDry(soil_moisture_value);
  int soil_sensor_threshold = sensors::getSoilThreshold();
  int battery_percent = battery::getPercentage();

  display::ScreenData sensor_data = {humidity,    temperature_fahrenheit, battery_percent, soil_moisture_value,
                                     is_soil_dry, soil_sensor_threshold};

  if (!button::isPressed()) {
    is_soil_dry ? led::on() : led::off();
  }

  display_manager.update(sensor_data);
}

void readSensorsIfTime() {
  uint32_t now = millis();

  if (now - last_sensor_read < kSensorInterval) {
    return;
  }

  processSensors();

  last_sensor_read = now;
}

void setup() {
  Serial.begin(kSerialBaudRate);

  sensors::init();
  display_manager.init();
  button::init();
  led::init();
}

void loop() {
  button::handleEvent();
  readSensorsIfTime();
}