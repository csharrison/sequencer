#ifndef SEQUENCE_GENERATOR_H_
#define SEQUENCE_GENERATOR_H_

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

  SequenceGenerator(bool* enabled_steps, int total_steps);
  ~SequenceGenerator();

  // Returns the step index to play next, or -1 if nothing should be played.
  int Advance();
 
  void SetOrdering(Ordering ordering);
  void SetDisabledStepPolicy(DisabledStepPolicy disabled_policy);

  int current_step() { return current_step_; }
 private:
  int AdvanceOne();
  
  bool* enabled_steps_;
  // The step that is playing currently.
  int current_step_ = -1;
  int total_steps_;
  Ordering current_ordering_ = Ordering::kRight;
  DisabledStepPolicy disabled_policy_ = DisabledStepPolicy::kDoNotSkip;
};

#endif  // SEQUENCE_GENERATOR_H_
