//!------------------------------------------//
//!             Roger Takeshita              //
//!    https://github.com/Roger-Takeshita    //
//!------------------------------------------//

//? About
//*   Base project to use interrput buttons using pull down resistor during the execution of the code.

//* INTERRUPT
//*   Interrupts are useful for making things happen automatically in microcontroller programs and can help solve timing problems. Good tasks for using an interrupt may include reading a rotary encoder, or monitoring user input.
//*   If you wanted to ensure that a program always caught the pulses from a rotary encoder, so that it never misses a pulse, it would make it very tricky to write a program to do anything else, because the program would need to constantly poll the sensor lines for the encoder, in order to catch pulses when they occurred. Other sensors have a similar interface dynamic too, such as trying to read a sound sensor that is trying to catch a click, or an infrared slot sensor (photo-interrupter) trying to catch a coin drop. In all of these situations, using an interrupt can free the microcontroller to get some other work done while not missing the input.

//* PULL-UP RESISTOR
//*   Pullup Resistors with pins configured as INPUT
//*     Often it is useful to steer an input pin to a known state if no input is present. This can be done by adding a pullup resistor (to +5V), or a pulldown resistor (resistor to ground) on the input. A 10K resistor is a good value for a pullup or pulldown resistor.

//*   Properties of Pins Configured as INPUT_PULLUP
//*     There are 20K pullup resistors built into the Atmega chip that can be accessed from software. These built-in pullup resistors are accessed by setting the pinMode() as INPUT_PULLUP. This effectively inverts the behavior of the INPUT mode, where HIGH means the sensor is off, and LOW means the sensor is on.
//*     The value of this pullup depends on the microcontroller used. On most AVR-based boards, the value is guaranteed to be between 20kΩ and 50kΩ. On the Arduino Due, it is between 50kΩ and 150kΩ. For the exact value, consult the datasheet of the microcontroller on your board.
//*     When connecting a sensor to a pin configured with INPUT_PULLUP, the other end should be connected to ground. In the case of a simple switch, this causes the pin to read HIGH when the switch is open, and LOW when the switch is pressed.
//*     The pullup resistors provide enough current to dimly light an LED connected to a pin that has been configured as an input. If LEDs in a project seem to be working, but very dimly, this is likely what is going on.
//*     The pullup resistors are controlled by the same registers (internal chip memory locations) that control whether a pin is HIGH or LOW. Consequently, a pin that is configured to have pullup resistors turned on when the pin is an INPUT, will have the pin configured as HIGH if the pin is then switched to an OUTPUT with pinMode(). This works in the other direction as well, and an output pin that is left in a HIGH state will have the pullup resistors set if switched to an input with pinMode().

//? Links
//* https://www.tinkercad.com/things/d5w57o408Xp-nanobtnanalogread
//* https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
//* https://www.arduino.cc/en/Tutorial/DigitalPins

//? Simulation
//* https://www.tinkercad.com/things/btpq6kXChfU

//!======================================================================VARS
   const byte button1 = 2;   //Arduino Nano Internal Interrput I/O are 2 and 3 (digital pins)
   const byte button2 = 3;
   const byte led1 = 4;
   const byte led2 = 5;
   const int updateButton = 100;
   volatile int btn1, btn2;
   volatile bool buttonPressedFlag = false;
   unsigned long lastT_Button = millis();
//!======================================================================INTERRUPT
   void interruptButton() {
      btn1 = btn2 = 0;
      btn1 = digitalRead(button1);
      btn2 = digitalRead(button2);
      buttonPressedFlag = true;
   }
//!======================================================================SETUP
   void setup() {
      Serial.begin(9600);
      pinMode(button1, INPUT_PULLUP);
      pinMode(button2, INPUT_PULLUP);
      pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
      attachInterrupt (digitalPinToInterrupt(button1), interruptButton, RISING);
      attachInterrupt (digitalPinToInterrupt(button2), interruptButton, RISING);
   }
//!======================================================================LOOP
  void loop() {
      //?-------------------------------------------------------LOOP Interrupt Buttons
         if (buttonPressedFlag) {
            if (millis() - lastT_Button > updateButton){
               if (btn1 == 1) {
                  digitalWrite(led1, !digitalRead(led1));
                  Serial.println("Button 1 was pressed");
               } else if (btn2 == 1) {
                  digitalWrite(led2, !digitalRead(led2));
                  Serial.println("Button 2 was pressed");
               }
               lastT_Button = millis();
            }
            buttonPressedFlag = false;
         }    
      //?-------------------------------------------------------OTHER
  }