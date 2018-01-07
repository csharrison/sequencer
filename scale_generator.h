#ifndef SCALE_GENERATOR_H_
#define SCALE_GENERATOR_H_

enum class Scale {
  kLinear, // Not implemented yet.
  kChromatic,
  kMajor,
  kMinor
};

// This class returns values in midi note numbers
// 0 = C0
// It assumes the key of C. Transposing will be done later in the chain.
class ScaleGenerator {
 public:
  // |pot_value| will be 0-1023. Return value will be a midi note value (0-127).
  // TODO(csharrison): Implement the linear scale using pitch bend?
  static int GetNote(int pot_value, Scale scale);
 
 private:
  static int GetChromaticNote(int pot_value);
  static int GetScaleValue(int chromatic_value, int* scale_steps, int scale_length);
};

#endif  // SCALE_GENERATOR_H_
