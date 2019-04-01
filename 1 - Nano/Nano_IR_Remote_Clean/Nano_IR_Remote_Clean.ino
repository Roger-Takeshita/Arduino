//==========================================
//https://github.com/Roger-Takeshita/Arduino
//==========================================

//======================================================================LIBRARY
	#include <IRremote.h>

//======================================================================VARS
	int RECV_PIN = D2; //IR RECEIVER
	int BTN_PRESS;
	bool signalFlag = false;
	int btnReadInterval = 120;
	unsigned long last = millis();

	IRrecv irrecv(RECV_PIN);
	decode_results results;

//======================================================================DECODER
	int getPortNumber (int getButtonCode) {
		switch(getButtonCode) {
			case 0xFDB04F:    //NUMBER 0
				BTN_PRESS=0;
				signalFlag = true;
				break;
			case 0xFD00FF:    //NUMBER 1
				BTN_PRESS=1;
				signalFlag = true;
				break;
			case 0xFD807F:    //NUMBER 2
				BTN_PRESS=2;
				signalFlag = true;
				break;
			case 0xFD40BF:    //NUMBER 3
				BTN_PRESS=3;
				signalFlag = true;
				break;
			case 0xFD20DF:    //NUMBER 4
				BTN_PRESS=4;
				signalFlag = true;
				break;
			case 0xFDA05F:    //NUMBER 5
				BTN_PRESS=5;
				signalFlag = true;
				break;
			case 0xFD609F:    //NUMBER 6
				BTN_PRESS=6;
				signalFlag = true;
				break;
			case 0xFD10EF:    //NUMBER 7
				BTN_PRESS=7;
				signalFlag = true;
				break;
			case 0xFD906F:    //NUMBER 8
				BTN_PRESS=8;
				signalFlag = true;
				break;
			case 0xFD50AF:    //NUMBER 9
				BTN_PRESS=9;
				signalFlag = true;
				break;
			case 0xFD30CF:    //  *
				BTN_PRESS=10;
				signalFlag = true;
				break;
			case 0xFD708F:    //  # 
				BTN_PRESS=11;
				signalFlag = true;
				break;
			case 0xFDA857:    //  OK 
				BTN_PRESS=12;
				signalFlag = true;
				break;
			case 0xFD8877:    //  UP
				BTN_PRESS=13;
				signalFlag = true;
				break;
			case 0xFD9867:    //  DOWN
				BTN_PRESS=14;
				signalFlag = true; 
				break;
			case 0xFD6897:    //  LEFT
				BTN_PRESS=15;
				signalFlag = true;
				break;
			case 0xFD28D7:    //  RIGHT
				BTN_PRESS=16;
				signalFlag = true;
				break;
			case 0xFFFFFFFF:
				break;
		}
		return BTN_PRESS;
	}

//======================================================================SETUP
	void setup() {
		//-------------------------------------------------------Serial
			Serial.begin(9600);
		//-------------------------------------------------------Receiver
			irrecv.enableIRIn();
	}

//======================================================================LOOP
	void loop() {
		if (irrecv.decode(&results)) {
			if (millis() - last > btnReadInterval) {
				irrecv.resume();
				int i = getPortNumber(results.value);
				if (signalFlag){
					signalFlag = false;
					Serial.println(BTN_PRESS);
				}
				last = millis();
				irrecv.resume();
			}
		}
	}


