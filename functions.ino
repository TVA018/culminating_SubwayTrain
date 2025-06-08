String repeatString(String baseString, int numberOfRepeats){
  String repeatedString = "";

  for(int i = 0; i < numberOfRepeats; i++){
    repeatedString = " " + repeatedString;
  }

  return repeatedString;
}

String padStrForLCD(String baseString){
  int strLen = baseString.length();

  if(strLen >= LCD_WIDTH){
    return String(baseString);
  }

  int padLength = (LCD_WIDTH - baseString.length()) / 2; // the padding for one side

  return repeatString(" ", padLength) + baseString;
}

/** Pads a station name by a certain number of spaces for display on the LCD */
String padStationName(String stationName){
  // default padding is 5
  // make sure the string length is a signed integer so that it doesn't overflow
  int padLength = max(LCD_WIDTH - int(stationName.length()), 5);

  return stationName + repeatString(" ", padLength);
}

String rotateStringRight(String baseString){
  // "rotates" the string to the right by shifting all characters to the right, 
  // and looping characters back to the start if they go past the end

  // return if the baseString is empty
  if(baseString.length() <= 0) return baseString;

  String lastLetter = String(baseString[baseString.length() - 1]);
  String remainingString = baseString.substring(0, baseString.length() - 1);

  return lastLetter + remainingString;
}

void printDirection(){
  Serial.print("Current Direction: ");
  Serial.println((motorDirection < 0) ? 
    "Backward" : 
    ((motorDirection > 0) ? "Forward" : "Neutral"));
}