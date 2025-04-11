#ifndef SENSORS_H
#define SENSORS_H

#include <stdbool.h>

namespace sensors {
void init();
float readHumidity();
float readTemperatureFahrenheit();
int readSoilMoisture();
bool isSoilDry(int soil_moisture_value);
void calibrateSoilThreshold();
int getSoilThreshold();
}  // namespace sensors

#endif