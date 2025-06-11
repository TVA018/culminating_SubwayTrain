String repeatString(String baseString, int numberOfRepeats) {
  String repeatedString = "";

  for (int i = 0; i < numberOfRepeats; i++) {
    repeatedString = " " + repeatedString;
  }

  return repeatedString;
}

String padStrForLCD(String baseString) {
  int strLen = baseString.length();

  if (strLen >= LCD_WIDTH) {
    return String(baseString);
  }

  int padLength = (LCD_WIDTH - baseString.length()) / 2;  // the padding for one side

  return repeatString(" ", padLength) + baseString;
}

/** Pads a station name by a certain number of spaces for display on the LCD */
String padStationName(String stationName) {
  // default padding is 5
  // make sure the string length is a signed integer so that it doesn't overflow
  int padLength = max(LCD_WIDTH - int(stationName.length()), 5);

  return stationName + repeatString(" ", padLength);
}

String rotateStringRight(String baseString) {
  // return if the baseString is empty
  if (baseString.length() <= 0) return baseString;

  String lastLetter = String(baseString[baseString.length() - 1]);
  String remainingString = baseString.substring(0, baseString.length() - 1);

  return lastLetter + remainingString;
}

void printDirection() {
  Serial.print("Current Direction: ");
  Serial.println((motorDirection < 0) ? "Backward" : ((motorDirection > 0) ? "Forward" : "Neutral"));
}

void updateNumberOfPeople() {
  randomSeed(millis());  // randomize the seed based on the time elapsed
  int prevAmountOfPeople = numPeople;
  int decreaseAmount = random(0, numPeople + 1);
  int increaseAmount = random(0, trainCapacity - numPeople + decreaseAmount + 1);
  numPeople += increaseAmount - decreaseAmount;  // randomize the number of people

  Serial.println(String(decreaseAmount) + " people left the train.");
  Serial.println(String(increaseAmount) + " people got on the train.");
  Serial.println("Current # people on the train: " + String(numPeople));  // print the number of people on the train
  Serial.println();
}