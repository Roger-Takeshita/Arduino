//======================================================================VARS
  int btnReadInterval = 150;
  int btnAnalog = A6;
  int btnValue;
  int on = 0;
  unsigned long last = millis();

//======================================================================SETUP
  void setup() {
    Serial.begin(9600);
  }
//======================================================================LOOP
  void loop() {
    btnValue = analogRead(btnAnalog);
    if(btnValue>100){
      if (millis() - last > btnReadInterval){
        on = !on;
        Serial.println(on? "ON":"OFF");
        digitalWrite(13, on? HIGH:LOW);
        Serial.println(last);
        Serial.println(millis());
        Serial.println(millis()-last);
      }
      last = millis();
    }
  }
