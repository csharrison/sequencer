#ifndef TOGGLE_BUTTON_H_
#define TOGGLE_BUTTON_H_

class ToggleButton {
 public: 
  ToggleButton();
  ~ToggleButton();

  void ReadFromPin(int pin);
  bool on() { return on_; }
 private:
  bool on_ = true;
  bool currently_pressed_ = false;
};

#endif  // TOGGLE_BUTTON_H_
