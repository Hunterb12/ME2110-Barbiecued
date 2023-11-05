#include <myDuino.h>

myDuino robot(1);
int banana = 0; 

int done = false;

int movingMotorPin = 1;
int solenoidPin = 1;
int clawPneumaticPin = 2;



//Create Encoder Handler
void encHandler() {
  robot.doEncoder();
}

void setup() {
  //Attach handler to Encoder Channels
  //Initialize Serial Monitor
  Serial.begin(9600);

}



void loop() {
  // put your main code here, to run repeatedly:
  banana = robot.readButton(1);
  //if(banana == 1 && done == false){
    //Run Code
    robot.LED(1,1);
    //robot.digital(solenoidPin, 1);
    //delay(1000);
    //robot.digital(clawPneumaticPin, 1);
    //delay(1000);
    //robot.digital(solenoidPin, 0);
    //robot.digital(clawPneumaticPin, 0);
    //robot.LED(2,1);
    //delay(1000);
    robot.moveMotor(2,2,255);
    robot.moveMotor(1,2,255);
  //}
  Serial.println("Banana: " + String(banana));
}
