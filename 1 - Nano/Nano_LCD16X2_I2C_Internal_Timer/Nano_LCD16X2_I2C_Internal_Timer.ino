//==========================================
//https://github.com/Roger-Takeshita/Arduino
//==========================================

//======================================================================LIBRARY
  #include <LiquidCrystal_I2C.h> 

//======================================================================VARS
  int buttonHr  = 2;
  int buttonMin =  3;
  int secNet = 0;
  int secLast = 0;
  int minNet = 0;
  int hourNet = 0;

  //-------------------------------------------------------LCD 16x2 I2C
    LiquidCrystal_I2C lcd (0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
    uint8_t dgrsChar[8] = {0x4,0xa,0x4,0x0,0x0,0x0,0x0,0x0}; 

//======================================================================SETUP
  void setup () {
    //-------------------------------------------------------Serial
      Serial.begin(9600);
    //-------------------------------------------------------LCD 16x2 I2C
      lcd.begin(16,2);
      lcd.createChar(0, dgrsChar);
      lcd.setCursor (0,0);
      lcd.print(F(" Time Lapse Pro  "));
      lcd.setCursor (0,1);
      lcd.print(F("   Roger-That    "));
      delay(2000);
      //lcd.noBacklight ();
      lcd.clear();
    //-------------------------------------------------------Vars
      pinMode(buttonHr, INPUT);
      pinMode(buttonMin, INPUT);
  }

//======================================================================LOOP
  void loop () {
   secNet = (millis()/1000)%60; // 1 Sec
   if (secNet != secLast) {
     secLast = secNet;
     if (secNet ==0) {
       CALL_TIME();
       printTime();
     }
   }
   delay(500);
  }
  
//======================================================================VOID
  void CALL_TIME() {
    minNet++;
    if (minNet>59) {
      minNet = 0;
      hourNet++;
      if (hourNet>23) {
        hourNet = 0;
      }
    }
  }

  void printTime() {
     lcd.setCursor (0,0);
     lcd.print("  ");
     if (hourNet<10) {
        Serial.print("0");
        lcd.print("0");
     }
     Serial.print(hourNet);
     lcd.print(hourNet);
     Serial.print(":");
     lcd.print(":");
     if (minNet<10) {
        Serial.print("0");
        lcd.print("0");
     }
     Serial.print(minNet);
     lcd.print(minNet);
     Serial.print(":");
     lcd.print(":");
     if (secNet < 10) {
        Serial.print("0");
        lcd.print("0");
     }
     Serial.println(secNet);
     lcd.print(secNet);
  }

