#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int year, month, day, hour, minute, second;

void setup() {
    Serial.begin(115200);

    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        abort();
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // July 1, 2020 at 22pm you would call:
        rtc.adjust(DateTime(2020, 7, 1, 22, 0, 0));
    }
}

void loop() {
    DateTime now = rtc.now();
    year = now.year();
    month = now.month();
    day = now.day();
    hour = now.hour();
    minute = now.minute();
    second = now.second();

    Serial.print(year, DEC);
    Serial.print('/');
    Serial.print(month, DEC);
    Serial.print('/');
    Serial.print(day, DEC);
    Serial.print(" - ");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(" - ");
    Serial.print(hour, DEC);
    Serial.print(':');
    Serial.print(minute, DEC);
    Serial.print(':');
    Serial.print(second, DEC);
    Serial.println();

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();
    delay(1000);
}