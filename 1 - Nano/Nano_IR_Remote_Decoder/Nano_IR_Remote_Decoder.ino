//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

//? About
//* Infrared decoder, this is the first step to indentify the Hex value of each button from the any remote.

//? Simulation
//* https://www.tinkercad.com/things/bG4kuE9qqGp

//!======================================================================LIBRARIES
   #include <IRremote.h>
//!======================================================================VARS
   int RECV_PIN = 12;
   IRrecv irrecv(RECV_PIN);
   decode_results results;
//!======================================================================SETUP
   void setup() {
      Serial.begin(9600);
      irrecv.enableIRIn();  // Start the receiver
   }
//!======================================================================LOOP
   void loop() {
      if (irrecv.decode(&results)) {
         Serial.println(results.value, HEX);
         irrecv.resume();   // Receive the next value
      }
      delay(100);
   }

