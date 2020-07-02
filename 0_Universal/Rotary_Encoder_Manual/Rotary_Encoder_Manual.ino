  #define PinA  34 // Used for generating interrupts using CLK signal
  #define PinB  35 // Used for reading DT signal
  #define PinSW 32 // Used for the push button switch
int lastCount = 50;
volatile int virtualPosition = 0;
int updateInterruptTime = 50;
unsigned long lastInterruptTime = millis();

void isr ()  {

  if (millis() - lastInterruptTime > updateInterruptTime) {
    if (digitalRead(PinB) == HIGH) {
      virtualPosition-- ; // Could be -5 or -10
    }
    else {
      virtualPosition++ ; // Could be +5 or +10
    }
    Serial.println(virtualPosition);
    lastInterruptTime = millis();
  }  
}

void setup() {
  Serial.begin(115200);
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);
  pinMode(PinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PinA), isr, CHANGE);
  Serial.println("Start");
}

void loop() {
  if ((!digitalRead(PinSW))) {
    virtualPosition = 0;
    while (!digitalRead(PinSW))
      delay(10);
    Serial.println("Reset");
  }

  if (virtualPosition != lastCount) {
    Serial.print(virtualPosition > lastCount ? "Up  :" : "Down:");
    Serial.println(virtualPosition);
    lastCount = virtualPosition ;
  }
}
