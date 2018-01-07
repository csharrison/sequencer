#include "sequencer.h"
#include "step_clock.h"
#include "toggle_button.h"

#define MAX_INPUT_PIN 3

// GLOBAL SETTINGS
unsigned long start_ms = millis();

// Should be less than 64.
int transpose = 24;
int duty_length = 400; // ms
bool function_button = false;
StepClock poll_clock(start_ms, 5 /* step_interval */);

// SEQUENCE
int x_pots[8];
int y_pots[8];
ToggleButton x_enabled[8];
ToggleButton y_enabled[8];

Sequencer x_sequencer(x_enabled, x_pots, 4 /* total_steps */, start_ms, 400);
Sequencer y_sequencer(y_enabled, y_pots, 4 /* total_steps */, start_ms, 400);

void ReadInputs() {
  for (int i = 0; i <= MAX_INPUT_PIN; ++i) {
    x_pots[i] = analogRead(i);
  }
  x_enabled[0].ReadFromPin(3);
  int seq_speed = analogRead(5);
  x_sequencer.set_speed(seq_speed);
  transpose = analogRead(4) / 32;
}

void WriteLeds(int on_index, int off_index) {
  if (on_index != -1)
    digitalWrite(on_index + 8, HIGH);
  if (off_index != -1)
    digitalWrite(off_index + 8, LOW);

  digitalWrite(4, x_enabled[0].on() ? HIGH : LOW);
}

void setup() {
  Sequencer::Begin();
  for (int i = 0; i <= MAX_INPUT_PIN + 8; ++i) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  unsigned long current_ms = millis();
  if (poll_clock.Tick(current_ms)) {
    ReadInputs();
  }

  int step_on = -1;
  int step_off = -1;
  int on_value = -1;
  x_sequencer.Tick(current_ms, &on_value, &step_on, &step_off);
  if (on_value != -1) {
    x_sequencer.Play(on_value, transpose, duty_length);
  }
  WriteLeds(step_on, step_off);
}

