#define SET(x,y) x|=_BV(y)
#define CLR(x,y) x&=(~_BV(y))
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
unsigned long prevMillis = 0;
unsigned long period = 500;
bool redLed = false;
bool blueLed = true;
char receivedData[32];
char incoming;
int pos = 0;
bool dataReceived = false;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  for (int i = 2; i < 20; i++) {
    pinMode(i, OUTPUT);
  }
  tone(19, 440);
  delay(100);
  noTone(19);
}

void loop() {
  if (millis() - prevMillis >= period) {
    prevMillis = millis();
    if (redLed) {
      SET(PORTB, 0);
    }
    else {
      CLR(PORTB, 0);
    }
    if (blueLed) {
      SET(PORTB, 1);
    }
    else {
      CLR(PORTB, 1);
    }
    blueLed = !blueLed;
    redLed = !redLed;
  }
  if (Serial.available() > 0) {
    incoming = Serial.read();
    if (incoming != '\n') {
      pos++;
      receivedData[pos] = incoming;
      dataReceived = true;
    }
    else {
      pos = 0;
      dataReceived = false;
    }
  }
  for(int i = 0; i < pos && dataReceived; i++) {
    if(receivedData[i] != '\0') {
      if(receivedData[i] == '/') {
        lcd.clear();
        lcd.setCursor(0,0);
      }
      else {
        lcd.print(receivedData[i]);
      }
    }
    receivedData[i] = '\0';
  }
}
