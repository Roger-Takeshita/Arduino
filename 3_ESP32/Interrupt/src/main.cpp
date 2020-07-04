#include <Arduino.h>

const byte button1 = 18;
const byte LED_PIN = 5; // Wemos Lolin 32 Pro - Builtin LED
const int updateButton = 100;
volatile int btn1;
volatile bool buttonPressedFlag = false;
unsigned long internalCounterBtn = millis();

void interruptButton() {
    btn1 = 0;
    btn1 = digitalRead(button1);
    buttonPressedFlag = true;
}

void setup() {
    Serial.begin(9600);
    pinMode(button1, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(button1), interruptButton, RISING);
}

void loop() {
    if (buttonPressedFlag) {
        if (millis() - internalCounterBtn > updateButton) {
            if (btn1 == 1) {
                digitalWrite(LED_PIN, !digitalRead(LED_PIN));
                Serial.println("Button was pressed");
            }
            internalCounterBtn = millis();
        }
        buttonPressedFlag = false;
    }
}