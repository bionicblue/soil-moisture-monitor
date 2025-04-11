#include "led.h"

#include <Arduino.h>

#include "hardware_config.h"

namespace led {

void init() { pinMode(hardwareconfig::kLedPin, OUTPUT); }

void on() { digitalWrite(hardwareconfig::kLedPin, HIGH); }

void off() { digitalWrite(hardwareconfig::kLedPin, LOW); }

void blink(BlinkArgs args) {
  for (int i = 0; i < args.times; i++) {
    on();
    // TODO(BionicBlue): Convert delay to a non-blocking version
    delay(args.delay_time);
    off();
    delay(args.delay_time);
  }
}
}  // namespace led