//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

//? About
//* Clean sketch using Blynk Library and two physic push buttons to turn on/off a led.

//? Blynk Setup
//* Create a new project
//* On your new project, go to setting (first button on the left of the play button)
//* Copy "auth token" this is the authentication key that we are going to use in our project
//* After you finish the layout of your project, click on the play button.lick on the play button.

//? Scketch Config
//* Change the auth ("blink-authentication-key")
//* Change the ssid ("your-wifi-name")
//* Change the pass ("your-wifi-password")
//* They are all strings, so don't forget the double quotes

//!======================================================================LIBRARIES
   #define BLYNK_PRINT Serial
   #include <ESP8266WiFi.h>
   #include <BlynkSimpleEsp8266.h>

//!======================================================================VARS
   int led     = D4;
   int button1 = D7;
   int button2 = D8;
   int btnReadInterval = 200;
   unsigned long updateButton = millis();

   char auth[] = "blink-authentication-key";
   char ssid[] = "your-wifi-name";
   char pass[] = "your-wif-password";

//!======================================================================BLYNK
   BLYNK_WRITE(V0) {    //* Turn on/off the led
      int pinValue = param.asInt();
      digitalWrite(led, !digitalRead(led));
   }

   BLYNK_WRITE(V1) {    //* Turn on/off the led
      int pinValue = param.asInt();
      digitalWrite(led, !digitalRead(led));
   }

   BLYNK_WRITE(V2) {    //* Turn off the led
      int pinValue = param.asInt();
      digitalWrite(led, LOW);
   }

//!======================================================================SETUP
   void setup() {
      Serial.begin(115200);
      Blynk.begin(auth, ssid, pass);
      pinMode(button1, INPUT);
      pinMode(button2, INPUT);
      pinMode(led, OUTPUT);
   }

//!======================================================================LOOP
   void loop() {
      Blynk.run();
      if (digitalRead(button1) > 0) {
         if (millis() - updateButton > btnReadInterval){
            digitalWrite(led, !digitalRead(led));
            if(digitalRead(led) == HIGH){
               Blynk.virtualWrite(V0, LOW);
            }
            else{
               Blynk.virtualWrite(V0, HIGH);
            }
            updateButton = millis();
         }
         
      }
      if (digitalRead(button2) > 0) {
         if (millis() - updateButton > btnReadInterval){
            digitalWrite(led, !digitalRead(led));
            if(digitalRead(led) == HIGH){
               Blynk.virtualWrite(V1, LOW);
            }
            else{
               Blynk.virtualWrite(V1, HIGH);
            }
            updateButton = millis();
         }
      }
   }
