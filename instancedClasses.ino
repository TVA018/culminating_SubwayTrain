// subclasses which acts as instances of the super class with overrided methods and properties
class ForwardButton: public ButtonManager {
public:
  ForwardButton() : ForwardButton(new StringRotater()) {
    Serial.println("WARNING, YOU SHOULD NOT BE CREATING THIS CLASS WITH THIS CONSTRUCTOR");
  }

  ForwardButton(StringRotater* rotater): ButtonManager(FORWARD_BUTTON_PIN, BUTTON_DEBOUNCE) {
    this->rotater = rotater;
  }
private:
  StringRotater* rotater;

  void onRelease() override {
    if(currentStationIndex >= (NUM_STATIONS - 1) && motorDirection == 0) return;

    motorDirection = min(motorDirection + 1, 1); // increase by 1, capped at 1
    printDirection();

    if(motorDirection == 0){
      // Just arrived at a new location, had to have been moving backwards
      currentStationIndex--;
      stationHeader = padStrForLCD("Currently At");
      tone(BUZZER_PIN, BEEP_FREQUENCY, BEEP_DURATION);
    } else {
      // Currently in motion
      // get next station
      stationHeader = padStrForLCD("Next Station");
      rotater->setString(STATIONS[currentStationIndex + motorDirection]);
    }
  }
};

class BackwardButton: public ButtonManager {
public:
  BackwardButton() : BackwardButton(new StringRotater()) {
    Serial.println("WARNING, YOU SHOULD NOT BE CREATING THIS CLASS WITH THIS CONSTRUCTOR");
  }

  BackwardButton(StringRotater* rotater): ButtonManager(BACKWARD_BUTTON_PIN, BUTTON_DEBOUNCE) {
    this->rotater = rotater;
  }
private:
  StringRotater* rotater;

  void onRelease() override {
    if(currentStationIndex <= 0 && motorDirection == 0) return;

    motorDirection = max(motorDirection - 1, -1); // decrease by 1, capped at -1
    printDirection();

    if(motorDirection == 0){
      // Just arrived at a new location, had to have been moving forwards
      currentStationIndex++;
      stationHeader = padStrForLCD("Currently At");
      tone(BUZZER_PIN, BEEP_FREQUENCY, BEEP_DURATION);
    } else {
      // Currently in motion
      // get next station
      stationHeader = padStrForLCD("Next Station");
      rotater->setString(STATIONS[currentStationIndex + motorDirection]);
    }
  }
};