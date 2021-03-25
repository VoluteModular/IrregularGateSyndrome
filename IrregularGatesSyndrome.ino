/*
Irregular Gate Syndrome
Justin Ahrens

*/
const int inPin = 0; // Input pin
const int inhibitPin = 1; // Inhibit Pin
const int outPins[] = {3,4,5,6,7,8}; // Trigger and gate Output pins
const int dipPins[] = {13,12,11,10,9}; // Pins for jumpers to set options
const int potPins[] = {A0,A1,A2}; // Pins connected to the randomness pots.
bool dipState[] = {false, false, false, false, false}; //Set the starting state for the config jumpers
unsigned long pulseLength = 4; //Default pulse length
bool clockWait = false;    
bool randomEnd = false;      // This controls whether the ends of the gates will be random or a set length 
bool inhibit = false;        // If this is set then no gates/triggers will be output or all gates/triggers will be output
bool inhib_rand = false;
int randValue1 = 30;
int randValue2 = 30;
int randValue3 = 30;
int clockDiv1 = 2;
int clockDiv2 = 4;
int clockDiv3 = 8;
unsigned int clockCount = 0;

int mode = 1;
int cvINPin = 5;
int inhMode = 0;
const byte butPin = 2;


void setup() {
  pinMode(butPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(butPin), flashFast, CHANGE);  
  randomSeed(analogRead(0));
  pinMode(inPin, INPUT);
  pinMode(inhibitPin, INPUT);
  for (int i = 0; i < 6; i++){
    pinMode(outPins[i], OUTPUT);
    //digitalWrite(outPins[i], HIGH);
    //delay(200);
    //digitalWrite(outPins[i], LOW);
  }
  for (int i = 0; i <5 ; i++){
    pinMode(dipPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i <4 ; i++){
    pinMode(potPins[i], INPUT);
  }  
  checkDipPins();
  if (randomEnd) flashFast();
}

void loop() {
  if (mode == 0) randomGates();
  if (mode == 1) clockDivide();
  checkDipPins();
  checkInhibitPin();
  checkAnalogPins();
}
void checkMode(){
static bool lastModeState = false;
static unsigned long timeSinceLastChange = 0;
if (digitalRead(2)!= lastModeState) {
  
}
else {
  
}
  
  
}

void clockDivide() {
  
  unsigned long currentMillis = millis();
  static unsigned long lastMillis = 0;
  if (checkExternalClockStart()){
    clockWait = true;
    clockCount++;
    
    if ((clockCount % clockDiv1)==0) {
      if (!inhibit ) digitalWrite(outPins[0], HIGH);
    }
    /*randNumber = random(100);
    if (randNumber <= randValue2) {
      if (!inhibit ) digitalWrite(outPins[1], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue3) {
      if (!inhibit ) digitalWrite(outPins[2], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue1) {
      if (!inhibit) digitalWrite(outPins[3], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue2) {
      if (!inhibit) digitalWrite(outPins[4], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue3) {
      if (!inhibit) digitalWrite(outPins[5], HIGH);
    } */

    lastMillis = currentMillis;
    
  }
  else if (currentMillis - lastMillis >= pulseLength){
    digitalWrite(outPins[0], LOW);
    digitalWrite(outPins[1], LOW);
    digitalWrite(outPins[2], LOW);
  }
  
}

void randomGates(){
  unsigned long currentMillis = millis();
  static unsigned long lastMillis = 0;
  if (checkExternalClockStart()){
    clockWait = true;
    int randNumber = random(100);
    if (randNumber <= randValue1) {
      if (!inhibit ) digitalWrite(outPins[0], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue2) {
      if (!inhibit ) digitalWrite(outPins[1], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue3) {
      if (!inhibit ) digitalWrite(outPins[2], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue1) {
      if (!inhibit) digitalWrite(outPins[3], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue2) {
      if (!inhibit) digitalWrite(outPins[4], HIGH);
    }
    randNumber = random(100);
    if (randNumber <= randValue3) {
      if (!inhibit) digitalWrite(outPins[5], HIGH);
    } 

    lastMillis = currentMillis;
    
  }
  else if (currentMillis - lastMillis >= pulseLength){
    digitalWrite(outPins[0], LOW);
    digitalWrite(outPins[1], LOW);
    digitalWrite(outPins[2], LOW);
  }
  if ((digitalRead(inPin)==LOW) & clockWait) {
    clockWait = false;
    if (randomEnd) {
      int randNumber = random(100);
      if (randNumber <= 30) {
      digitalWrite(outPins[3], LOW);
      }
      randNumber = random(100);
      if (randNumber <= 30) {
      digitalWrite(outPins[4], LOW);
      }         
      randNumber = random(100);
      if (randNumber <= 30) {
      digitalWrite(outPins[5], LOW);
      }
    }else {
      digitalWrite(outPins[3], LOW);
      digitalWrite(outPins[4], LOW);
      digitalWrite(outPins[5], LOW);
         
    }
    
      
  }
}

boolean checkExternalClockStart(){        // check if we are at the beginning of a clock pulse
  static boolean lastClockInput = false;  //this variable holds the status of the last clock input
  boolean result = false;                 //this holds the result
  boolean clockInput;                     //this holds the input status
  clockInput = digitalRead(inPin);        //read the pin
  result = !lastClockInput && clockInput; // We trigger when input switches from LOW to HIGH
  lastClockInput = clockInput;            // set the last clock input
  return result;
}
boolean checkExternalClockEnd(){          // check if we are at the end of a clock pulse
  static boolean lastClockInput = true;
  boolean result = false;
  boolean clockInput;
  clockInput = digitalRead(inPin);
  result = !lastClockInput && clockInput; // We trigger when input switches from HIGH to LOW
  lastClockInput = clockInput;
  return result;
}

void checkDipPins() {   // This checks the status of the jumpers to set the variables
  for (int i = 0; i<5; i++){
    if (digitalRead(dipPins[i])== HIGH) dipState[i] = true;
    else dipState[i] = false;
  }
  if (dipState[0] == true) pulseLength = 150; // pin one sets the pulse length
  else pulseLength = 4;     
  randomEnd = dipState[1];    // pin two sets wether the end of the gates are random or 
  inhib_rand = dipState[2];   // pin three sets whether the 2nd input is inhibit or random CV no jumper = inhibit, jumper - random for t1/t3
}
void checkInhibitPin(){
  if (digitalRead(inhibitPin)== HIGH) inhibit=true;
  else inhibit = false;
  if (inhib_rand) inhibit=false;
}
void checkAnalogPins() {
    static int v0,v1,v2,v3;
    static int avg0,avg1,avg2,avg3;
    
    v0 = analogRead( potPins[0] );  // Read pot value from analog input 0
    avg0 += ( v0 - avg0 ) / 2;  // Smooth value cheaper than a cap
    v1 = analogRead( potPins[1] );
    avg1 += ( v1 - avg1 ) / 2;    
    v2 = analogRead( potPins[2] );
    avg2 += ( v2 - avg2 ) / 2;
    v3 = analogRead( A5 );
    avg3 += ( v3 - avg3 ) / 2;

    randValue1 = map(avg0, 0, 1023, 0, 100);
    randValue2 = map(avg1, 0, 1023, 0, 100);
    randValue3 = map(avg2, 0, 1023, 0, 100);
    /*if (inhib_rand == true) {
      randValue1 = map(avg3, 0, 1023, 0, 100);
      randValue2 = map(avg3, 0, 1023, 0, 100);
      randValue3 = map(avg3, 0, 1023, 0, 100);
    }*/
    
      
}
void flashFast() {
  digitalWrite(outPins[0],HIGH);
  delay(50);
  digitalWrite(outPins[0],LOW);
  delay(50);
  digitalWrite(outPins[0],HIGH);
  delay(50);
  digitalWrite(outPins[0],LOW);
  delay(50);
  digitalWrite(outPins[0],HIGH);
  delay(50);
  digitalWrite(outPins[0],LOW);
  delay(50);
  digitalWrite(outPins[0],HIGH);
  delay(50);
  digitalWrite(outPins[0],LOW);
  delay(50);
  
}
