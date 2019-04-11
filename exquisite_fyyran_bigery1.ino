
#include <LiquidCrystal.h>
#include <Keypad.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const byte ROWS = 4;
const byte COLS = 4;

//Initialising keys
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 6, 9};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


// Global Variables

int passcode[] = {1, 2, 3 ,4};

int Success = 0;
int line = 0;
int attemptnum = 0;
int entrylocation[] = {0, 0, 0, 0};
const char* wordslocation[] = {"1st", "2nd", "3rd", "4th"};
int clearline = 0;




void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Print a message to the LCD.
  lcd.print("4 digit code:"); 
  
}

void loop() {
  Success = 0;
  if (clearline == 1){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("4 digit code:");
  clearline = 0;
  }
  
  // set the cursor to column 0, line 1
  lcd.setCursor(line, 1);
  // Keypad print code
  char customkey = customKeypad.getKey();
  lcd.blink();
  // Print Keypad press
  if (customkey){
    lcd.print(customkey);
    Serial.println(customkey);
    // Convert from ASCII to number
    int alpha = customkey - 48;
    entrylocation[line] = alpha;
    // Moves the cursor over by one when the loop starts again
    line = line + 1;
  }
  
// Checks for correct Answer
  if (line==4){
  for (int i = 0;  i <= 4; i++)
  {
  if (entrylocation[i] == passcode[i]) 
    {
    Success = (Success + 1);
    if (Success == 4){
      lcd.noBlink();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOU HAVE WON");
      lcd.setCursor(0, 1);
      lcd.print("Congragulations");
      delay(10000); }
   
    }
  }
  }
  
  Serial.println("Success numer is");
  Serial.println(Success);
  
 
  // Tells the user they have failed at entering the correct code
  if (line == 4){
    attemptnum = attemptnum + 1;
    for (int count = 0; count <=5; count++)
    {
      lcd.noBlink();
      lcd.setCursor(0, 1);
      lcd.print("wrong");
      delay(200);
      lcd.setCursor(0, 1);
      lcd.print("       ");
      delay(200);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(4-attemptnum);
      lcd.print(" attempts left");
      line = 0;
      clearline = 1;
    }
  if (attemptnum == 4){
      lcd.noBlink();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("YOU HAVE FAILED");
      lcd.setCursor(0, 1);
      lcd.print("GAME OVER");
      delay(5000);
    }
  for (int i = 0; i <=4; i++) {
    if (entrylocation[i] == passcode[i])
    {
      lcd.setCursor(0,0);
      lcd.print("The ");
      lcd.print(wordslocation[i]);
      lcd.print(" digit   ");
      lcd.setCursor(0,1);
      lcd.print("is correct  ");
      Serial.print(wordslocation[1]);
      delay(4000);
      clearline = 1;
    }
  }
  }
}
 