//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

//? About
//* IR Remote with IR receiver, the hex codes were modified to match the Tinkercad website. You modify accordenly to your remote.

//? Simulation
//* https://www.tinkercad.com/things/bG4kuE9qqGp

//!======================================================================LIBRARIES
   #include <IRremote.h>
//!======================================================================VARS
   int RECV_PIN   = 2;
   int RELAY_PIN1 = 3;
   int RELAY_PIN2 = 4;
   int RELAY_PIN3 = 5;
   int RELAY_PIN4 = 6;
   unsigned long last_result = millis();
   unsigned long update_result = 150;
   IRrecv irrecv(RECV_PIN);
   decode_results results;
//!======================================================================FUNCTIONS
   void decode_signal() {
      if (irrecv.decode(&results)) {
         if (millis() - last_result > update_result) {
            switch(results.value) {
               case 0xFD30CF:
                  Serial.println("Number 0");
               break;
               case 0xFD08F7:
                  Serial.println("Number 1");
                  digitalWrite(RELAY_PIN1, !digitalRead(RELAY_PIN1));
               break;
               case 0xFD8877:
                  Serial.println("Number 2");
                  digitalWrite(RELAY_PIN2, !digitalRead(RELAY_PIN2));
               break;
               case 0xFD48B7:
                  Serial.println("Number 3");
                  digitalWrite(RELAY_PIN3, !digitalRead(RELAY_PIN3));
               break;
               case 0xFD28D7:
                  Serial.println("Number 4");
                  digitalWrite(RELAY_PIN4, !digitalRead(RELAY_PIN4));
               break;
               case 0xFDA857:
                  Serial.println("Number 5");
               break;
               case 0xFD6897:
                  Serial.println("Number 6");
               break;
               case 0xFD18E7:
                  Serial.println("Number 7");
               break;
               case 0xFD9867:
                  Serial.println("Number 8");
               break;
               case 0xFD58A7:
                  Serial.println("Number 9");
               break;
               case 0xFD00FF:
                  Serial.println("On/Off");
                  digitalWrite(RELAY_PIN1, LOW);
                  digitalWrite(RELAY_PIN2, LOW);
                  digitalWrite(RELAY_PIN3, LOW);
                  digitalWrite(RELAY_PIN4, LOW);
               break;
               case 0xFFFFFFFF:
                  Serial.println("UNKNOWN");
               break;
            }
         }
         last_result = millis();
         irrecv.resume(); // Receive the next value
      }
   }
//!======================================================================SETUP
   void setup() {
      pinMode(RELAY_PIN1, OUTPUT);
      pinMode(RELAY_PIN2, OUTPUT);
      pinMode(RELAY_PIN3, OUTPUT);
      pinMode(RELAY_PIN4, OUTPUT);
      digitalWrite(RELAY_PIN1, HIGH);
      digitalWrite(RELAY_PIN2, HIGH);
      digitalWrite(RELAY_PIN3, HIGH);
      digitalWrite(RELAY_PIN4, HIGH);
      Serial.begin(9600);
      irrecv.enableIRIn(); // Start the receiver
   }
//!======================================================================LOOP
   void loop() {
      decode_signal();
   }
