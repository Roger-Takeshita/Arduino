//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

//? About
//* Base code to use the IR Remote with IR receiver.

//!======================================================================LIBRARIES
	#include <IRremote.h>
//!======================================================================VARS
	int RECV_PIN = D2; //IR RECEIVER
	int BTN_PRESS;
	int signalOK = 0;
	int btnReadInterval = 120;
	unsigned long last = millis();
	IRrecv irrecv(RECV_PIN);
	decode_results results;
//!======================================================================FUNCTIONS
	int getPortNumber (int getButtonCode) {
		switch(getButtonCode){
			case 0xFDB04F:    //NUMBER 0
				BTN_PRESS=0;
				signalOK=1;
				break;
			case 0xFD00FF:    //NUMBER 1
				BTN_PRESS=1;
				signalOK=1;
				break;
			case 0xFD807F:    //NUMBER 2
				BTN_PRESS=2;
				signalOK=1;
				break;
			case 0xFD40BF:    //NUMBER 3
				BTN_PRESS=3;
				signalOK=1;
				break;
			case 0xFD20DF:    //NUMBER 4
				BTN_PRESS=4;
				signalOK=1;
				break;
			case 0xFDA05F:    //NUMBER 5
				BTN_PRESS=5;
				signalOK=1;
				break;
			case 0xFD609F:    //NUMBER 6
				BTN_PRESS=6;
				signalOK=1;
				break;
			case 0xFD10EF:    //NUMBER 7
				BTN_PRESS=7;
				signalOK=1;
				break;
			case 0xFD906F:    //NUMBER 8
				BTN_PRESS=8;
				signalOK=1;
				break;
			case 0xFD50AF:    //NUMBER 9
				BTN_PRESS=9;
				signalOK=1;
				break;
			case 0xFD30CF:    //  *
				BTN_PRESS=10;
				signalOK=1;
				break;
			case 0xFD708F:    //  # 
				BTN_PRESS=11;
				signalOK=1;
				break;
			case 0xFDA857:    //  OK 
				BTN_PRESS=12;
				signalOK=1;
				break;
			case 0xFD8877:    //  UP
				BTN_PRESS=13;
				signalOK=1;
				break;
			case 0xFD9867:    //  DOWN
				BTN_PRESS=14;
				signalOK=1; 
				break;
			case 0xFD6897:    //  LEFT
				BTN_PRESS=15;
				signalOK=1;
				break;
			case 0xFD28D7:    //  RIGHT
				BTN_PRESS=16;
				signalOK=1;
				break;
			case 0xFFFFFFFF:
				break;
		}
		return BTN_PRESS;
	}
//!======================================================================SETUP
	void setup() {
		//?----------------------------TURN ON SERIAL COMMUNICATION
			Serial.begin(9600);

		//?----------------------------TURN ON IR RECIVER
			irrecv.enableIRIn();
	}
//!======================================================================LOOP
	void loop() {
		if (irrecv.decode(&results)){
			if (millis() - last > btnReadInterval){
				irrecv.resume();
				int i = getPortNumber(results.value);
				if (signalOK == 1) {
					signalOK = 0;
					Serial.println(BTN_PRESS);
				}
				last = millis();
				irrecv.resume();
			}
		}
	}


