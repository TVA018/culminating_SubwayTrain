const int
  REST = 1000,
  C = -9,
  Cs = -8,
  Db = -8,
  D = -7,
  Ds = -6,
  Eb = -6,
  E = -5,
  F = -4,
  Fs = -3,
  Gb = -3,
  G = -2,
  Gs = -1,
  Ab = -1,
  A = 0,
  As = 1,
  Bb = 1,
  B = 2;

const int BASE_FREQUENCY = 440;
const int BPM = 60;

// Durations are in milliseconds
const double WHOLE_NOTE = 60.0 / BPM * 1000 * 2;
const double DOTTED_WHOLE_NOTE = WHOLE_NOTE * 3 / 2;
const double HALF_NOTE = WHOLE_NOTE / 2;
const double DOTTED_HALF_NOTE = HALF_NOTE * 3 / 2;
const double QUARTER_NOTE = HALF_NOTE / 2;
const double DOTTED_QUARTER_NOTE = QUARTER_NOTE * 3 / 2;
const double EIGHTH_NOTE = QUARTER_NOTE / 2;
const double SIXTEENTH_NOTE = EIGHTH_NOTE / 2;

int getFrequencyHz(int note, int octave) {
  if (note == REST) return 0;

  double n = note + (octave - 4) * 12;

  Serial.println(round(pow(2, n / 12) * BASE_FREQUENCY));

  return round(pow(2, n / 12) * BASE_FREQUENCY);
}

const int SWAN_LAKE[] = {
  Fs, 5, HALF_NOTE,
  B, 4, EIGHTH_NOTE,
  Cs, 5, EIGHTH_NOTE,
  D, 5, EIGHTH_NOTE,
  E, 5, EIGHTH_NOTE,

  Fs, 5, DOTTED_QUARTER_NOTE,
  D, 5, EIGHTH_NOTE,
  Fs, 5, DOTTED_QUARTER_NOTE,
  D, 5, EIGHTH_NOTE,
  
  Fs, 5, DOTTED_QUARTER_NOTE,
  D, 5, EIGHTH_NOTE,

};

const int SWAN_SEQ_LENGTH = sizeof(SWAN_LAKE) / sizeof(int);
const int NUM_NOTES_SWAN = SWAN_SEQ_LENGTH / 3;