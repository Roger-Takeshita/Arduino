//==========================================
//https://github.com/Roger-Takeshita/Arduino
//==========================================

//======================================================================LIBRARY
	#include <IRremote.h>

//======================================================================VARS
	int RECV_PIN = 12;

	IRrecv irrecv(RECV_PIN);
	decode_results results;

//======================================================================SETUP
	void setup() {
		//-------------------------------------------------------Serial
	  	Serial.begin(9600);
	 	//-------------------------------------------------------IR Receiver
	  	irrecv.enableIRIn();
	}
//====================================================================== LOOP
	void loop() {
	  if (irrecv.decode(&results)) {
	    Serial.println(results.value, HEX);
	    irrecv.resume(); // Receive the next value
	  }
	  delay(100);
	}
