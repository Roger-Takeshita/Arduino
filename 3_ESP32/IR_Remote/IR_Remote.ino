//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

#include <Arduino.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>

const uint16_t RECV_PIN = 35;
const char *button[17] = {"0",  "1",    "2",    "3",     "4", "5",
                          "6",  "7",    "8",    "9",     "*", "#",
                          "UP", "DOWN", "LEFT", "RIGHT", "OK"};
const uint16_t btnReadInterval = 100;
unsigned long last = millis();

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  Serial.println();
  Serial.print("IR Receiver Running on PIN ");
  Serial.println(RECV_PIN);
}

int getBtn(int btnCode) {
  int BTN_PRESS = -1;

  switch (btnCode) {
  case 16625743: // NUMBER 0
    BTN_PRESS = 0;

    break;
  case 16580863: // NUMBER 1
    BTN_PRESS = 1;

    break;
  case 16613503: // NUMBER 2
    BTN_PRESS = 2;

    break;
  case 16597183: // NUMBER 3
    BTN_PRESS = 3;

    break;
  case 16589023: // NUMBER 4
    BTN_PRESS = 4;

    break;
  case 16621663: // NUMBER 5
    BTN_PRESS = 5;

    break;
  case 16605343: // NUMBER 6
    BTN_PRESS = 6;

    break;
  case 16584943: // NUMBER 7
    BTN_PRESS = 7;

    break;
  case 16617583: // NUMBER 8
    BTN_PRESS = 8;

    break;
  case 16601263: // NUMBER 9
    BTN_PRESS = 9;

    break;
  case 16593103: //  *
    BTN_PRESS = 10;

    break;
  case 16609423: //  #
    BTN_PRESS = 11;

    break;
  case 16615543: //  UP
    BTN_PRESS = 12;

    break;
  case 16619623: //  DOWN
    BTN_PRESS = 13;

    break;
  case 16591063: //  LEFT
    BTN_PRESS = 14;

    break;
  case 16607383: //  RIGHT
    BTN_PRESS = 15;

    break;
  case 16623703: //  OK
    BTN_PRESS = 16;

    break;
  default:
    break;
  }

  return BTN_PRESS;
}

void loop() {
  if (irrecv.decode(&results)) {
    if (millis() - last > btnReadInterval) {
      int btn = getBtn(results.value);
      if (btn != -1) {
        Serial.println(button[btn]);
      }

      last = millis();
      irrecv.resume();
    }
  }
}
