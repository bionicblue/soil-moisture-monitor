#include "display.h"
#include "hardware_config.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define BUTTON_PIN 15

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }
}

void updateDisplay(DisplayData& display_data) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Display Humidity
  display.print("Humidity: ");
  if (isnan(display_data.humidity)) {
    display.print("Error");
  } else {
    display.print(display_data.humidity);
    display.println("%");
  }

  // Display Temperature
  display.print("Temperature: ");
  if (isnan(display_data.temperatureF)) {
    display.print("Error");
  } else {
    display.print(display_data.temperatureF);
    display.print(char(248)); // Degree symbol
    display.println("F");
  }

  // Display Soil Moisture
  display.print("Soil Moist: ");
  display.print(display_data.soilMoistureValue);
  display.println(" ADC");

  display.print("Threshold: ");
  display.print(display_data.soil_sensor_threshold);
  display.println(" ADC");

  display.print("Soil Dry: ");
  display.println(display_data.soilDry ? "Yes" : "No");

  // Draw Battery Icon at Bottom-Right
  int batteryX = SCREEN_WIDTH - 30; // X position for the battery icon
  int batteryY = SCREEN_HEIGHT - 10; // Y position for the battery icon
  int batteryWidth = 20; // Width of the battery icon
  int batteryHeight = 8; // Height of the battery icon

  // Draw the battery outline
  display.drawRect(batteryX, batteryY, batteryWidth, batteryHeight, SSD1306_WHITE);

  // Draw the battery "cap"
  display.fillRect(batteryX + batteryWidth, batteryY + 2, 2, batteryHeight - 4, SSD1306_WHITE);

  // Fill the battery level based on percentage
  int fillWidth = map(display_data.batteryPercent, 0, 100, 0, batteryWidth - 2); // Map percentage to battery width
  display.fillRect(batteryX + 1, batteryY + 1, fillWidth, batteryHeight - 2, SSD1306_WHITE);

  // Display Battery Percentage
  display.setCursor(batteryX - 20, batteryY); // Position to the left of the battery icon
  display.print(display_data.batteryPercent);
  display.print("%");

  // Update the display
  display.display();
}