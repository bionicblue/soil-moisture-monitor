#ifndef SENSORS_H
#define SENSORS_H

void initSensors();
float readHumidity();
float readTemperatureF();
int readSoilMoisture();
bool isSoilDry(int soilMoistureValue);
void calibrateSoilSensorThreshold();
int getSoilSensorThreshold();

#endif