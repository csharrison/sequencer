#ifndef TOGGLE_BUTTON_H_
#define TOGGLE_BUTTON_H_

class ToggleButton {
 public: 
  ToggleButton(int pin);
  ~ToggleButton();

  void ReadPin();
  bool on() { return on_; }
 private:
  int pin_;
  bool on_ = false;
  bool currently_pressed_ = false;
};

#endif  // TOGGLE_BUTTON_H_
