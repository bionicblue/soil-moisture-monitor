#include "battery.h"
#include "hardware_config.h"
#include <Arduino.h>

#define MAX_BATTERY_VOLTAGE 4.2
#define MIN_BATTERY_VOLTAGE 3.0

int getBatteryPercentage() {
  int rawADC = analogRead(BATTERY_PIN);
  float voltage = (rawADC / 4095.0) * 3.3 * 2;

  int percentage = (int)((voltage - MIN_BATTERY_VOLTAGE) / (MAX_BATTERY_VOLTAGE - MIN_BATTERY_VOLTAGE) * 100);
  if (percentage > 100) percentage = 100;
  if (percentage < 0) percentage = 0;

  return percentage;
}