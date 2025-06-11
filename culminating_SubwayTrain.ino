// This file primarily sets up the global variables and necessary methods
enum StatusColors {
  STATIONARY_COLOR,
  MOVING_COLOR,
  ERROR_COLOR
};

// Declare functions but don't define its behaviour yet
String repeatString(String baseString, int numberOfRepeats);

String padStrForLCD(String baseString);

/** Pads a station name by a certain number of spaces for display on the LCD */
String padStationName(String stationName);


/** "rotates" a string to the right by shifting all characters to the right, and looping characters back to the start if they go past the end */
String rotateStringRight(String baseString);

/** Debugging */
void printDirection();

/** Randomly adds or remove people from the train */
void updateNumberOfPeople();

// PINS
const int RS = 2, EN = 3, D4 = 4, D5 = 5, D6 = 7, D7 = 9;
const int LEDS[] = { A0, A1 };
const int PHOTO_PIN = A3;
const int FORWARD_BUTTON_PIN = A4;
const int BACKWARD_BUTTON_PIN = A5;
const int RGB_RED = 11, RGB_GREEN = 10;
const int BUZZER_PIN = 12;

const int LCD_WIDTH = 16, LCD_HEIGHT = 2;

// Station names
const String STATIONS[] = {
  padStationName("Runnymede Station"),
  padStationName("High Park Station"),
  padStationName("Keele Station"),
  padStationName("Dundas West Station"),
  padStationName("Landsdowne Station"),
  padStationName("Dufferin Station"),
  padStationName("Ossington Station"),
  padStationName("Christie Station"),
  padStationName("Bathurst Station"),
  padStationName("Spadina Station"),
  padStationName("St George Station"),
  padStationName("Bay Station"),
  padStationName("Bloor-Yonge Station"),
};

const int NUM_STATIONS = sizeof(STATIONS) / sizeof(String);

int motorDirection = 0;  // -1 is backwards, 0 is none, and 1 is forward

String stationHeader = padStrForLCD("Currently At");
int currentStationIndex = 0;

const int BUTTON_DEBOUNCE = 10;

const int trainCapacity = 1000;  // the maximum amount of people possible on the train
int numPeople = 0;               // number of people on the train