// Protocol
// DW13:1 -- Digital Write pin 13 HIGH
// returns 13:1
// DS13:0 -- Digital Status pin 13
// returns 13:1 (if the status is 1)
// AS14:0 -- Analog Status pin 14 (A0)
// returns 14:510 (if the status is 510)
String inputString = "";
String cmdString = "";
String pinString = "";
String valueString = "";
boolean stringComplete = false;
boolean inputState = false;

long previousMillis;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("serial:ready");
  inputString.reserve(10);
  pinString.reserve(10);
  valueString.reserve(10);

  //OUTPUTS
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(4, LOW);
  Serial.println("4:0");
  digitalWrite(7, LOW);
  Serial.println("7:0");
  digitalWrite(8, LOW);
  Serial.println("8:0");
  digitalWrite(9, LOW);
  Serial.println("9:0");
  digitalWrite(10, LOW);
  Serial.println("10:0");
  digitalWrite(11, LOW);
  Serial.println("11:0");
  digitalWrite(12, LOW);
  Serial.println("12:0");
  digitalWrite(13, LOW);
  Serial.println("13:0");
  Serial.println("actuators:initialized");
  //INPUTS
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  Serial.println("sensors:initialized");
}

void loop() {

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }

  parseCommand();
}

void finish() {
  while (true) {
    ;
    ;
  }
}

void parseCommand() {
  // print the string when a newline arrives:
  if (stringComplete) {
    inputString.trim();
    //Serial.println(inputString);
    int separatorIndex = inputString.indexOf(':');
    cmdString = inputString.substring(0, 2);
    pinString = inputString.substring(2, separatorIndex);
    valueString = inputString.substring(separatorIndex + 1);

    if (cmdString == "DW") {
      int pinNum = pinString.toInt();
      int value = valueString.toInt();
      digitalWrite(pinNum, value);
      Serial.print(pinString);
      Serial.print(":");
      Serial.println(valueString);
    }
    if (cmdString == "DS") {
      int pinNum = pinString.toInt();
      int value = digitalRead(pinNum);
      Serial.print(pinString);
      Serial.print(":");
      Serial.println(value);
    }
    if (cmdString == "AS") {
      int pinNum = pinString.toInt();
      int value = analogRead(pinNum);
      Serial.print(pinString);
      Serial.print(":");
      Serial.println(value);
    }
    // clear the strings
    inputString = "";
    cmdString = "";
    pinString = "";
    valueString = "";
    stringComplete = false;
  }
}
