#include <Wire.h>
#define RTC_ADDRESS 0x68
#define dataPin1 2
#define latchPin1 3
#define clockPin1 4
#define dataPin2 5
#define latchPin2 6
#define clockPin2 7
#define colon 8

//0,1,2,3,4,5,6,7,8,9
byte bcdVal[] = {B00000000, B00010001, B00100010, B00110011, B01000100, B01010101, B01100110, B01110111, B10001000, B10011001};
bool colonState;
bool poisonFlag;
int i = 0;

void setup() {
  for (int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  Wire.begin();

  cli();
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 0.5hz
  OCR1A = 15624;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
  
//  setHour(12);
//  setMinute(45);
//  setSecond(0);
}

ISR(TIMER1_COMPA_vect) {
  colonState = !colonState;
  if (poisonFlag) {
    digitalWrite(latchPin1, LOW);
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, (bcdVal[i])); //hour
    shiftOut(dataPin1, clockPin1, LSBFIRST, (bcdVal[i])); //minute
    digitalWrite(latchPin1, HIGH);
    digitalWrite(latchPin2, HIGH);
    i++;
    if (i > 10) {
      i = 0;
      poisonFlag = false;
    }
  }
}

void loop() {
  byte hour = getHour();
  byte minute = getMinute();
  byte second = getSecond();
  if (second == 0 && minute == 0) {
    poisonFlag = true;
  }
  if (!poisonFlag) {
    byte firstHour = hour % 10;
    byte secondHour = hour / 10;
    byte firstMinute = minute % 10;
    byte secondMinute = minute / 10;
    digitalWrite(latchPin1, LOW);
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin2, LSBFIRST, (bcdVal[firstHour] | B11110000) & (bcdVal[secondHour] | B00001111)); //hour
    shiftOut(dataPin1, clockPin1, LSBFIRST, (bcdVal[firstMinute] | B11110000) & (bcdVal[secondMinute] | B00001111)); //minute
    digitalWrite(latchPin1, HIGH);
    digitalWrite(latchPin2, HIGH);
  }
  if (colonState) {
    digitalWrite(colon, HIGH);
  }
  else {
    digitalWrite(colon, LOW);
  }
}

byte decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

byte bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}

void setHour(byte hour) { //12 hour mode only
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x02);
  bool am_pm = hour > 11;
  Wire.write(decToBcd(hour) | (am_pm << 5) | B01000000);
  Wire.endTransmission();
}

void setMinute(byte minute) {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x01);
  Wire.write(decToBcd(minute));
  Wire.endTransmission();
}

void setSecond(byte second) {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(second));
  Wire.endTransmission();
}

byte getHour() {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(RTC_ADDRESS, 1);
  byte temp_hour = Wire.read();
  return (bcdToDec(temp_hour & B00011111));
}

byte getMinute() {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom(RTC_ADDRESS, 1);
  byte temp_minute = Wire.read();
  return (bcdToDec(temp_minute));
}

byte getSecond() {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(RTC_ADDRESS, 1);
  byte temp_hour = Wire.read();
  return (bcdToDec(temp_hour));
}
