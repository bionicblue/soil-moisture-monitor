#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <stdbool.h>

namespace display {

struct ScreenData {
  float humidity;
  float temperature_fahrenheit;
  int battery_percent;
  int soil_moisture_value;
  bool is_soil_dry;
  int soil_sensor_threshold;
};

class Manager {
 public:
  Manager();
  void init();
  void update(struct ScreenData& screen_data);

 private:
  Adafruit_SSD1306 display_;

  void humidity(struct ScreenData& screen_data);
  void temperature(struct ScreenData& screen_data);
  void soilMoisture(struct ScreenData& screen_data);
  void battery(struct ScreenData& screen_data);
};

}  // namespace display

#endif