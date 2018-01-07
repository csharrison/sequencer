#include "scale_generator.h"

// static
int ScaleGenerator::GetNote(int pot_value, Scale scale, float* pitch_bend) {
  int chromatic_value = GetChromaticNote(pot_value);
  switch(scale) {
    case Scale::kLinear:
      return GetLinearNote(pot_value, pitch_bend);
    case Scale::kChromatic:
      return chromatic_value;
    case Scale::kMajor: {
      int scale_steps[7] = {2, 2, 1, 2, 2, 2, 1};
      return GetScaleValue(chromatic_value, scale_steps, 7);
    }
    case Scale::kMinor: {
      int scale_steps[7] = {2, 1, 2, 2, 1, 2, 2};
      return GetScaleValue(chromatic_value, scale_steps, 7);
    }
  };
  return 0;
}

// static
int ScaleGenerator::GetLinearNote(int pot_value, float* pitch_bend) {
  // The root will be rounded down due to integer division.
  int root = pot_value / 16;
  int remainder = pot_value % 16;
  *pitch_bend = .5 * ((float) remainder) / 16.0;
  return root;
}

// static
int ScaleGenerator::GetChromaticNote(int pot_value) {
  // Return a value < 64.
  return pot_value / 16;
}

// static
int ScaleGenerator::GetScaleValue(int chromatic_value,
                                  int* scale_steps,
                                  int scale_length) {
  // Find the root value below |chromatic_value|.
  int root = 0;
  while (root + 12 < chromatic_value) {
    root += 12;
  }
  
  int note = root;
  for (int i = 0 ; i < scale_length ; i++) {
     int next_note = note + scale_steps[i];
     if (next_note > chromatic_value) {
       break;
     }
     note = next_note;    
  }
  return note;
}
