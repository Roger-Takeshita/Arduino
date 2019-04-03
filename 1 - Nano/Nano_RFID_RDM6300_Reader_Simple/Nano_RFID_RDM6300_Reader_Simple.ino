//https://www.youtube.com/watch?v=52xt6LfU9tE

#include <SoftwareSerial.h>

SoftwareSerial Rfid = SoftwareSerial(2,3); // RX TX 

void setup() {
  Serial.begin(9600);
  Rfid.begin(9600);
}

void loop() {
  if(Rfid.available() > 0 ){
    while(Rfid.available() > 0 ){
      int r = Rfid.read();
      Serial.print(r);
      Serial.print(r, DEC);
      Serial.print(" ");
    }
    Serial.println();
  }
}
