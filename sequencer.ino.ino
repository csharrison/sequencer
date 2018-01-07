#include <MIDI.h>
#include "scale_generator.h"
#include "sequence_generator.h"
#include "step_clock.h"
#include "sequencer.h"
#include "toggle_button.h"

#define MAX_INPUT_PIN 3

// Created and binds the MIDI interface to the default hardware Serial port
// Should be less than 64.
int transpose = 24;
int duty_length = 400; // ms
int x_pots[MAX_INPUT_PIN + 1] = {0, 0, 0, 0};
bool x_enabled[4] = {true, true, true, true};
unsigned long start_ms = millis();
Sequencer x_sequencer(x_enabled, x_pots, 4 /* total_steps */, start_ms, 400);
int seq_speed = 200;
ToggleButton button(3);
void ReadInputs() {
  for (int i = 0; i <= MAX_INPUT_PIN; ++i) {
    x_pots[i] = analogRead(i);
  }
  button.ReadPin();
  x_enabled[0] = button.on();
  seq_speed = analogRead(5);
  x_sequencer.set_speed(seq_speed);
  transpose = analogRead(4) / 32;
}

void WriteLeds(int on_index, int off_index) {
  if (on_index != -1)
    digitalWrite(on_index + 8, HIGH);
  if (off_index != -1)
    digitalWrite(off_index + 8, LOW);

  digitalWrite(4, button.on() ? HIGH : LOW);
}

void setup() {
  Sequencer::Begin();
  for (int i = 0; i <= MAX_INPUT_PIN + 8; ++i) {
    pinMode(i, OUTPUT);
  }
}

char read_interval = 0;
Scale current_scale = Scale::kMinor;
SequenceGenerator sequence_generator(nullptr, MAX_INPUT_PIN + 1);
StepClock step_clock(millis(), 500);
int current_note = -1;



void loop() {
  if (read_interval++ == 0) {
    ReadInputs();
    read_interval = 0;
  }

  unsigned long current_ms = millis();

  int step_on = -1;
  int step_off = -1;
  int on_value = -1;
  x_sequencer.Tick(current_ms, &on_value, &step_on, &step_off);
  if (on_value != -1) {
    x_sequencer.Play(on_value, transpose, duty_length);
  }
  WriteLeds(step_on, step_off);
  

  /*
  if (step_clock.Tick(current_ms)) {  
    int step_index = sequence_generator.Advance();
    int output = transpose + ScaleGenerator::GetNote(x_pots[step_index], current_scale);
    WriteLeds(step_index);

    // 127 vel, ch 1.
    if (current_note != -1) {
      // MIDI.sendNoteOff(current_note, 127, 1);
    } else if (output != -1) {
      // MIDI.sendNoteOn(output, 127, 1);
    }
    current_note = output;
  }
  */
}

