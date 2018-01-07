#ifndef SEQUENCER_H_
#define SEQUENCER_H_

#include "scale_generator.h"
#include "sequence_generator.h"
#include "step_clock.h"

class Sequencer {
 public:
  static void Begin();
  Sequencer(ToggleButton* enabled_steps,
            int* pots,
            int total_steps,
            int start_ms,
            int initial_step_ms);
  ~Sequencer();

  void Tick(unsigned long current_ms, int* on_value, int* step_on, int* step_off);

  void Play(int step_on_value, int transpose, int length_ms);

  void set_speed(int pot_speed) {
    note_on_clock_.set_step_interval(pot_speed);
  }
  
  void set_scale(Scale scale) {
    current_scale_ = scale;
  }

  SequenceGenerator& sequence_generator() {
    return sequence_generator_;
  }
  
 private:
  StepClock note_on_clock_;
  StepClock note_off_clock_;
  SequenceGenerator sequence_generator_;
  Scale current_scale_ = Scale::kChromatic;

  float current_bend_ = 0.0;
  int current_note_ = -1;
  int* pots_;
};

#endif  // SEQUENCER_H_
