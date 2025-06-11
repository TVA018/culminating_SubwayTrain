#include <LiquidCrystal.h>

// create objects
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
DeltaTracker deltaTracker;
StringRotater rotater(STATIONS[currentStationIndex], 600);

DoorSound doorSound(BUZZER_PIN, 1500, 800);
ForwardButton forwardButton(&rotater, &doorSound);
BackwardButton backwardButton(&rotater, &doorSound);

AutoLeds autoLeds(PHOTO_PIN, LEDS, sizeof(LEDS) / sizeof(int), 200);
StatusLight statusLight(RGB_RED, RGB_GREEN);

void setup() {
  // debugging purposes
  Serial.begin(9600);
  Serial.println();

  // begin status lights
  statusLight.begin();
  statusLight.setColor(STATIONARY_COLOR);  // start with an error color, will be changed if setup completes properly

  // set up the LCD's number of columns and rows:
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);

  // setup objects
  deltaTracker.begin();
  autoLeds.begin();
  forwardButton.begin();
  backwardButton.begin();
  doorSound.begin();

  // all checks completed
  statusLight.setColor(STATIONARY_COLOR);  // setup complete, go back to normal
}

void loop() {
  // call update functions
  deltaTracker.update();

  long deltaMs = deltaTracker.getDeltaMillis();

  forwardButton.update(deltaMs);
  backwardButton.update(deltaMs);
  rotater.update(deltaMs);
  doorSound.update(deltaMs);
  autoLeds.update();

  // print on lcd
  lcd.setCursor(0, 0);
  lcd.print(stationHeader);

  lcd.setCursor(0, 1);
  lcd.print(rotater.getString());

  // update status light
  if (motorDirection == 0) {  // stationary
    statusLight.setColor(STATIONARY_COLOR);
  } else {
    statusLight.setColor(MOVING_COLOR);
  }
}