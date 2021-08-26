#define firstDigit 2
#define secondDigit 3
#define thirdDigit 4
#define bottomLeft 5
#define bottom 6
#define bottomRight 7
#define middle 8
#define top 9
#define topRight 10
#define topLeft 11

const int zero[6] = {top, topLeft, topRight, bottomLeft, bottomRight, bottom};
#define zeroSize 6
const int one[2] = {bottomLeft, topLeft};
#define oneSize 2
const int two[5] = {top, topRight, middle, bottomLeft, bottom};
#define twoSize 5
const int three[5] = {top, topRight, middle, bottomRight, bottom};
#define threeSize 5
const int four[4] = {topLeft, middle, topRight, bottomRight};
#define fourSize 4
const int five[5] = {top, topLeft, middle, bottomRight, bottom};
#define fiveSize 5
const int six[5] = {topLeft, middle, bottomRight, bottom, bottomLeft};
#define sixSize 5
const int seven[3] = {top, topRight, bottomRight};
#define sevenSize 3
const int eight[7] = {top, topLeft, topRight, middle, bottomLeft, bottomRight, bottom};
#define eightSize 7
const int nine[5] = {top, topLeft, topRight, middle, bottomRight};
#define nineSize 5

char nums[3];
int j = 0;
unsigned long previousMillis = 0;
#define holdTime 1000

void setup() {
  for (int i = firstDigit; i <= thirdDigit; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  for (int i = bottomLeft; i <= topLeft; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0 || millis() - previousMillis >= holdTime) {
    reset();
    memset(nums,'a',sizeof(nums));
  }
  while (Serial.available() > 0) {
    nums[j] = Serial.read();
    j++;
    previousMillis = millis();
  }
  displayNumber(nums, sizeof(nums) / sizeof(nums[0]));
}

void displayNumber(char input[], int arrSize) {
  for (int i = 0; i < arrSize; i++) {
    switch (input[i]) {
      case '0':
        writeNumber(zero, zeroSize, i + 2);
        break;
      case '1':
        writeNumber(one, oneSize, i + 2);
        break;
      case '2':
        writeNumber(two, twoSize, i + 2);
        break;
      case '3':
        writeNumber(three, threeSize, i + 2);
        break;
      case '4':
        writeNumber(four, fourSize, i + 2);
        break;
      case '5':
        writeNumber(five, fiveSize, i + 2);
        break;
      case '6':
        writeNumber(six, sixSize, i + 2);
        break;
      case '7':
        writeNumber(seven, sevenSize, i + 2);
        break;
      case '8':
        writeNumber(eight, eightSize, i + 2);
        break;
      case '9':
        writeNumber(nine, nineSize, i + 2);
        break;
    }
    delay(1);
    reset();
  }
  j = 0;
}

void writeNumber(int num[], int numSize, int digit) {

  digitalWrite(digit, HIGH);

  for (int i = 0; i < numSize; i++) {
    digitalWrite(num[i], LOW);
  }
}

void reset() {
  for (int i = bottomLeft; i <= topLeft; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = firstDigit; i <= thirdDigit; i++) {
    digitalWrite(i, LOW);
  }
}
