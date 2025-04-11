#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

namespace button {
void init();
void handleEvent();
void onHold();
bool isPressed();
}  // namespace button
#endif