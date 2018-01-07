#include "toggle_button.h"

#include "Arduino.h"

ToggleButton::ToggleButton() {}

ToggleButton::~ToggleButton() {}

void ToggleButton::ReadFromPin(int pin) {
  bool pressed = digitalRead(pin) == HIGH;
  if (pressed && !currently_pressed_) {
    on_ = !on_;
  }
  currently_pressed_ = pressed;
}

