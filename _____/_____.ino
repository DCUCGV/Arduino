int ulPin=9;   //초음파 SIG연결 핀
  
void setup(){
  Serial.begin(9600);   //컴퓨터화면에 data값을 확인할 수 있도록 시리얼 통신 설정
}
  
void loop(){
  pinMode(ulPin,OUTPUT);     //초음파센서를 출력으로 설정
  digitalWrite(ulPin, LOW);  // 신호를 끄고 (2마이크로 초동안)
  delayMicroseconds(2);
  digitalWrite(ulPin, HIGH); //초음파 신호를 보낸다(5마이크로 초동안)
  delayMicroseconds(5);
  digitalWrite(ulPin, LOW); // 신호를 끈다.
  
  
  
  
  
  pinMode(ulPin, INPUT);    // 초음파센서를 입력으로 설정
  
  long duration = pulseIn(ulPin,HIGH); 
  
                              // 초음파센서에 반사되어 돌아온 초음파가 측정될 시간을 저장(마이크로초 단위)
  
  long cm = mtocm(duration);  // cm거리 계산 함수
  long inch = mtoinch(duration);  //inch거리 계산 함수
  
  Serial.print(cm);
  Serial.print("cm  ");
  Serial.print(inch);
  Serial.print("inch ");
  Serial.println();
  
  delay(5);
}
  
long mtocm(long a){
return a/29/2;      //초음파는 1초에 340m이동한다. 즉 1000000마이크로 초에 34000cm를 이동한다.
  
                        //따라서 cm거리는 시간x속력으로 a는 왕복시간이므로 (a/2)x34000/1000000이다.
}
  
long mtoinch(long b){
return b/74/2;    // 1000000마이크로 초동안 대략 13386inch를 이동하므로
  
                      // inch거리는 시간x속력으로 b는 왕복시간이므로 (b/2)x13386/1000000이다.
}
