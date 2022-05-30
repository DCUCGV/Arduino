#include<Stepper.h>

#include<SoftwareSerial.h>
//BLE
#include <AccelStepper.h>
#include <MultiStepper.h>
#define StepperAngle 8
MultiStepper steppers;
SoftwareSerial Bluetooth(9,8);
AccelStepper stepper1(StepperAngle,10,12,11,13);
AccelStepper stepper2(StepperAngle, A2, A4, A3, A5);
//Stepper stepper1(StepperAngle,10,12,11,13);

int speedLeft = 500;
int speedRight = 500;
 
int leftWheelForeward = 1;
int leftWheelBackward = -1;
int rightWheelForeward = -1;
int rightWheelBackward = 1;//  if(stepper1.distanceToGo()==0){
//    stepper1.moveTo(-stepper1.currentPosition());
//  }
//  stepper1.run();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(9600);
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
//  stepper1.setAcceleration(100.0);
//  stepper1.setSpeed(1000);
//  stepper2.setAcceleration(100.0);
//  stepper2.setSpeed(1000);
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
}

void loop() {
  long positions[2];
//  stepper1.moveTo(-stepper1.currentPosition());
//  stepper2.moveTo(-stepper1.currentPosition());
//  stepper1.run();
//  stepper2.run(0;
//  stepper2.run();
  if(Bluetooth.available()){

    char cmd = Bluetooth.read();
    if(cmd == '1'){
      Serial.println("ok");
      positions[0] = 5200;
      positions[1] = 5200;
     
    //  steppers.setAcceleration(50.0);
    //  steppers.setSpeed(2000);
      steppers.moveTo(positions);
      steppers.runSpeedToPosition();
      delay(2000);  
      positions[0] = -1;
      positions[1] = -1;
    //  steppers.setAcceleration(50.0);
    //  steppers.setSpeed(2000);
      steppers.moveTo(positions);
      steppers.runSpeedToPosition();
      delay(3000);
      }
   }
//   stepper1.setAcceleration(50.0);
//   stepper1.setSpeed(2000);
//   stepper2.setAcceleration(50.0);
//   stepper2.setSpeed(2000);
//   stepper1.moveTo(2038);
//   stepper2.moveTo(2038);
//   stepper1.run();
//   stepper2.run(); 
//   
  
   
   
//  
//  stepper1.run();
}
