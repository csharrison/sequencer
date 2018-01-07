#ifndef SEQUENCE_GENERATOR_H_
#define SEQUENCE_GENERATOR_H_

class ToggleButton;

// The order the sequence is going in.
enum class Ordering {
  kRandom,
  kLeft,
  kRight
};

enum class DisabledStepPolicy {
  kSkip,
  kDoNotSkip,
};

class SequenceGenerator {
 public:

  SequenceGenerator(ToggleButton* enabled_steps, int total_steps);
  ~SequenceGenerator();

  // Returns the step index to play next, or -1 if nothing should be played.
  int Advance();
 
  void set_ordering(Ordering ordering) {
    current_ordering_ = ordering;
  }

  void set_disabled_step_policy(DisabledStepPolicy disabled_policy) {
    disabled_policy_ = disabled_policy;
  }

  int current_step() const { return current_step_; }
 private:
  int AdvanceOne();
  
  ToggleButton* enabled_steps_;
  // The step that is playing currently.
  int current_step_ = -1;
  int total_steps_;
  Ordering current_ordering_ = Ordering::kRight;
  DisabledStepPolicy disabled_policy_ = DisabledStepPolicy::kDoNotSkip;
};

#endif  // SEQUENCE_GENERATOR_H_
