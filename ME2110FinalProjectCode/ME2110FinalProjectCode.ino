#include <myDuino.h>

myDuino robot(1);

int encCount = 0;
int encDir = 0;
unsigned long m1spd = 0;
unsigned long m2spd = 0;
unsigned long initTime = 0;
unsigned long stopTime = 0;
unsigned long currentTime = 0;
int banana = 0; 
int but2 = 0; 
int but3 = 0; 
int but4 = 0;
int done = 0;

int movingMotorPin = 1;
int liftMotorPin = 2;
int solenoidPin = 1;
int clawPneumaticPin = 2;
int liftPneumaticPin = 3;


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
    
    //Move the robot forward until it hits the center
    currentTime = millis();
    while(but2 != 1 && timeStamp() <= 10000 && banana == 1){
      but2 = robot.readButton(2);
      robot.moveMotor(movingMotorPin, 1, 255);
      //Open at 1 second
      if(timeStamp() >= 2000){
        robot.digital(solenoidPin, 1);
      }

      //Open claw at 2 seconds
      if(timeStamp() >= 3000){
        robot.digital(clawPneumaticPin,1);
      }
      currentTime = millis();
      robot.LED(1,1);
    }
    robot.moveMotor(movingMotorPin,1,0);
    robot.digital(solenoidPin,0)
    robot.digital(clawPneumaticPin,0);

    //Move slightly Back to avoid hitting Calutron
    if(banana == 1){
      robot.moveMotor(movingMotorPin,2,100);
      delay(200);
      robot.moveMotor(movingMotorPin,2,0);
    }

    //Lift nuke and Sit until 25 second mark
    currentTime = millis();
    while(timeStamp() <= 25000 && banana == 1){
      robot.LED(2,1);
      //raise for 6 seconds
      if(timeStamp() <= 16000){
        robot.moveMotor(liftMotorPin, 1, 255);
        robot.digital(liftPneumaticPin, 1);
      }
      else{
        robot.moveMotor(liftMotorPin, 1, 0);
      }
    }
    robot.digital(liftPneumaticPin, 0);

    //Drive backwards to Barbie Land and lower Scissor Lift
    while(timeStamp() <= 38000 && banana == 1){
      robot.LED(1,0);
      robot.moveMotor(movingMotorPin,2,255);
      robot.moveMotor(liftMotorPin, 2, 100);
    }
    robot.moveMotor(movingMotorPin,2,0);
    robot.moveMotor(liftMotorPin, 2, 100);



    robot.LED(2,0);
    done = 1;
    shutDown();
    delay(1000000);
  }
}

unsigned long timeStamp(){
  return millis() - initTime;
}

void shutDown(){
  robot.moveMotor(1,1,0);
  robot.moveMotor(2,1,0);
  robot.digital(1, 0);
  robot.digital(2, 0);
  robot.digital(3, 0);
  robot.digital(4, 0);
}
