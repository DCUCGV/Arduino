#include<Servo.h>
#include<SoftwareSerial.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

//BLE
SoftwareSerial Bluetooth(9,8);

//Stepp Motor
#define StepperAngle 8
AccelStepper stepper1(StepperAngle, 10, 12, 11, 13);
AccelStepper stepper2(StepperAngle, A2, A4, A3, A5);
MultiStepper steppers;

//Ultrasonic sensor
//1
#define trigPin1 2
#define echoPin1 3


//2
#define trigPin2 4
#define echoPin2 5


//3
#define trigPin3 7
#define echoPin3 6

#define servoPin1 A1
#define servoPin2 A0

//Servo Motor
Servo servo1, servo2;
//int angle = 0;
boolean isNear = false;
void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);

  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(0);
  servo2.write(0);
}

void loop() {
  //초음파센서 사용을 위한 변수 선언 
  float duration1, distance1, volume1, duration2, distance2, volume2, duration3, distance3;

  //ultra1, ultra2는 쓰레기통 내부 용량 측정
  //ultra1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1*17/1000;
  volume1 = (30-distance1)/30*100;
  
  //ultra2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*17/1000;
  volume2 = (30-distance2)/30*100;

  //ultra3 입구 거리 측정
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = ((34000*duration3)/1000000)/2;
  if(volume1 <80.0 && volume2 <80.0){
    //80 미만 일때 뚜껑제어(열림)
    //쓰레기통 입구의 20cm 이내에 있을 시 열림
    Serial.print("입구와의 거리 : ");
    Serial.println(distance3);
  
    if(distance3 <=20 ){
//      if(!isNear){
//        isNear = true;
      servo1.write(0);
      servo2.write(360);
      delay(6000);
//      }
    }
    else{
//      if(isNear){
//        isNear=false;
      servo1.write(90);
      servo2.write(90);
      delay(1000);     
//     }
    }
  }
  
  else if(volume1 >=80.0 && volume2 >=80.0){
//    servo1.detach();
//    servo2.detach();
    long positions[2];
    if(Bluetooth.available()){
        char cmd = Bluetooth.read();
        if(cmd == '1'){
          Serial.println("ok");
          positions[0] = 5200;
          positions[1] = -5200;
          steppers.moveTo(positions);
          steppers.runSpeedToPosition();
          delay(2000); 
           
          positions[0] = -1;
          positions[1] = 1;
          steppers.moveTo(positions);
          steppers.runSpeedToPosition();
          delay(3000);
        }
    }
    
  }
}
