//======================================================================LIBRARY
  #include <SoftwareSerial.h>

//======================================================================VARS
  SoftwareSerial Rfid = SoftwareSerial(2,3);

//======================================================================SETUP
  void setup() {
    Serial.begin(9600);
    Rfid.begin(9600);
  }

//======================================================================LOOP
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
