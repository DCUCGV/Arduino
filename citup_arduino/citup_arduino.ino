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


#define servoPin A0

Servo servo;
void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);

  stepper1.setMaxSpeed(850);
  stepper2.setMaxSpeed(850);
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  
  servo.attach(servoPin);
  servo.write(0);
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
  distance1 = ((34000*duration1)/1000000)/2;
  volume1 = (16-distance1)/16*100;
  
  //ultra2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
   
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 =((34000*duration2)/1000000)/2;
  volume2 = (16-distance2)/16*100;

  //ultra3 입구 거리 측정
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = ((34000*duration3)/1000000)/2;
//  Serial.print("volume1 : ");
//  Serial.println(volume1);
//  Serial.print("volume2 : ");
//  Serial.println(volume2);
//  float volume = (volume1+volume2)/2.0;
  Serial.println(volume1);
  
  delay(500);
  if(volume1 <80.0 || volume2 <80.0){
    //80 미만 일때 뚜껑제어(열림)
    //쓰레기통 입구의 20cm 이내에 있을 시 열림
//    Serial.print("입구와의 거리 : ");
//    Serial.println(distance3);
  
    if(distance3 <=60 ){
      servo.write(110);
      delay(3000);
    }
    else{
      servo.write(0);
      delay(1000);     
    }
  }

  
//  else if(volume1 >=30.0 || volume2 >=30.0){
////    Serial.print("volume1 : ");
//    Serial.println(volume1);
//    Serial.print("volume2 : ");
//    Serial.println(volume2);
//    servo1.detach();
//    servo2.detach();
    long positions[2];
    if(Bluetooth.available()){
        char cmd = Bluetooth.read();
        if(cmd == '1'){
//          Serial.println("ok");
          positions[0] = 3000;
          positions[1] = -3000;
          steppers.moveTo(positions);
          steppers.runSpeedToPosition();
          delay(2000); 
           
          positions[0] = 1;
          positions[1] = -1;
          steppers.moveTo(positions);
          steppers.runSpeedToPosition();
          delay(3000);
        }
    }
    
//  }
}
