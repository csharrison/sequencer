#include "sequence_generator.h"

#include "Arduino.h"
#include "scale_generator.h"
#include "toggle_button.h"


SequenceGenerator::SequenceGenerator(ToggleButton* enabled_steps, int total_steps)
 : enabled_steps_(enabled_steps), total_steps_(total_steps) {}

SequenceGenerator::~SequenceGenerator() {}

int SequenceGenerator::Advance() {
  for (int i = 0; i < total_steps_; i++) {
    int step_index = AdvanceOne();
    if (enabled_steps_[step_index].on())
      return step_index;
    switch (disabled_policy_) {
      case DisabledStepPolicy::kSkip:
        continue;
      case DisabledStepPolicy::kDoNotSkip:
        return -1;
    }
  }
  return -1;
}

int SequenceGenerator::AdvanceOne() {
  int next_step = current_step_;
  switch (current_ordering_) {
    case Ordering::kRandom:
      next_step = random(total_steps_);
      break;
    case Ordering::kLeft:
      next_step--;
      break;
    case Ordering::kRight:
      next_step++;
      break;
  };
  if (next_step >= total_steps_)
    next_step = 0;
    
  if (next_step < 0)
    next_step = total_steps_ - 1;

  current_step_ = next_step;
  return next_step;
}

