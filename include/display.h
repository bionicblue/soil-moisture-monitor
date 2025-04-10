#ifndef DISPLAY_H
#define DISPLAY_H

struct DisplayData {
  float humidity;
  float temperatureF;
  int batteryPercent;
  int soilMoistureValue;
  bool soilDry;
  int soil_sensor_threshold;
};

void initDisplay();
void updateDisplay(DisplayData& display_data);

#endif