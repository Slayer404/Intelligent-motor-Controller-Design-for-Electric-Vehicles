// #define pot A0
// #define pwm 9
// int pwmVal = 0;
// const float freq=2000;
// void setup() {
//   pinMode(pot, INPUT);
//   pinMode(pwm, OUTPUT);
//   Serial.begin(9600);
// }

// void loop() {
//   unsigned int potVal = analogRead(pot);
//   pwmVal = map(potVal, 0, 1023, 0, 255);
  
//   Serial.println(pwmVal);
//   analogWrite(pwm, pwmVal);
//   // delay(100);
// }

#define pot A0
#define pwm 9

void setup() {
  pinMode(pot, INPUT);
  pinMode(pwm, OUTPUT);
  Serial.begin(9600);

  // Configure Timer1 for 2 kHz PWM on pin 9
  TCCR1A = 0;               // Clear TCCR1A register
  TCCR1B = 0;               // Clear TCCR1B register
  TCNT1  = 0;               // Initialize counter value to 0

  TCCR1A |= (1 << COM1A1);  // Non-inverting mode
  TCCR1A |= (1 << WGM11);   // Mode 14: Fast PWM, TOP = ICR1
  TCCR1B |= (1 << WGM13) | (1 << WGM12); // Mode 14: Fast PWM, TOP = ICR1
  TCCR1B |= (1 << CS10);    // No prescaling

  ICR1 = 1999;              // Set TOP value for 2 kHz frequency
}

void loop() {
  unsigned int potVal = analogRead(pot);
  int pwmVal = map(potVal, 0, 1023, 0, 1999); // Map pot value to ICR1 range for duty cycle
  
  Serial.println(pwmVal);
  OCR1A = pwmVal;           // Set PWM duty cycle
  if (pwmVal <110)
    OCR1A = 110;
  delay(10);               // Short delay for stabilization
}

