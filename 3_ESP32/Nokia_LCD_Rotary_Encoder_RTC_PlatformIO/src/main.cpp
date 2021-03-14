#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Arduino.h>

#include "Button2.h"
#include "ESPRotary.h"
#include "RTClib.h"

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
// int RTC_SCL = 22;
// int RTC_SDA = 12;
unsigned long lastTimeClock = millis();
int waitClock = 1000;  // 1    sec
int8_t hora, minuto, segundo, dia, mes, ano;

ESPRotary r = ESPRotary(rotaryDT, rotaryCLK, rotaryStep);
Button2 b = Button2(rotarySW);

Adafruit_PCD8544 display = Adafruit_PCD8544(lcdCLK, lcdDIN, lcdDC, lcdCE, lcdRST);
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Saturday"};

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

void resetDefaults() { backlightOff(); }

void rotate(ESPRotary& r) { Serial.println(r.getPosition()); }

// +on left or right rotation
void showDirection(ESPRotary& r) { Serial.println(r.directionToString(r.getDirection())); }

// +single click+
void click(Button2& btn) {
  Serial.println("Click!");
  if (digitalRead(lcdBL)) {
    backlightOff();
  } else {
    backlightOn();
  }
}

// +long click
void resetPosition(Button2& btn) {
  r.resetPosition();
  resetDefaults();
  Serial.println("Reset!");
}

void printHeader() {
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0, 0);
  display.setCursor(18, 0);
  if (hora < 10) {
    display.print(0);
  }
  display.print(hora);
  display.print(":");
  if (minuto < 10) {
    display.print(0);
  }
  display.print(minuto);
  display.print(":");
  if (segundo < 10) {
    display.print(0);
  }
  display.print(segundo);
  display.drawFastHLine(0, 10, 83, BLACK);
}

void printEncoder() {
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
}

void updateClock() {
  if (millis() - lastTimeClock > waitClock) {
    DateTime now = rtc.now();
    hora = now.hour();
    minuto = now.minute();
    segundo = now.second();
    dia = now.day();
    mes = now.month();
    ano = now.year();
    lastTimeClock = millis();
  }
}

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

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // January 1, 2021 at HH, MM, SS:
    rtc.adjust(DateTime(2021, 1, 30, 21, 10, 0));
  }
  // January 1, 2021 at HH, MM, SS:
  // rtc.adjust(DateTime(2021, 1, 30, 21, 10, 0));
}

void loop() {
  r.loop();
  b.loop();
  updateClock();
  printHeader();
  printEncoder();
  display.display();
}