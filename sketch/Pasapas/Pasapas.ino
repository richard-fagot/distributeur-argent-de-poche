#include <Keypad.h> //Keypad by Mark Stanley, Alexander Brevig Version 3.1.1
#include <LiquidCrystal_PCF8574.h> // by Mathias Hertel
#include <ds3231.h> //ds3231FS by Petre Rodan
#include <Servo.h>


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


static const byte BASE = 10; // Le code tapé au clavier est en base 10.
unsigned int userTypedCode = 0; // variable contenant le code saisi par l'utilisateur.
byte index = 7;


Servo s1, s2, s3;

const byte s1_pin = 9;
const byte s2_pin = 6;
const byte s3_pin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  lcd.begin(20, 4);
  lcd.setBacklight(255);
  clrscr();


  DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)

  moveServos(180);
}

enum codeState {
  INVITE_CODE,
  GOOD,
  BAD,
  DISTRIB,
  WRITING
};

codeState codeResult = INVITE_CODE;

void loop() {
  captureAndProcessUserEntries();
  displayTime();
  switch(codeResult) {
    case INVITE_CODE:
      clrscr();
      lcd.print("CODE : ");
      printTime();
      codeResult = WRITING;
      break;
    case GOOD:
      clrscr();
      lcd.print("CODE BON");
      printTime();
      delay(2000);
      codeResult = DISTRIB;
      userTypedCode = 0;
      break;
    case DISTRIB:
      distribute();
      codeResult = INVITE_CODE;
      break;
    case BAD:
      clrscr();
      lcd.print("CODE FAUX");
      printTime();
      delay(2000);
      codeResult = INVITE_CODE;
      userTypedCode = 0;
      break;
    default:
      break;
  }
}

void moveServos(byte direction) {
  s1.attach(s1_pin);
  s1.write(direction);
  s2.attach(s2_pin);
  s2.write(direction);
  s3.attach(s3_pin);
  s3.write(direction);

  delay(2000);
  s1.detach();
  s2.detach();
  s3.detach();  
}

void distribute() {
  moveServos(0);
  moveServos(180);
}

ts timeDetails;
byte minute = 0;
void displayTime() {
  DS3231_get(&timeDetails);
  byte tdMin = (byte)timeDetails.min; 
  if(tdMin != minute) {
    printTime();
  }
    
}

void printTime() {
  DS3231_get(&timeDetails);  
  
  uint8_t tdH = timeDetails.hour;
  byte tdMin = (byte)timeDetails.min;
  
  byte a = tdH / 10 ;
  byte b = tdH - a * 10;
  byte c = tdMin / 10;
  byte d = tdMin - c * 10; 
  char s[6] = {'0' + a, '0' + b, ':', '0' + c, '0' + d, '\0'};

  lcd.setCursor(15,0);
  lcd.print(s);  
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
