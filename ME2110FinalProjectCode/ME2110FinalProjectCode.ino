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
int done = 0;

int movingMotorPin = 1;
int liftMotorPin = 2;
int solenoidPin = 1;
int clawPneumaticPin = 2;


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
  if(banana == 1 && done == 0){
    //Run Code
    initTime = millis();
    
    //Move the robot forward until it hits the center
    while(but2 != 1 || millis() <= initTime + 3000 || banana == 1){
      robot.moveMotor(movingMotorPin, 1, 255);
      //Open at 1 second
      if(millis() >= initTime + 1000){
        robot.digital(solenoidPin, 1);
      }

      //Open claw at 2 seconds
      if(millis() >= initTime + 2000){
        robot.digital(clawPneumaticPin,1);
      }
    }
    robot.moveMotor(movingMotorPin,1,0);
    robot.digital(solenoidPin,0)
    delay(10000);

    //Lift nuke

    //Drive backwards using IR sensor and button as fail safe





    done = 1;
  }
}
