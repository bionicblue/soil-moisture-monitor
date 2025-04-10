#include <Arduino.h>
#include "button.h"
#include "hardware_config.h"
#include "led.h"
#include "sensors.h"

unsigned long button_pressed_at = 0;
const unsigned long kButtonHoldTime = 5000;

bool button_held = false;

void initButton() {
  pinMode(kButtonPin, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
}

void HandleButtonEvent() {
  if (digitalRead(kButtonPin) == LOW) {
    if (button_pressed_at == 0) {
      Serial.println("Start button hold");
      button_pressed_at = millis();  // Start timing
      ledOff();
    } else if (!button_held && millis() - button_pressed_at >= kButtonHoldTime) {
      button_held = true;
      OnButtonHeld();
    }
  } else {
    if (button_held) {
      Serial.println("Button released after hold");
    }
    button_pressed_at = 0;
    button_held = false;
  }
}

void OnButtonHeld() {
  Serial.println("Button held for 5 seconds");
  ledBlink(3, 100);
  calibrateSoilSensorThreshold();
}

bool isButtonPressed() {
  return button_pressed_at > 0;
}