#define SET(x,y) x|=_BV(y)
#define CLR(x,y) x&=(~_BV(y))
#define joe 19
#define longDuration 200
#define shortDuration 100
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
int counter = 0;
bool flag = false;

//SET(PORTB, 0);
//CLR(PORTB, 0);
//SET(PORTB, 1);
//CLR(PORTB, 1);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  for (int i = 2; i < 20; i++) {
    pinMode(i, OUTPUT);
  }
  tone(joe, 440);
  delay(100);
  noTone(joe);
}

void loop() {
  if (Serial.available() > 0) {
    char incoming = Serial.read();
    if (incoming == '/') {
      lcd.clear();
      lcd.setCursor(0, 0);
      counter = 0;
    }
    else {
      lcd.print(incoming);
      convertToMorse(incoming);
      counter++;
      if (counter > 15 && !flag) {
        lcd.setCursor(0, 1);
        flag = true;
      }
      if (counter > 32) {
        lcd.clear();
        lcd.setCursor(0, 0);
        counter = 0;
        flag = false;
      }
    }
  }
}

void l() {
  SET(PORTB, 0);
  tone(joe, 440);
  delay(longDuration);
  noTone(joe);
  CLR(PORTB, 0);
  delay(longDuration);
}

void s() {
  SET(PORTB, 1);
  tone(joe, 440);
  delay(shortDuration);
  noTone(joe);
  CLR(PORTB, 1);
  delay(shortDuration);
}

void convertToMorse(char input) {
  if (input == 'A' || input == 'a') {
    s();
    l();
  }
  if (input == 'B' || input == 'b') {
    l();
    s();
    s();
    s();
  }
  if (input == 'C' || input == 'c') {
    l();
    s();
    l();
    s();
  }
  if (input == 'D' || input == 'd') {
    l();
    s();
    s();
  }
  if (input == 'E' || input == 'e') {
    s();
  }
  if (input == 'F' || input == 'f') {
    s();
    s();
    l();
    s();
  }
  if (input == 'G' || input == 'g') {
    l();
    l();
    s();
  }
  if (input == 'H' || input == 'h') {
    s();
    s();
    s();
    s();
  }
  if (input == 'I' || input == 'i') {
    s();
    s();
  }
  if (input == 'J' || input == 'j') {
    s();
    l();
    l();
    l();
  }
  if (input == 'K' || input == 'k') {
    l();
    s();
    l();
  }
  if (input == 'L' || input == 'l') {
    s();
    l();
    s();
    s();
  }
  if (input == 'M' || input == 'm') {
    l();
    l();
  }
  if (input == 'N' || input == 'n') {
    l();
    s();
  }
  if (input == 'O' || input == 'o') {
    l();
    l();
    l();
  }
  if (input == 'P' || input == 'p') {
    s();
    l();
    l();
    s();
  }
  if (input == 'Q' || input == 'q') {
    l();
    l();
    s();
    l();
  }
  if (input == 'R' || input == 'r') {
    s();
    l();
    s();
  }
  if (input == 'S' || input == 's') {
    s();
    s();
    s();
  }
  if (input == 'T' || input == 't') {
    l();
  }
  if (input == 'U' || input == 'u') {
    s();
    s();
    l();
  }
  if (input == 'V' || input == 'v') {
    s();
    s();
    s();
    l();
  }
  if (input == 'W' || input == 'w') {
    s();
    l();
    l();
  }
  if (input == 'X' || input == 'x') {
    l();
    s();
    s();
    l();
  }
  if (input == 'Y' || input == 'y') {
    l();
    s();
    l();
    l();
  }
  if (input == 'Z' || input == 'z') {
    l();
    l();
    s();
    s();
  }
  if (input == '0') {
    l();
    l();
    l();
    l();
    l();
  }
  if (input == '1') {
    s();
    l();
    l();
    l();
    l();
  }
  if (input == '2') {
    s();
    s();
    l();
    l();
    l();
  }
  if (input == '3') {
    s();
    s();
    s();
    l();
    l();
  }
  if (input == '4') {
    s();
    s();
    s();
    s();
    l();
  }
  if (input == '5') {
    s();
    s();
    s();
    s();
    s();
  }
  if (input == '6') {
    l();
    s();
    s();
    s();
    s();
  }
  if (input == '7') {
    l();
    l();
    s();
    s();
    s();
  }
  if (input == '8') {
    l();
    l();
    l();
    s();
    s();
  }
  if (input == '9') {
    l();
    l();
    l();
    l();
    s();
  }
}
