//==========================================
//https://github.com/Roger-Takeshita/Arduino
//==========================================

//======================================================================LIBRARY
  #include <SoftwareSerial.h>

//======================================================================VARS
  SoftwareSerial RFID = SoftwareSerial(2,3); // RX TX 
  int data[14];
 
//======================================================================SETUP
void setup(){
  RFID.begin(9600);    
  Serial.begin(9600);  
}
 
//======================================================================LOOP
void loop() {
  delay(200);
  if (RFID.available() > 0) {
    for (int i = 0; i<14;i++) {
      data[i] = RFID.read();
    }
    for (int i = 1; i<11; i++) {
      char d = data[i];
      Serial.print(d, DEC);
    }
    delay(2000);
    RFID.flush();
    Serial.println();
  }
}
