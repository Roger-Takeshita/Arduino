//==========================================
//https://github.com/Roger-Takeshita/Arduino
//==========================================

//======================================================================LIBRARY
  #include <DS3231.h>

//======================================================================VARS
  DS3231  rtc(SDA, SCL);  //SDA 4, SCL 5
  int delayTime = 1000;
  Time t;

//======================================================================SETUP
  void setup()  {
  //-------------------------------------------------------TURN ON SERIAL COMMUNICATION 115200 BAND RATE
    Serial.begin(9600);

  //-------------------------------------------------------TURN ON RTC
    rtc.begin();
  
  //-------------------------------------------------------SETUP MANUALLY DATE / TIME / DAY OF THE WEEK
    /*rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
    rtc.setTime(14, 05, 0);     // Set the time to 12:00:00 (24hr format)
    rtc.setDate(7, 11, 2017);*/   // Set the date to January 1st, 2014
}

//======================================================================LOOP
  void loop() {
    CALL_TIME();
  }
//======================================================================VOID
  void CALL_TIME() {
    t = rtc.getTime();
    //CLOCK   
      // HOUR
      if (t.hour<10){
        Serial.print("0");
      }
      Serial.print(t.hour, DEC);
      // MINUTE
      Serial.print(":");
      if (t.min<10){
        Serial.print("0");
      }
      Serial.print(t.min, DEC);
      // SECOND
      Serial.print(":");
      if (t.sec<10){
        Serial.print("0");
      }
      Serial.print(t.sec, DEC);
      
    // DATE
      //DAY
      Serial.print(" ");
      if (t.date<10){
        Serial.print("0");
      }
      Serial.print(t.date, DEC);
      // MONTH
      Serial.print("/");
      if (t.mon<10){
        Serial.print("0");
      }
      Serial.print(t.mon, DEC);
      // YEAR
      Serial.print("/");
      Serial.print(t.year, DEC);
      
    // DAY OF THE WEEK
      Serial.print(" ");
      Serial.print(rtc.getDOWStr());
      Serial.println();

    delay (delayTime);
  }
