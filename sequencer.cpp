#include "Arduino.h"
#include "MIDI.h"
#include "sequencer.h"

// Creates and binds the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE()

// static
void Sequencer::Begin() {
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
}

Sequencer::Sequencer(ToggleButton* enabled_steps,
                     int* pots,
                     int total_steps,
                     int start_ms,
                     int initial_step_ms)
  : note_on_clock_(start_ms, initial_step_ms),
    note_off_clock_(start_ms, -1),
    sequence_generator_(enabled_steps, total_steps),
    pots_(pots) {}

Sequencer::~Sequencer() {}

void Sequencer::Tick(unsigned long current_ms, int* on_value, int* step_on, int* step_off) {
  int current_step = sequence_generator_.current_step();
  
  bool note_on = note_on_clock_.Tick(current_ms);
  bool note_off = note_off_clock_.Tick(current_ms);
  if (note_off) {
    MIDI.sendNoteOff(current_note_, 127, 1);
    current_note_ = -1;
    note_off_clock_.Reset();
  }
  if (note_on) {
    *step_on = sequence_generator_.Advance();
    if (*step_on != -1)
      *on_value = pots_[*step_on];
  }
  if (note_off || note_on) {
    if (current_step != *step_on)
      *step_off = current_step;
  }
}

void Sequencer::Play(int step_on_value, int transpose, int length_ms) {
  float pitch_bend = 0.0;
  int note = transpose + ScaleGenerator::GetNote(step_on_value, current_scale_, &pitch_bend);
  if (current_note_ != -1) {
    MIDI.sendNoteOff(current_note_, 127, 1);
  }
  current_note_ = note;
  if (pitch_bend != current_bend_) {
    current_bend_ = pitch_bend;
    MIDI.sendPitchBend(pitch_bend, 1);
  }
  MIDI.sendNoteOn(note, 127, 1);
  note_off_clock_ = StepClock(millis(), length_ms);
}
