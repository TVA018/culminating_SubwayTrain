/** Class to help manage button inputs. Allows functions to be run on certain events such as when the button is released */
class ButtonManager {
public:
  ButtonManager(int PIN, int DEBOUNCE_MS) {
    this->PIN = PIN;
    this->DEBOUNCE_MS = DEBOUNCE_MS;
  }

  void begin() {
    pinMode(PIN, INPUT_PULLUP);
    rawPressState = digitalRead(PIN);
    pressState = rawPressState;
    timeSinceLastChangeMs = 0;
  }

  int getPin() {
    return PIN;
  }

  int getPressState() {
    return pressState;
  }

  void update(long deltaMs) {
    int previousPressState = pressState;
    updatePressState(deltaMs);
    int currentPressState = pressState;

    if (currentPressState == LOW) {
      // Check if the button was just pressed
      if (previousPressState == HIGH) {  // Was previously not pressed
        onPress();                       // call onPress() if it exists
      }

      whilePressed();
    } else {
      // Check if the button was just released
      if (previousPressState == LOW) {  // Was previously pressed
        onRelease();                    // call onRelease() if it exists
      }
    }
  }
private:
  int PIN;
  int DEBOUNCE_MS;
  int pressState;     // debounced press state, used for actual logic
  int rawPressState;  // what digitalRead() returns
  long timeSinceLastChangeMs;

  /**This function is called when the button is initially held down*/
  virtual void onPress(){};
  /**This function is called when the button is released*/
  virtual void onRelease(){};
  /**This function is continuously called as long as the button is held down*/
  virtual void whilePressed(){};

  // updates the press state
  void updatePressState(long deltaMs) {
    int currentPressState = digitalRead(PIN);

    timeSinceLastChangeMs += deltaMs;

    // if state reading changed
    if (currentPressState != rawPressState) {
      timeSinceLastChangeMs = 0;
      rawPressState = currentPressState;
    }

    // if the state change has stayed for longer than the debounce time
    if (timeSinceLastChangeMs >= DEBOUNCE_MS) {
      // the actual press state is likely what digitalRead() provides
      pressState = rawPressState;
    }
  }
};

/** Keeps track of how much time has passed since the last update/tick */
class DeltaTracker {
public:
  void begin() {
    prevMs = millis();
  }

  // updates the tracker
  void update() {
    long currentMs = millis();
    deltaMs = currentMs - prevMs;
    prevMs = currentMs;

    return deltaMs;
  }

  long getDeltaMillis() {
    return deltaMs;
  }
private:
  long prevMs;
  long deltaMs = 0;
};

/** Helper class to rotate a line/row on the LCD */
class StringRotater {
public:
  StringRotater()
    : StringRotater("Placeholder", 500) {}

  /** timeoutMs is the duration between rotations in milliseconds */
  StringRotater(String startingString, long timeoutMs) {
    this->currentString = startingString;
    this->timeoutMs = timeoutMs;
  }

  void update(long deltaMs) {
    timeSinceLastRotationMs += deltaMs;

    // time to update
    if (timeSinceLastRotationMs >= timeoutMs) {
      timeSinceLastRotationMs -= timeoutMs;

      currentString = rotateStringRight(currentString);
    }
  }

  // return a copy of the string to prevent the user from modifying it
  String getString() {
    return String(currentString);
  }

  void setString(String newString) {
    currentString = newString;
    timeSinceLastRotationMs = 0;
  }
private:
  String currentString;
  long timeoutMs;
  long timeSinceLastRotationMs = 0;
};

/** Unused */
// class MotorController {
// public:
//   /** The forwardpin and backwardPin can be any digital pin, while the speedPin must be a PWM pin */
//   MotorController(int forwardPin, int backwardPin, int speedPin){
//     FORWARD_PIN = forwardPin;
//     BACKWARD_PIN = backwardPin;
//     SPEED_PIN = speedPin;
//   }

//   void begin(){
//     pinMode(FORWARD_PIN, OUTPUT);
//     pinMode(BACKWARD_PIN, OUTPUT);
//     pinMode(SPEED_PIN, OUTPUT);
//   }

//   /** -1 = Backward, 0 = Neutral, 1 = Forward */
//   void setDirection(int direction){
//     digitalWrite(FORWARD_PIN, max(direction, 0));
//     digitalWrite(BACKWARD_PIN, max(-direction, 0));
//   }

//   /** speed range is 0-255 (inclusive) */
//   void setSpeed(int speed){
//     // digitalWrite(SPEED_PIN, HIGH);
//     analogWrite(SPEED_PIN, speed);
//   }
// private:
//   int FORWARD_PIN;
//   int BACKWARD_PIN;
//   int SPEED_PIN;
// };

// Turn on and off leds based on a photoresistor
class AutoLeds {
public:
  /** The minBrightness is the minimum brightness required for the LEDs to turn on */
  AutoLeds(int photoPin, int* leds, int numLeds, int minBrightness) {
    this->photoPin = photoPin;
    this->leds = leds;
    this->numLeds = numLeds;
    this->minBrightness = minBrightness;
  }

  void begin() {
    pinMode(photoPin, INPUT);

    for (int i = 0; i < numLeds; i++) {
      pinMode(leds[i], OUTPUT);
    }
  }

  void update() {
    int photoReading = analogRead(photoPin);

    // turn on leds if it is dark enough
    if (photoReading <= minBrightness) {
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(leds[i], HIGH);
      }
    } else {
      for (int i = 0; i < numLeds; i++) {
        digitalWrite(leds[i], LOW);
      }
    }
  }
private:
  int photoPin;
  int* leds;
  int numLeds;
  int minBrightness;
};

/** The RGB light responsible for showing the current status of the subway train */
class StatusLight {
public:
  StatusLight(int RED_PIN, int GREEN_PIN) {
    redPin = RED_PIN;
    greenPin = GREEN_PIN;
  }

  void begin() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
  }

  /** Use the class's colours as the parameter to this function */
  void setColor(int colorCode) {
    if (colorCode == STATIONARY_COLOR) {
      // Pure green
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
    } else if (colorCode == MOVING_COLOR) {
      // Yellow
      analogWrite(redPin, 255);
      analogWrite(greenPin, 100);
    } else {
      // Error, pure red
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, LOW);
    }
  }
private:
  int redPin;
  int greenPin;
};

/** Simulates the beeping sound of a door opening or closing */
class DoorSound {
public:
  long durationMs;

  DoorSound(int buzzerPin, long durationMs, int highFrequency) {
    PIN = buzzerPin;
    this->durationMs = durationMs;
    this->highFrequency = highFrequency;
    this->lowFrequency = pow(2.0, -1.0 / 3) * highFrequency;
  }

  void begin() {
    pinMode(PIN, OUTPUT);
  }

  void update(long deltaMs) {
    if (!isPlaying) return;  // don't play sound

    timeElapsed += deltaMs;

    if (timeElapsed <= durationMs) {
      // play low sound if time elapsed is in the second half of the duration
      // and the door is opening
      int targetFrequency = (!isOpenSound && (timeElapsed > durationMs / 2)) ? lowFrequency : highFrequency;
      tone(PIN, targetFrequency);
    } else {
      noTone(PIN);
      isPlaying = false;
    }
  }

  /** Opening sound */
  void playOpening() {
    timeElapsed = 0;
    isPlaying = true;
    isOpenSound = true;
  }

  /** Closing sound */
  void playClosing() {
    timeElapsed = 0;
    isPlaying = true;
    isOpenSound = false;
  }
private:
  int highFrequency;
  int lowFrequency;
  bool isOpenSound = false;  // is the sound of a door opening
  bool isPlaying = false;
  int PIN;
  long timeElapsed;  // since the beep started
};