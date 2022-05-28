#include<Stepper.h>
#include<Servo.h>
#include<SoftwareSerial.h>

//BLE
SoftwareSerial Bluetooth(9,8);

//Stepp Motor
#define StepperAngle 2037
Stepper M28BYJ1(StepperAngle, 13, 11, 12, 10);
Stepper M28BYJ2(StepperAngle, A2, A4, A3, A5);

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
int angle = 0;

void setup() {
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(servoPin1,OUTPUT);
  pinMode(servoPin2,OUTPUT);
  Serial.begin(9600);
  Bluetooth.begin(9600);
  M28BYJ1.setSpeed(15);
  M28BYJ2.setSpeed(15);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
}

void loop() {
  if(Bluetooth.available()){
      char cmd = Bluetooth.read();
      
      if(cmd == '1'){
        Serial.println("ok");
        M28BYJ1.step(StepperAngle),M28BYJ2.step(StepperAngle);
        delay(1000);
    
        M28BYJ1.step(-StepperAngle);
        M28BYJ2.step(-StepperAngle);
        delay(1000);
      }
    }
  digitalWrite(servoPin1,LOW);
  delayMicroseconds(2);
  digitalWrite(servoPin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(servoPin2,LOW);
  delayMicroseconds(2);
  digitalWrite(servoPin2, HIGH);
  delayMicroseconds(10);

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
//  Serial.println(volume2);
//  Serial.println(volume1); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
//  Serial.println(volume2); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
////      Serial.println(); 
  if(volume1 <80 && volume2 <80){
    //Serial.print("80이하");
    //Serial.println(volume1); 
    //delay(1000);
    //80 미만 일때 뚜껑제어(열림) 
    digitalWrite(trigPin3, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);
  
    duration3 = pulseIn(echoPin3, HIGH);
    distance3 = duration3*17/1000;

    //쓰레기통 입구의 20cm 이내에 있을 시 열림
    if(distance3 <=20){
//      Serial.print("입구와의 거리 : ");
//      Serial.println(distance3);
      angle = 90;
      servo1.write(angle);
      servo2.write(angle);
      delay(2000);
    }
    //20cm 보다 멀리 있을 시 뚜껑 안열림
    else{
      angle=0;
      servo1.write(angle);
      servo2.write(angle);
    }
    
  }
//  if(volume1 >=80 || volume2 >=80){
////    Serial.println(volume1);
////    Serial.println(volume2);
    
//  }
}
