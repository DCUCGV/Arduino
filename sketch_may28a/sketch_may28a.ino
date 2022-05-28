#include<SoftwareSerial.h>
SoftwareSerial Bluetooth(9,8);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooth.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Bluetooth.available()){
    //Serial.write(Bluetooth.read());
    char cmd = Bluetooth.read();
    if(cmd =='1'){
      Serial.println("ok");
    }
  }
  if(Serial.available()){
    Bluetooth.write(Serial.read());
  }
}
