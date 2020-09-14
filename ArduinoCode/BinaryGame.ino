// include the library code:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int Pin0 = 7;      // Binary number 2^0 or 1
const int Pin1 = 8;      // Binary number 2^1 or 2
const int Pin2 = 9;      // Binary number 2^2 or 4
const int Pin3 = 10;     // Binary number 2^3 or 8
const int Pin4 = 11;     // Binary number 2^4 or 16
const int Pin5 = 12;     // Binary number 2^5 or 32
const int Pin6 = A0;     // Binary number 2^6 or 64
const int Pin7 = A1;     // Binary number 2^7 or 128
const int easyMode = A2; // Easy mode is 0-15, Hard is 0-255

int BinaryValue; // Value for adding up numbers to compare to random number

int correctNumber = 0; // Flag to see if the number was correct
int wrongNumber = 0;   // Flag to see if the number was wrong

const int buzzer = 3; //Buzzer pin
int freq;             //frequency out

const int buttonPin = 2;      // the number of the pushbutton pin
const int buttonLedRed = 4;   // the number of the pushbutton LED pin
const int buttonLedGreen = 5; // the number of the pushbutton LED pin
const int buttonLedBlue = 6;  // the number of the pushbutton LED pin

int buttonState; // variable for reading the pushbutton status
long randNumber; // variable for the random number

void setup()
{

  lcd.init(); // set up the LCD's number of columns and rows
  lcd.backlight();

  pinMode(Pin0, INPUT_PULLUP);
  pinMode(Pin1, INPUT_PULLUP);
  pinMode(Pin2, INPUT_PULLUP);
  pinMode(Pin3, INPUT_PULLUP);
  pinMode(Pin4, INPUT_PULLUP);
  pinMode(Pin5, INPUT_PULLUP);
  pinMode(Pin6, INPUT_PULLUP);
  pinMode(Pin7, INPUT_PULLUP);

  pinMode(easyMode, INPUT_PULLUP);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLedRed, OUTPUT);
  pinMode(buttonLedGreen, OUTPUT);
  pinMode(buttonLedBlue, OUTPUT);

  pinMode(buzzer, OUTPUT); // Set buzzer pin as OUTPUT

  // if analog input pin 3 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(A3));

  if (digitalRead(easyMode) == HIGH)
  {
    randNumber = random(0, 15);
  }
  else
  {
    randNumber = random(0, 255);
  }

  // Print a message to the LCD.
  lcd.print("Your number is");

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);

  lcd.print(randNumber); // Print the random number
  digitalWrite(buttonLedBlue, HIGH);
}

void checkNumber() // Check switches for correct number
{
  if (digitalRead(Pin0) == LOW)
  {
    BinaryValue = 1;
  }
  else
  {
    BinaryValue = 0;
  }

  if (digitalRead(Pin1) == LOW)
  {
    BinaryValue = BinaryValue + 2;
  }

  if (digitalRead(Pin2) == LOW)
  {
    BinaryValue = BinaryValue + 4;
  }

  if (digitalRead(Pin3) == LOW)
  {
    BinaryValue = BinaryValue + 8;
  }

  if (digitalRead(Pin4) == LOW)
  {
    BinaryValue = BinaryValue + 16;
  }

  if (digitalRead(Pin5) == LOW)
  {
    BinaryValue = BinaryValue + 32;
  }

  if (digitalRead(Pin6) == LOW)
  {
    BinaryValue = BinaryValue + 64;
  }

  if (digitalRead(Pin7) == LOW)
  {
    BinaryValue = BinaryValue + 128;
  }

  if (BinaryValue == randNumber) // Check if switches match random number
  {
    correctNumber = 1;
  }
  else
  {
    wrongNumber = 1;
  }
}

void printBinary() // Displays status of switches
{
  if (digitalRead(Pin7) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }

  if (digitalRead(Pin6) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }
  if (digitalRead(Pin5) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }
  if (digitalRead(Pin4) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }
  lcd.print(" ");
  if (digitalRead(Pin3) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }
  if (digitalRead(Pin2) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }
  if (digitalRead(Pin1) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }
  if (digitalRead(Pin0) == HIGH)
  {
    lcd.print("0");
  }
  else
  {
    lcd.print("1");
  }
}

void loop()
{

  attachInterrupt(digitalPinToInterrupt(buttonPin), checkNumber, FALLING); // Wait for pushbutton to be pressed, when pressed check to see if correct number is inputted

  lcd.setCursor(7, 1);

  printBinary(); // Display status of switches

  if (wrongNumber == 1)
  {
    digitalWrite(buttonLedBlue, LOW);
    digitalWrite(buttonLedRed, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Try again");
    lcd.setCursor(0, 1);
    lcd.print(randNumber);
    tone(buzzer, 200); // Play wrong answer tone
    delay(400);
    noTone(buzzer); // Stop sound...
    wrongNumber = 0;
    correctNumber = 0;
    digitalWrite(buttonLedRed, LOW);
    digitalWrite(buttonLedBlue, HIGH);
  }

  if (correctNumber == 1)
  {
    digitalWrite(buttonLedBlue, LOW);
    digitalWrite(buttonLedGreen, HIGH);
    tone(buzzer, 600); // Play correct answer tone
    delay(100);
    tone(buzzer, 1000);
    delay(100);
    tone(buzzer, 800);
    delay(100);
    noTone(buzzer); // Stop sound...
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Correct!");
    lcd.setCursor(0, 1);
    lcd.print(randNumber);
    lcd.print(" is ");

    printBinary(); // Display status of switches

    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Your number is");
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);

    if (digitalRead(easyMode) == HIGH)
    {
      randNumber = random(0, 15);
    }
    else
    {
      randNumber = random(0, 255);
    }

    lcd.print(randNumber);

    correctNumber = 0;
    wrongNumber = 0;
    digitalWrite(buttonLedGreen, LOW);
    digitalWrite(buttonLedBlue, HIGH);
  }
}
