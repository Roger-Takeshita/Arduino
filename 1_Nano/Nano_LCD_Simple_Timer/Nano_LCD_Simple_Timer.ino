//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

//? About
//* Simple timer display, using LiquidCrystal LCD using I2C communication.

//!======================================================================LIBRARIES
   #include <LiquidCrystal_I2C.h> 
//!======================================================================VARS
   const int buttonHr  = 2;
   const int buttonMin =  3;
   const int button3 = 4;
   const int button4 = 5;
   int secNet = 0;
   int secLast = 0;
   int minNet = 0;
   int hourNet = 0;
   LiquidCrystal_I2C lcd (0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
   uint8_t dgrsChar[8] = {0x4,0xa,0x4,0x0,0x0,0x0,0x0,0x0}; 
//!======================================================================SETUP
   void setup () {
      Serial.begin(9600);
      pinMode(buttonHr, INPUT);
      pinMode(buttonMin, INPUT);
      lcd.begin(16,2);
      lcd.createChar(0, dgrsChar);
      lcd.setCursor (0,0);
      lcd.print(F(" Time Lapse Pro  "));
      lcd.setCursor (0,1);
      lcd.print(F("   Roger-That    "));
      delay(2000);
      lcd.clear();
   }
//!======================================================================LOOP
   void loop () {
   secNet = (millis()/1000)%60;
   if (secNet != secLast){
      secLast = secNet;
      if (secNet ==0){
         CALL_TIME();
         printTime();
      }
   }
   delay(500);
   }
  
//!======================================================================FUNCTIONS
   void CALL_TIME(){
      minNet++;
      if (minNet>59) {
         minNet = 0;
         hourNet++;
         if (hourNet>23){
            hourNet = 0;
         }
      }
   }

   void printTime(){
      lcd.setCursor (0,0);
      lcd.print("  ");
      if (hourNet<10){
         Serial.print("0");
         lcd.print("0");
      }
      Serial.print(hourNet);
      lcd.print(hourNet);
      Serial.print(":");
      lcd.print(":");
      if (minNet<10){
         Serial.print("0");
         lcd.print("0");
      }
      Serial.print(minNet);
      lcd.print(minNet);
      Serial.print(":");
      lcd.print(":");
      if (secNet < 10){
         Serial.print("0");
         lcd.print("0");
      }
      Serial.println(secNet);
      lcd.print(secNet);
   }

