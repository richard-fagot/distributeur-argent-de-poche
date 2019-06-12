#include <Keypad.h> //Keypad by Mark Stanley, Alexander Brevig Version 3.1.1
#include <Servo.h>  // Librairie par défaut
#include <string.h>
#include <Wire.h>
#include <ds3231.h> //ds3231FS by Petre Rodan
#include "PocketMoneyDistributor.h"
#include "Displayer.h"
#include "SL44x2.h" //https://sourceforge.net/p/arduinosclib/wiki/Home/
#include "StateMachineEnum.h"
ts timeDetails;


///////////////////////////////////////////////////////////////////////////////
//
//  Paramètres du lecteur de carte à puce.
//
///////////////////////////////////////////////////////////////////////////////

const uint8_t SC_C2_RST = A1;
const uint8_t SC_C1_VCC = A0;
const uint8_t SC_C7_IO = A2;
const uint8_t SC_C2_CLK = 9;
const uint8_t SC_SWITCH_CARD_PRESENT= 13;
const boolean SC_SWITCH_CARD_PRESENT_INVERT = false;
SL44x2 sl44x2(SC_C7_IO, SC_C2_RST, SC_C1_VCC, SC_SWITCH_CARD_PRESENT, SC_C2_CLK, SC_SWITCH_CARD_PRESENT_INVERT);

///////////////////////////////////////////////////////////////////////////////
//
// Données de la carte à puce.
//
///////////////////////////////////////////////////////////////////////////////

char name[20+1]; // 20 caractères max pour le prénom
unsigned int code;
unsigned int pocketMoney;


///////////////////////////////////////////////////////////////////////////////
//
// États de l'automate fini.
//
///////////////////////////////////////////////////////////////////////////////



state STATE;
state nextState;
unsigned long delayInterval;
unsigned long previousMillis;

///////////////////////////////////////////////////////////////////////////////
//
// Définition des paramètres du clavier.
//
///////////////////////////////////////////////////////////////////////////////

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


//Distributor distributor;
PocketMoneyDistributor distributor;

Displayer displayer;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////** PROGRAMME ** //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void setup() {
  
  Wire.begin(); //start i2c (required for connection)
  DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)
  
  displayer.initialize();
  Serial.begin(9600);

  // Crée un distributeur contenant deux types de pièces :
  // - des pièces de 2€ dont le servo est relié à la broche 10 ;
  // - des pièces de 1€ dont le servo est relié à la broche 11.
  distributor.setup(3, 3, 200, 5, 100, 6, 50);
  distributor.initialize();

  STATE = BEGIN;
  
  // Tests unitaires
  //testSuiteDistributionSequence();
}



void loop() {
  
  // Si la carte est retirée en dehors du process nominal,
  // il est possible que les données n'aient pas été récupérées
  // alors on dit simplement au revoir et on revient au début du process;
  /*
  if(!sl44x2.cardInserted() && WAIT_FOR_CARD_REMOVE != STATE) {
    STATE = UNEXPECTED_CARD_REMOVE;
    Serial.println("Unexpected card removed");
  }
  */

  switch(STATE) {

    case BEGIN:
      displayer.clear();
    	displayer.addLine("Insere ta carte");
    	STATE = WAIT_FOR_CARD;
    	break;
    
    case WAIT_FOR_CARD:
     	if(sl44x2.cardInserted()) {
        	STATE = COLLECT_CARD_DATA;
     	}
    	break;
    
    case COLLECT_CARD_DATA:
      if (sl44x2.cardReady()) {
        collectSmartcardData();
        DS3231_get(&timeDetails);
        if(timeDetails.wday != 9) {
          STATE = SAY_HELLO;  
        } else {
          STATE = NOT_THE_GOOD_DAY;
        } 
      }
    	break;
    
    case SAY_HELLO: 
    {
      displayer.clear();
      displayer.addLine("Bonjour");
      displayer.addLine(name);
      displayer.addLine("Entre ton code");
      userTypedCode = 0;
    	STATE = CAPTURE_USER_ENTRIES;
    }
      break;
    
    case NOT_THE_GOOD_DAY:
    {
      displayer.clear();
      displayer.addLine("Retire ta carte.");
      displayer.addLine("Ce n'est pas le bon");
      char msg[21] = "jour ";
      strcat(msg, name);
      displayer.addLine(msg);
      displayer.addLine("Reviens samedi !");
      //waitForCardRemoveThenGo(BEGIN);
      STATE = WAIT_FOR_CARD_REMOVE;
      nextState = BEGIN;
    }
      break;
    
    case CAPTURE_USER_ENTRIES:
    	captureAndProcessUserEntries();
    	break;
    
    case GOOD_CODE:
      displayer.clear();
      displayer.addLine("Code bon");
      displayer.addLine("Retire ta carte");
      //waitForCardRemoveThenGo(DISPLAY_DISTRIBUTION);
      STATE = WAIT_FOR_CARD_REMOVE;
      nextState = DISPLAY_DISTRIBUTION;
    	break;
    
    case WRONG_CODE:
      displayer.clear();
    	displayer.addLine("Code Faux");
      //waitThenGo(5000, SAY_HELLO);
      delayInterval = 5000;
      nextState = SAY_HELLO;
      STATE = WAIT;
      previousMillis = millis();
    	break;
    
    case WAIT_FOR_CARD_REMOVE:
      Serial.println("Wait for card remove");
    	if(!sl44x2.cardInserted()) {
        sl44x2.cardRemoved();
        String s = "go to ";
        s.concat(nextState==DISPLAY_DISTRIBUTION?"go to display distrib":"oups");
          Serial.println( s);
          STATE = nextState;
    	}
    	break;
    
    case DISPLAY_DISTRIBUTION:
    {
      displayer.clear();
      displayer.addLine("Distribution de");
      char totalToDistribute = pocketMoney / 100;
      byte cents = (pocketMoney - totalToDistribute * 100) / 10;
      char msg[21] = {(char)('0' + totalToDistribute), ',', (char)('0' + cents), '0', '\0'};
      strcat(msg, " euro(s)");
      displayer.addLine(msg);
      STATE = DISTRIBUTION;
    }
      break;
    
    case DISTRIBUTION:
    {
      distributor.distribute(pocketMoney);
      if(distributor.hasFinished()) {
        STATE = SAY_GOODBYE;  
      }
    }
    	break;
    
    case SAY_GOODBYE:
      displayer.clear();
      displayer.addLine("Au revoir");
      displayer.addLine(name);
      //waitThenGo(2000, BEGIN);
      delayInterval = 2000;
      nextState = BEGIN;
      STATE = WAIT;
      previousMillis = millis();
      break;
    case WAIT:
      if(millis() - previousMillis > delayInterval) {
        STATE = nextState;
      }
      break;

    case UNEXPECTED_CARD_REMOVE:
      displayer.clear();
      displayer.addLine("Au revoir");
      //waitThenGo(2000, BEGIN);
      delayInterval = 2000;
      nextState = BEGIN;
      STATE = WAIT;
      previousMillis = millis();
      break;

    default: break;
  }

}

int toInt(char c) {
  return (int)(c - 48);
}

void waitForCardRemoveThenGo(state stateToGOAfterCardRemoved); // nécessaire car le compilateur réorganise l'ordre de déclaration 
                                                              // de telle sorte que la déclaration de la fonction se retrouve
                                                              // avant la déclaration de l'enum.
void waitForCardRemoveThenGo(state stateToGOAfterCardRemoved) {
  STATE = WAIT_FOR_CARD_REMOVE;
  nextState = stateToGOAfterCardRemoved;
}

void waitThenGo(unsigned long interval, state stateToGOAfterWait);
void waitThenGo(unsigned long interval, state stateToGOAfterWait) {
    delayInterval = interval;
    nextState = stateToGOAfterWait;
    STATE = WAIT;
    previousMillis = millis();
}

/**
  * Fonction utilitaire pour le débogage.
  */
void log(const char* msg) {
  	char logMsg[81] = "Log - ";
    strncat(logMsg, msg, 80);
  
	  Serial.println(logMsg);  
}


/**
 * Capture les entrées saisies au clavier numérique 
 * et lance les actions correspondantes.
 */
void captureAndProcessUserEntries() {

  char customKey = customKeypad.getKey();
  
  if (customKey){
    if(customKey >= 48 && customKey <= 57) {
      userTypedCode = userTypedCode * BASE + (customKey - 48);
    }
    
    if(customKey == 'D') {
      if(userTypedCode == code) {
        STATE = GOOD_CODE;
      } else {
        STATE = WRONG_CODE;
      }
    }  
  }
  
}


/**
 * Quand l'utilisateur a saisi un code faux
 * on l'invite à recommencer.
 */
void returnToSayHelloState() {
  //:TODO
  userTypedCode = 0;
  STATE = SAY_HELLO;
}

void returnToBegin() {
  STATE = BEGIN;
}

/**
 * Récupère les informations stockées dans la carte à puce.
 * 
 */
void collectSmartcardData() {
  uint8_t  data[1+4+3+20];
  uint16_t i = sl44x2.readMainMemory(0x60, data, 28);
  
  int length = data[0];
  code = toInt(data[1])*1000 + toInt(data[2])*100 + toInt(data[3])*10 + toInt(data[4]);
  pocketMoney = toInt(data[5])*100 + toInt(data[6])*10 + toInt(data[7]);
  strncpy(name, (const char *)(data+8), length);
  name[length] = '\0';
}


/*****************************************************************************/
/********************************* MOCK **************************************/
/*****************************************************************************/
void mockCollectSmartcardData() {
  strcpy(name, "Elsa");
  code = 2436;
  pocketMoney = 350;
}

void mockCaptureAndProcessUserEntries() {
  userTypedCode = 2436;
  STATE = GOOD_CODE;
}
/*****************************************************************************/
/******************************* UNIT TESTS **********************************/
/****************************************************************************
void testSuiteDistributionSequence() {
  // Test exactly one coin, corresponding to the first in the coint list
  byte expectedResult1[] = {0, NO_COIN, NO_COIN, NO_COIN, NO_COIN};
  testDistributionSequence(200, expectedResult1, "Test exactly one coin, corresponding to the first in the coint list");
  
  // Test exactly one coin, corresponding to one not the first in the coint list
  byte expectedResult2[] = {1, NO_COIN, NO_COIN, NO_COIN, NO_COIN};
  testDistributionSequence(100, expectedResult2, "Test exactly one coin, corresponding to one not the first in the coint list");
  
  // Test coin combination
  byte expectedResult3[] = {0, 0, 1, NO_COIN, NO_COIN};
  testDistributionSequence(500, expectedResult3, "Test coin combination");
  
  // Test no combination available (because no corresponding coin found)
  byte expectedResult4[] = {NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN};
  testDistributionSequence(637, expectedResult4, "Test no combination available (because no corresponding coin found)");
  
  // Test out of bound sequence
  byte expectedResult5[] = {NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN};
  testDistributionSequence(2200, expectedResult5, "Test out of bound sequence");
}

void testDistributionSequence(int moneyAmount, byte expectedResult[], String title) {
  distributionSequence(moneyAmount);
  
  boolean success = true;
  
  for(byte i  = 0 ; i < MAX_SEQUENCE_STEPS ; i++) {
    if(servoIndexSequence[i] != expectedResult[i]) {
      success = false;
      break;
    }
  }
  
  if(!success) {
    Serial.print("FAIL - "); Serial.println(title);
    Serial.print("Expected - "); printArray(expectedResult, MAX_SEQUENCE_STEPS); Serial.println();
    Serial.print("Was      - "); printArray(servoIndexSequence, MAX_SEQUENCE_STEPS); Serial.println();
  } else {
    Serial.print("SUCCESS - "); Serial.println(title);
  }
  
}
       
 void printArray(byte array[], int size) {
   Serial.print("[");
   for(int i = 0 ; i < size-1; i++) {
     Serial.print(array[i]);
     Serial.print(", ");
   }
   Serial.print(array[size-1]);
   Serial.print("]");
 }
*/
