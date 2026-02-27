#include <Keypad.h>

// 7-segment display pins (common cathode)
const int segA = 2;
const int segB = 3;
const int segC = 4;
const int segD = 5;
const int segE = 6;
const int segF = 7;
const int segG = 8;

// Optional DP (not used)
const int segDP = 9;

// Segment pins array
int segPins[] = {segA, segB, segC, segD, segE, segF, segG};

// 4x4 Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};  // Adjust if needed
byte colPins[COLS] = {10, 11, 12, 13};  // Adjust if needed

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Digit segment patterns (common cathode, LOW = ON)
byte digitPatterns[10][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0}  // 9
};

void setup() {
  // Initialize segment pins
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
    digitalWrite(segPins[i], HIGH); // OFF for common cathode
  }

  pinMode(segDP, OUTPUT);
  digitalWrite(segDP, HIGH); // DP off
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key && key >= '0' && key <= '9') {
    Serial.print("Key Pressed: ");
    Serial.println(key);
    int digit = key - '0';
    displayDigit(digit);
  }
}

// Function to display digit 0-9
void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digitPatterns[digit][i] ? LOW : HIGH);
  }
}
