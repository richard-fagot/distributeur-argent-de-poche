#include <Keypad.h> //Keypad by Mark Stanley, Alexander Brevig Version 3.1.1
#include <LiquidCrystal_PCF8574.h> // by Mathias Hertel
#include <ds3231.h> //ds3231FS by Petre Rodan
#include <Servo.h>
#include "SL44x2.h" //https://sourceforge.net/p/arduinosclib/wiki/Home/

LiquidCrystal_PCF8574 lcd = LiquidCrystal_PCF8574(0x27);


const uint8_t SC_C2_RST = A1;
const uint8_t SC_C1_VCC = A0;
const uint8_t SC_C7_IO = A2;
const uint8_t SC_C2_CLK = 9;
const uint8_t SC_SWITCH_CARD_PRESENT= 13;
const boolean SC_SWITCH_CARD_PRESENT_INVERT = false;
SL44x2 sl44x2(SC_C7_IO, SC_C2_RST, SC_C1_VCC, SC_SWITCH_CARD_PRESENT, SC_C2_CLK, SC_SWITCH_CARD_PRESENT_INVERT);

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

const byte s1_pin = 3;
const byte s2_pin = 5;
const byte s3_pin = 6;

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
  INSERT_CARD,
  WAITING_CARD,
  READ_DATA,
  INVITE_CODE,
  GOOD,
  BAD,
  WAIT_REMOVE,
  DISTRIB,
  WRITING
};

codeState codeResult = INSERT_CARD;
int secretCode = 0;
int money = 0;
char name[21] = "";

void loop() {
  captureAndProcessUserEntries();
  displayTime();
  switch(codeResult) {
    case INSERT_CARD:
      clrscr();
      lcd.setCursor(0, 2);
      lcd.print("  INSERER LA CARTE  ");
      printTime();
      codeResult = WAITING_CARD;
      break;
    case WAITING_CARD:
      if(sl44x2.cardInserted()) {
        codeResult = READ_DATA;
      }
      break;
    case READ_DATA:
      if (sl44x2.cardReady()) {
        uint8_t  data[1+4+3+20];
        uint16_t i = sl44x2.readMainMemory(0x60, data, 28);
        if (i > 0) {
          sl44x2.dumpHEX(data, i);
        }
        int length = data[0];
        secretCode = toInt(data[1])*1000 + toInt(data[2])*100 + toInt(data[3])*10 + toInt(data[4]);
        money = toInt(data[5])*100 + toInt(data[6])*10 + toInt(data[7]);
        strncpy(name, data+8, length);
        name[length] = '\0';
        codeResult = INVITE_CODE;
      }
      break;
    case INVITE_CODE:
      clrscr();
      lcd.print("CODE : ");
      lcd.setCursor(0, 3);
      lcd.print(name);
      printTime();
      codeResult = WRITING;
      break;
    case GOOD:
      clrscr();
      lcd.print("CODE BON");
      lcd.setCursor(0, 1);
      lcd.print("RETIRE LA CARTE");
      printTime();
      delay(2000);
      codeResult = WAIT_REMOVE;
      userTypedCode = 0;
      break;
    case WAIT_REMOVE:
      if(!sl44x2.cardInserted()) {
        sl44x2.cardRemoved();
        codeResult = DISTRIB;  
      }
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

int toInt(char c) {
  return (int)(c - 48);
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
      if(userTypedCode == secretCode) {
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
