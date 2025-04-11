#ifndef LED_H
#define LED_H

namespace led {
struct BlinkArgs {
  int times;
  int delay_time;
};

void init();
void on();
void off();
void blink(BlinkArgs args);
}  // namespace led

#endif