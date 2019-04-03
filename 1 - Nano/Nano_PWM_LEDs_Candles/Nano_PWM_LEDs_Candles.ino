//==========================================
//https://github.com/Roger-Takeshita/Arduino
//==========================================
//======================================================================VARS
	int PWM1=11;
	int PWM2=10;
	int PWM3=9;
	int PWM4=3;

//======================================================================SETUP
	void setup() {
		pinMode(PWM1, OUTPUT);
		pinMode(PWM2, OUTPUT);
		pinMode(PWM3, OUTPUT);
		pinMode(PWM4, OUTPUT);
	}
//======================================================================LOOP
	void loop() {
		analogWrite(PWM1, random(120)+135);
		analogWrite(PWM2, random(120)+135);
		analogWrite(PWM3, random(120)+135);
		analogWrite(PWM4, random(120)+135);
		delay(random(100));
	}
