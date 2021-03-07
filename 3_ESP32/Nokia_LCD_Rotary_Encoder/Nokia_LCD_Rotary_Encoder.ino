#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "Button2.h";
#include "ESPRotary.h";

int lcdRST = 27;
int lcdCE = 25;
int lcdDC = 32;
int lcdDIN = 17;
int lcdCLK = 16;
int lcdBL = 0;
int rotaryCLK = 26;
int rotaryDT = 18;
int rotarySW = 19;   // Button
int rotaryStep = 2;  // this number depends on your rotary encoder

ESPRotary r = ESPRotary(rotaryDT, rotaryCLK, rotaryStep);
Button2 b = Button2(rotarySW);

Adafruit_PCD8544 display = Adafruit_PCD8544(lcdCLK, lcdDIN, lcdDC, lcdCE, lcdRST);

void setup() {
  Serial.begin(115200);
  pinMode(lcdBL, OUTPUT);
  backlightOn();
  display.begin();
  display.clearDisplay();
  setContrast();

  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(showDirection);
  r.setRightRotationHandler(showDirection);
  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);
}

void loop() {
  r.loop();
  b.loop();
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0, 0);
  display.print("    Counter");
  display.drawFastHLine(0, 10, 83, BLACK);
  display.setTextSize(3);
  if (r.getPosition() >= 0 && r.getPosition() < 10) {
    display.setCursor(35, 15);
  } else if (r.getPosition() >= 0 && r.getPosition() < 100) {
    display.setCursor(25, 15);
  } else if (r.getPosition() <= -100) {
    display.setCursor(5, 15);
  } else {
    display.setCursor(15, 15);
  }
  display.print(r.getPosition());
  display.display();
}

//======================================================================VOID
void resetDefaults() { backlightOff(); }

void setContrast() {
  display.setContrast(60);
  display.display();
}

void backlightOff() {
  digitalWrite(lcdBL, LOW);
  Serial.println(digitalRead(lcdBL));
}

void backlightOn() {
  digitalWrite(lcdBL, HIGH);
  Serial.println(digitalRead(lcdBL));
}

void rotate(ESPRotary& r) { Serial.println(r.getPosition()); }

// +on left or right rotation
void showDirection(ESPRotary& r) { Serial.println(r.directionToString(r.getDirection())); }

// single click+
void click(Button2& btn) {
  Serial.println("Click!");
  if (digitalRead(lcdBL)) {
    backlightOff();
  } else {
    backlightOn();
  }
}

// long click
void resetPosition(Button2& btn) {
  r.resetPosition();
  resetDefaults();
  Serial.println("Reset!");
}
