#include<Stepper.h>

#define StepperAngle 2037
Stepper M28BYJ(StepperAngle, 11, 9, 10, 8);
#define trigPin1 4
#define echoPin1 5

#define trigPin2 3
#define echoPin2 2

#define trigPin3 6
#define echoPin3 7

void setup() {
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);
  Serial.begin(9600);
  M28BYJ.setSpeed(15);
}

void loop() {
  float duration1, distance1, volume1, duration2, distance2, volume2, duration3, distance3;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1*17/1000;
  volume1 = (30-distance1)/30*100;
  
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*17/1000;
  volume2 = (30-distance2)/30*100;
//  Serial.pr/intln(volume2);
  if (volume1<=100 && volume2<=100){
      //Serial.print(volume1); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
      Serial.println(); 
      if(volume1 <80 && volume2 <80){
        //Serial.print("80이하");
        //Serial.println(volume1); 
        delay(1000);
        //뚜껑제어 
        digitalWrite(trigPin3, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin3, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin3, LOW);
      
        duration3 = pulseIn(echoPin3, HIGH);
        distance3 = duration3*17/1000;
        Serial.print("뚜껑과의 거리 : ");
        Serial.println(distance3);
      }

      else if(volume1 >= 80 || volume2>=80){
        Serial.println("80이상");
        Serial.println(volume1); 
        Serial.println(volume2);
        M28BYJ.step(StepperAngle);
        delay(1000);
        M28BYJ.step(-StepperAngle);
        delay(1000);
      }
   }

}
