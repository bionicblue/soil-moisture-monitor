#include <Adafruit_GFX.h>

#include "display_manager.h"
#include "hardware_config.h"

namespace display {

const int16_t kScreenWidth = 128;
const int16_t kScreenHeight = 64;
const int kOledReset = -1;

Manager::Manager() : display_(kScreenWidth, kScreenHeight, &Wire, kOledReset) {}

void Manager::init() {
  pinMode(hardwareconfig::kButtonPin, INPUT_PULLUP);

  const int kOled12CAddress = 0x3C;
  if (!display_.begin(SSD1306_SWITCHCAPVCC, kOled12CAddress)) {
    Serial.println("SSD1306 allocation failed");
    for (;;) {
    };
  }
}

void Manager::update(struct ScreenData& screen_data) {
  display_.clearDisplay();
  display_.setCursor(0, 0);
  display_.setTextSize(1);
  display_.setTextColor(SSD1306_WHITE);

  humidity(screen_data);
  temperature(screen_data);
  soilMoisture(screen_data);
  battery(screen_data);

  // Update the display
  display_.display();
}

void Manager::humidity(struct ScreenData& screen_data) {
  display_.print("Humidity: ");

  if (isnan(screen_data.humidity)) {
    display_.print("Error");
  } else {
    display_.print(screen_data.humidity);
    display_.println("%");
  }
}

void Manager::temperature(struct ScreenData& screen_data) {
  const int kDegreeSymbolChar = 248;

  display_.print("Temperature: ");

  if (isnan(screen_data.temperature_fahrenheit)) {
    display_.print("Error");
  } else {
    display_.print(screen_data.temperature_fahrenheit);
    display_.print(static_cast<char>(kDegreeSymbolChar));
    display_.println("F");
  }
}

void Manager::soilMoisture(struct ScreenData& screen_data) {
  display_.print("Soil Moist: ");
  display_.print(screen_data.soil_moisture_value);
  display_.println(" ADC");

  display_.print("Threshold: ");
  display_.print(screen_data.soil_sensor_threshold);
  display_.println(" ADC");

  display_.print("Soil Dry: ");
  display_.println(screen_data.is_soil_dry ? "Yes" : "No");
}

void Manager::battery(struct ScreenData& screen_data) {
  // Draw Battery Icon at Bottom-Right
  const int16_t kBatteryWidth = 20;
  const int16_t kBatteryHeight = 8;
  const int16_t kBatteryXOffset = 30;
  const int16_t kBatteryYOffset = 10;
  const int16_t kBatteryTextXOffset = 20;
  const int kFullBatteryPercent = 100;
  const int kEmptyBatteryPercent = 0;
  const int kEmptyBatteryWidth = 0;

  int16_t battery_x = kScreenWidth - kBatteryXOffset;
  int16_t battery_y = kScreenHeight - kBatteryYOffset;

  // Draw the battery outline
  display_.drawRect(battery_x, battery_y, kBatteryWidth, kBatteryHeight, SSD1306_WHITE);

  // Draw the battery "cap"
  int16_t rect_x = static_cast<int16_t>(battery_x + kBatteryWidth);
  int16_t rect_y = static_cast<int16_t>(battery_y + 2);
  int16_t rect_width = 2;
  int16_t rect_height = kBatteryHeight - 4;
  display_.fillRect(rect_x, rect_y, rect_width, rect_height, SSD1306_WHITE);

  // Fill the battery level based on percentage
  int16_t fill_width = static_cast<int16_t>(map(screen_data.battery_percent, kEmptyBatteryPercent, kFullBatteryPercent,
                                                kEmptyBatteryWidth,
                                                kBatteryWidth - 2));  // Map percentage to battery width

  rect_x = static_cast<int16_t>(battery_x + 1);
  rect_y = static_cast<int16_t>(battery_y + 1);
  rect_height = kBatteryHeight - 2;
  display_.fillRect(rect_x, rect_y, fill_width, rect_height, SSD1306_WHITE);

  // Display Battery Percentage
  int16_t cursor_x = static_cast<int16_t>(battery_x - kBatteryTextXOffset);
  display_.setCursor(cursor_x, battery_y);
  display_.print(screen_data.battery_percent);
  display_.print("%");
}
}  // namespace display