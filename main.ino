#include <LiquidCrystal.h>

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
DeltaTracker deltaTracker;
StringRotater rotater(STATIONS[currentStationIndex], 600);

ForwardButton forwardButton(&rotater);
BackwardButton backwardButton(&rotater);

AutoLeds autoLeds(PHOTO_PIN, LEDS, sizeof(LEDS)/sizeof(int), 200);

void setup() {
  Serial.begin(9600);
  Serial.println();

  // set up the LCD's number of columns and rows:
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);

  pinMode(SPEED_POT_PIN, INPUT);
  deltaTracker.begin();
  autoLeds.begin();
  forwardButton.begin();
  backwardButton.begin();
}

void loop() {
  // call update functions
  deltaTracker.update();

  long deltaMs = deltaTracker.getDeltaMillis();

  forwardButton.update(deltaMs);
  backwardButton.update(deltaMs);
  rotater.update(deltaMs);
  autoLeds.update();

  // print on lcd
  lcd.setCursor(0, 0);
  lcd.print(stationHeader);

  lcd.setCursor(0, 1);
  lcd.print(rotater.getString());

  int speed = analogRead(SPEED_POT_PIN);
  speed = map(speed, 0, 1023, 0, 255);
  Serial.println(analogRead(PHOTO_PIN));
}