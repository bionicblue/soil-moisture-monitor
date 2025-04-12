#include "battery.h"

#include <Arduino.h>

#include "hardware_config.h"

namespace battery {

const float kMaxBatteryVoltage = 4.2;
const float kMinBatteryVoltage = 3.0;
const float kMaxADCValue = 4095.0;
const float kReferenceVoltage = 3.3;
const int kVoltageDivider = 2;  // Assuming a voltage divider with equal resistors
const int kMaxPercentage = 100;

int getPercentage() {
  int raw_adc = analogRead(hardwareconfig::kBatteryPin);
  
  double voltage = (static_cast<float>(raw_adc) / kMaxADCValue) * kReferenceVoltage * kVoltageDivider;

  int percentage =
      static_cast<int>((voltage - kMinBatteryVoltage) / (kMaxBatteryVoltage - kMinBatteryVoltage) * kMaxPercentage);
  
  if (percentage > kMaxPercentage) {
    percentage = kMaxPercentage;
  }
  if (percentage < 0) {
    percentage = 0;
  }

  return percentage;
};
}  // namespace battery