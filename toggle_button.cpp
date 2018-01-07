#include "toggle_button.h"

#include <Arduino.h>

ToggleButton::ToggleButton(int pin):
  pin_(pin) {}

ToggleButton::~ToggleButton() {}

void ToggleButton::ReadPin() {
  bool pressed = digitalRead(pin_) == HIGH;
  if (pressed && !currently_pressed_) {
    on_ = !on_;
  }
  currently_pressed_ = pressed;
}

