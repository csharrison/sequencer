#include "step_clock.h"

StepClock::StepClock(unsigned long start_ms,
                     unsigned long step_interval)
  : previous_ms_(start_ms),
    step_interval_(step_interval) {}
    
StepClock::~StepClock() {}

bool StepClock::Tick(unsigned long current_ms) {
  if (step_interval_ == -1)
    return false;
  current_step_ += current_ms - previous_ms_;
  previous_ms_ = current_ms;
  if (current_step_ >= step_interval_) {
    current_step_ = 0;
    return true;
  }
  return false;
}

void StepClock::Reset() {
  step_interval_ = -1;
  current_step_ = 0u;
}

