#include <Keypad.h> //Keypad by Mark Stanley, Alexander Brevig Version 3.1.1
#include <LiquidCrystal_PCF8574.h> // by Mathias Hertel
#include <ds3231.h> //ds3231FS by Petre Rodan

LiquidCrystal_PCF8574 lcd = LiquidCrystal_PCF8574(0x27);


  
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}};
  
byte rowPins[ROWS] = {7, 4, 2, A3}; 
byte colPins[COLS] = {12, 11, 10, 8};  

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


static const int BASE = 10; // Le code tapé au clavier est en base 10.
unsigned int userTypedCode = 0; // variable contenant le code saisi par l'utilisateur.
byte index = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(20, 4);
  lcd.setBacklight(255);
  clrscr();
  lcd.print("CODE : ");


  DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)
}

enum codeState {
  INVITE_CODE,
  GOOD,
  BAD,
  WRITING
};

codeState codeResult = WRITING;

void loop() {
  captureAndProcessUserEntries();
  switch(codeResult) {
    case INVITE_CODE:
      clrscr();
      lcd.print("CODE : ");
      codeResult = WRITING;
      break;
    case GOOD:
      clrscr();
      lcd.print("CODE BON");
      delay(2000);
      codeResult = INVITE_CODE;
      userTypedCode = 0;
      break;
    case BAD:
      clrscr();
      lcd.print("CODE FAUX");
      delay(2000);
      codeResult = INVITE_CODE;
      userTypedCode = 0;
      break;
    default:
      break;
  }
}

void clrscr() {
  lcd.setCursor(0, 0);
  lcd.clear();
}

void captureAndProcessUserEntries() {

  char customKey = customKeypad.getKey();
  
  if (customKey){
    if(customKey >= 48 && customKey <= 57) {
      userTypedCode = userTypedCode * BASE + (customKey - 48);
      lcd.setCursor(7, 0);
      lcd.print(userTypedCode);
    }
    
    if(customKey == 'D') {
      if(userTypedCode == 2436) {
        Serial.println("OK");
        codeResult = GOOD;
      } else {
        Serial.println("KO");
        codeResult = BAD;
      }
    }  

    if(customKey == 'C') {
      userTypedCode = 0;
    }
  }
  
}
