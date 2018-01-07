#ifndef STEP_CLOCK_H_
#define STEP_CLOCK_H_

class StepClock {
 public:
  StepClock(unsigned long start_ms, unsigned long step_interval);
  ~StepClock();
  
  // Returns true if a step should be taken.
  bool Tick(unsigned long current_ms);

  // Sets the step interval for the clock, in ms.
  void set_step_interval(unsigned long step_interval) {
    step_interval_ = step_interval;
  }

  void Reset();
  
 private:
  unsigned long previous_ms_;
  unsigned long step_interval_;
  unsigned long current_step_ = 0u;
};

#endif  // STEP_CLOCK_H_
