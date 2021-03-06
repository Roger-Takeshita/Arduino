#include "Button2.h";
#include "ESPRotary.h";

#define ROTARY_PIN1       26 // CLK
#define ROTARY_PIN2       18 // DT
#define BUTTON_PIN        19 // SW
#define CLICKS_PER_STEP   4  // this number depends on your rotary encoder

ESPRotary r = ESPRotary(ROTARY_PIN2, ROTARY_PIN1, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);

void setup() {
  Serial.begin(115200);
  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(showDirection);
  r.setRightRotationHandler(showDirection);
  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);
}

void loop() {
  r.loop();
  b.loop();
}

// on change
void rotate(ESPRotary & r) {
   Serial.println(r.getPosition());
}

// on left or right rotation
void showDirection(ESPRotary & r) {
  Serial.println(r.directionToString(r.getDirection()));
}

// single click
void click(Button2 & btn) {
  Serial.println("Click!");
}

// long click
void resetPosition(Button2 & btn) {
  r.resetPosition();
  Serial.println("Reset!");
}
