// subclasses which acts as instances of the super class with overrided methods and properties

/** Button to start moving forward */
class ForwardButton : public ButtonManager {
public:
  ForwardButton()
    : ForwardButton(new StringRotater(), new DoorSound(0, 0, 0)) {
    Serial.println("WARNING, YOU SHOULD NOT BE CREATING THIS CLASS WITH THIS CONSTRUCTOR");
  }

  ForwardButton(StringRotater* rotater, DoorSound* doorSound)
    : ButtonManager(FORWARD_BUTTON_PIN, BUTTON_DEBOUNCE) {
    this->rotater = rotater;
    this->doorSound = doorSound;
  }
private:
  StringRotater* rotater;
  DoorSound* doorSound;

  void onRelease() override {
    // prevent the train from moving past the end of the line
    if (currentStationIndex >= (NUM_STATIONS - 1) && motorDirection == 0) return;

    if (motorDirection == -1) {
      motorDirection = 0;
      // Just arrived at a new location, had to have been moving backwards
      currentStationIndex--;
      stationHeader = padStrForLCD("Currently At");
      doorSound->playOpening();
    } else if (motorDirection == 0) {
      // Currently in motion
      motorDirection = 1;
      // get next station
      stationHeader = padStrForLCD("Next Station");
      rotater->setString(STATIONS[currentStationIndex + motorDirection]);
      doorSound->playClosing();
    }
  }
};

/** Button to start moving backwards */
class BackwardButton : public ButtonManager {
public:
  BackwardButton()
    : BackwardButton(new StringRotater(), new DoorSound(0, 0, 0)) {
    Serial.println("WARNING, YOU SHOULD NOT BE CREATING THIS CLASS WITH THIS CONSTRUCTOR");
  }

  BackwardButton(StringRotater* rotater, DoorSound* doorSound)
    : ButtonManager(BACKWARD_BUTTON_PIN, BUTTON_DEBOUNCE) {
    this->rotater = rotater;
    this->doorSound = doorSound;
  }
private:
  StringRotater* rotater;
  DoorSound* doorSound;

  void onRelease() override {
    // prevent the train from moving past the end of the line
    if (currentStationIndex <= 0 && motorDirection == 0) return;

    if (motorDirection == 1) {
      motorDirection = 0;
      // Just arrived at a new location, had to have been moving forwards
      currentStationIndex++;
      stationHeader = padStrForLCD("Currently At");
      doorSound->playOpening();
    } else if (motorDirection == 0) {
      // Currently in motion
      motorDirection = -1;
      // get next station
      stationHeader = padStrForLCD("Next Station");
      rotater->setString(STATIONS[currentStationIndex + motorDirection]);
      doorSound->playClosing();
    }
  }
};