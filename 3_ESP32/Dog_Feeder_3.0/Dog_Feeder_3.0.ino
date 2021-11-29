#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "Button2.h";
#include "ESPRotary.h";
#include "RTClib.h"
#include "env.h";

// Nokia5110 LCD
int lcdRST     = 27;
int lcdCE      = 25;
int lcdDC      = 32;
int lcdDIN     = 17;
int lcdCLK     = 16;
int lcdBL      = 0;

// Rotary Encoder
int rotaryCLK  = 26;
int rotaryDT   = 18;
int rotarySW   = 19; // Button
int rotaryStep = 2;  // This number depends on your rotary encoder

// RTC - Real Time Clock
// int RTC_SCL = 22;
// int RTC_SDA = 12;

unsigned long lastTimeClock = millis();
unsigned long lastTimeOTA = millis();

int updateTime = 1000;   // 1 sec
int updateOTA  = 600000; // 10 min

bool otaFlag = true;
int8_t hora, minuto, segundo, dia, mes, ano;

ESPRotary r = ESPRotary(rotaryDT, rotaryCLK, rotaryStep);
Button2 b = Button2(rotarySW);

Adafruit_PCD8544 display = Adafruit_PCD8544(lcdCLK, lcdDIN, lcdDC, lcdCE, lcdRST);
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Saturday"};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Hostname
  ArduinoOTA.setHostname(HOST);

  // No authentication by default
  // Remove next line if you don't want to add an authentication password
  ArduinoOTA.setPassword(AUTH_PASSWORD);

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // WIFI_PASSWORD can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setWIFI_PASSWORDHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else
        type = "filesystem";

      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
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

  Serial.print("Connected to ");
  Serial.println(WIFI_NAME);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  checkOTA();
  r.loop();
  b.loop();
  updateClock();
  printHeader();
  printEncoder();
  display.display();
}

void checkOTA() {
  if (millis() - lastTimeOTA <= updateOTA) {
    ArduinoOTA.handle();
  } else if (otaFlag == true) {
    Serial.print("OTA has been DISABLED!");
    otaFlag = false;
  }
}

void resetDefaults() {
  backlightOff();
}

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
  if (millis() - lastTimeClock > updateTime) {
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
