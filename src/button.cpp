#include "button.h"

#include <Arduino.h>

#include <cstdint>

#include "hardware_config.h"
#include "led.h"
#include "sensors.h"

namespace button {

int button_pressed_at = 0;
const int kButtonHoldTime = 5000;

bool button_held = false;

void init() {
  pinMode(hardwareconfig::kButtonPin, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
}

void handleEvent() {
  if (digitalRead(hardwareconfig::kButtonPin) == LOW) {
    if (button_pressed_at == 0) {
      button_pressed_at = millis();  // Start timing
      led::off();
    } else if (!button_held && millis() - button_pressed_at >= kButtonHoldTime) {
      button_held = true;
      onHold();
    }
  } else {
    button_pressed_at = 0;
    button_held = false;
  }
}

void onHold() {
  const int kBlinkCount = 3;
  const int kBlinkDelayMs = 100;
  struct led::BlinkArgs args = {kBlinkCount, kBlinkDelayMs};
  led::blink(args);
  sensors::calibrateSoilThreshold();
}

bool isPressed() { return button_pressed_at > 0; }
}  // namespace button