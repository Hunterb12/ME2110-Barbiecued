#include <myDuino.h>

myDuino robot(1);

int encCount = 0;
int encDir = 0;
unsigned long m1spd = 0;
unsigned long m2spd = 0;
unsigned long initTime = 0;
unsigned long stopTime = 0;
int banana = 0; 
int but2 = 0; 
int but3 = 0; 
int but4 = 0;

//Create Encoder Handler
void encHandler() {
  robot.doEncoder();
}

void setup() {
  //Attach handler to Encoder Channels
  attachInterrupt(digitalPinToInterrupt(2), encHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), encHandler, CHANGE);

  //Initialize Serial Monitor
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  banana = robot.readButton(1);
  if(banana == 1){
    //Run Code
  }
}
