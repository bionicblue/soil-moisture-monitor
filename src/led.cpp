#include "led.h"
#include <Arduino.h>

#define LED_PIN 5

void initLED() {
  pinMode(LED_PIN, OUTPUT);
}

void ledOn() {
  digitalWrite(LED_PIN, HIGH);
}

void ledOff() {
  digitalWrite(LED_PIN, LOW);
}

void ledBlink(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    ledOn();
    delay(delayTime);
    ledOff();
    delay(delayTime);
  }
}