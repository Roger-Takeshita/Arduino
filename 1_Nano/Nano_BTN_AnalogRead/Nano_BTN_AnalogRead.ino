//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

//? About
//* Just a simple read analog port
//* Using a button to turn on/off digital port 13 within 150ms of interval
//* This might be useful when you run out of digital ports

//? Simulation
//* https://www.tinkercad.com/things/d5w57o408Xp

//!======================================================================VARS
   int btnReadInterval = 150;
   int btnAnalog = A5;
   int ledPin = 13;   //onboard LED Arduino Nano
   int on = 0;
   unsigned long last = millis();
//!======================================================================SETUP
   void setup() {
      Serial.begin(9600);
      pinMode(btnAnalog, INPUT);
      pinMode(ledPin, OUTPUT);
   }
//!======================================================================LOOP
   void loop() {
      if(analogRead(btnAnalog) > 100){
         if (millis() - last > btnReadInterval){
            on = !on;
            Serial.println(on? "ON":"OFF");
            digitalWrite(ledPin, on? HIGH:LOW);
            Serial.println(last);
            Serial.println(millis());
            Serial.println(millis()-last);
         }
      last = millis();
      }
   }