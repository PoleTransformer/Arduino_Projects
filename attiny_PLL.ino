//ATtiny45 Square Wave Generator (20kHz - 500kHz)
void setup() {
  pinMode(4, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(3, INPUT);

  PLLCSR |= (1 << PLLE);  // PLL enable

  while ((PLLCSR & (1 << PLOCK)) == 0x00)
  {
    // do nothing until plock bit is set
  }

  PLLCSR |= (1 << PCKE); // asynchronous mode

  TCCR1 |= (1 << CTC1) | (1 << COM1A1) | (1 << PWM1A); 

  TCCR1 |= (0 << CS10) | (0 << CS11) | (1 << CS12) | (0 << CS13); //prescaler

  OCR1C = 25; //frequency

  OCR1A = 12; //duty cycle

  TIMSK = (1 << OCIE1A); //enable overflow interrupt

  sei(); //enable global interrupt
}

void loop() {
}
