//==========================================
//https://github.com/Roger-Takeshita/Arduino
//==========================================

//======================================================================VARS
  int button1 = 32;
  int button2 = 33;
  int delayTime = 1000;
  int updateButton = 150;
  volatile int btn1, btn2;
  volatile bool buttonPressedFlag = false;
  unsigned long lastT_Button = millis();

//======================================================================INTERRUPT
  void interruptButtonPressed() {
    btn1 = btn2 = 0;
    btn1 = digitalRead(button1);
    btn2 = digitalRead(button2);
    if (btn1 > 0 || btn2 > 0) {
      buttonPressedFlag = true;
    }
  }
//======================================================================SETUP
  void setup() {
    //Serial.begin(9600);
    Serial.begin(115200);
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    attachInterrupt (button1, interruptButtonPressed, RISING);
    attachInterrupt (button2, interruptButtonPressed, RISING);
  }

//======================================================================LOOP
  void loop() {
    //-------------------------------------------------------LOOP Interrupt Buttons
      if (buttonPressedFlag) {
        if (millis() - lastT_Button > updateButton){
          if (btn1 > 0) {
            Serial.println("Button 1 was pressed");
          }
          if (btn2 > 0) {
            Serial.println("Button 2 was pressed");
          }
          lastT_Button = millis();
        }
        buttonPressedFlag = false;
      }
      
    //---------------------------------------------------------OTHER
  }
  
