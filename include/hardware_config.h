#ifndef CONFIG_H
#define CONFIG_H

#include <DHT.h>

namespace hardwareconfig {
// Digital Pins
const int kDhtPin = 4;
const int kLedPin = 5;
const int kButtonPin = 15;

// ADC Pins
const int kSoilSensorPin = 34;
const int kBatteryPin = 35;

// Hardware
constexpr const int kDhtType = DHT22;
}  // namespace hardwareconfig
#endif