#include <Keypad.h> //Keypad by Mark Stanley, Alexander Brevig Version 3.1.1
#include <Servo.h>  // Librairie par défaut
#include <string.h>
#include <Wire.h>
#include <ds3231.h> //ds3231FS by Petre Rodan
#include "PocketMoneyDistributor.h"
#include "Displayer.h"

ts timeDetails;

//////////////////////////////////////////////////////////////

void display(String msg);
void display(String msg, int duration, void (*callback)());

///////////////////////////////////////////////////////////////////////////////
//
//  Paramètres du lecteur de carte à puce.
//
///////////////////////////////////////////////////////////////////////////////

static const byte CARD_DETECTOR_PIN = 2; // Interupteur de détection de carte.


///////////////////////////////////////////////////////////////////////////////
//
// Paramètres de la détection d'insertion et de retrait de la carte à puce.
//
///////////////////////////////////////////////////////////////////////////////

static const byte CARD_DETECTED = LOW; // État de la broche de détection de carte lorsqu'une carte est présente.
static const byte NO_CARD_DETECTED = HIGH; // État de la broche de détection de carte en l'absence de carte.

boolean previousCardState = NO_CARD_DETECTED; // Permet de détecter un changement
                                              // d'état de présence de la carte.


///////////////////////////////////////////////////////////////////////////////
//
// Données de la carte à puce.
//
///////////////////////////////////////////////////////////////////////////////

String name;
unsigned int code;
unsigned int pocketMoney;


///////////////////////////////////////////////////////////////////////////////
//
// États de l'automate fini.
//
///////////////////////////////////////////////////////////////////////////////

enum state {
  BEGIN,
  WAIT_FOR_CARD,   
  COLLECT_CARD_DATA,
  SAY_HELLO,
  NOT_THE_GOOD_DAY,
  CAPTURE_USER_ENTRIES,
  GOOD_CODE,
  WRONG_CODE,
  WAIT_FOR_CARD_REMOVE,
  DISPLAY_DISTRIBUTION,
  DISTRIBUTION,
  WAIT
};

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
  
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};  

//Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


static const int BASE = 10; // Le code tapé au clavier est en base 10.
int userTypedCode = 0; // variable contenant le code saisi par l'utilisateur.


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

  pinMode(CARD_DETECTOR_PIN, INPUT_PULLUP);

  // Crée un distributeur contenant deux types de pièces :
  // - des pièces de 2€ dont le servo est relié à la broche 10 ;
  // - des pièces de 1€ dont le servo est relié à la broche 11.
  distributor.setup(2, 9, 200, 3, 100);
  distributor.initialize();

  STATE = BEGIN;
  
  // Tests unitaires
  //testSuiteDistributionSequence();
}



void loop() {
  
  switch(STATE) {
    case BEGIN:
      displayer.clear();
    	displayer.addLine("Insere ta carte");
    	STATE = WAIT_FOR_CARD;
    	break;
    case WAIT_FOR_CARD:
     	if(isCardInserted()) {
        	STATE = COLLECT_CARD_DATA;
     	}
    	break;
    case COLLECT_CARD_DATA:
    	collectSmartcardData();
      DS3231_get(&timeDetails);
      if(timeDetails.wday == 6) {
        STATE = SAY_HELLO;  
      } else {
        STATE = NOT_THE_GOOD_DAY;
      }
    	
    	break;
    case SAY_HELLO: 
    {
      displayer.clear();
      displayer.addLine("Bonjour");
      displayer.addLine(name.c_str());
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
      String msg = "jour ";
      msg.concat(name);
      displayer.addLine(msg.c_str());
      displayer.addLine("Reviens samedi !");
      waitForCardRemoveThenGo(BEGIN);
    }
      break;
    case CAPTURE_USER_ENTRIES:
      mockCaptureAndProcessUserEntries();
    	//captureAndProcessUserEntries();
    	break;
    case GOOD_CODE:
      displayer.clear();
      displayer.addLine("Code bon");
      displayer.addLine("Retire ta carte");
      waitForCardRemoveThenGo(DISPLAY_DISTRIBUTION);
    	break;
    case WRONG_CODE:
      displayer.clear();
    	displayer.addLine("Code Faux");
      waitThenGo(5000, SAY_HELLO);
    	break;
    case WAIT_FOR_CARD_REMOVE:
    	if(isCardRemoved()) {
          STATE = nextState;
    	}
    	break;
    case DISPLAY_DISTRIBUTION:
    {
      displayer.clear();
      displayer.addLine("Distribution de");
      String msg = "";
      msg.concat(pocketMoney / 100);
      msg.concat(" euro(s)");
      displayer.addLine(msg.c_str());
      STATE = DISTRIBUTION;
    }
      break;
    case DISTRIBUTION:
    {
      distributor.distribute(pocketMoney);
      if(distributor.hasFinished()) {
        displayer.clear();
        displayer.addLine("Au revoir");
        displayer.addLine(name.c_str());
        waitThenGo(2000, BEGIN);
      }
    }
    	break;
    case WAIT:
      if(millis() - previousMillis > delayInterval) {
        STATE = nextState;
      }
    default: break;
  }

}

void waitForCardRemoveThenGo(state stateToGOAfterCardRemoved) {
  STATE = WAIT_FOR_CARD_REMOVE;
  nextState = stateToGOAfterCardRemoved;
}

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
  	String logMsg = "Log - ";
  	logMsg.concat(msg);
  
	  Serial.println(logMsg);  
}


/**
  * Affiche le message sur l'écran LCD
  */
void display(const char* msg) {
  //:TODO
  Serial.println(msg);
  displayer.clear();
  displayer.addLine(msg);
}

void display(const char* msg, int duration, void (*callback)()) {
  display(msg);
  delay(duration);
  (*callback)();
}



/**
  * Detecte l'insertion d'une carte.
  */
boolean isCardInserted() {
   if(CARD_DETECTED == digitalRead(CARD_DETECTOR_PIN) && NO_CARD_DETECTED == previousCardState) {
     previousCardState = CARD_DETECTED;
     return true;
  }
  
  return false;
}

/**
  * Detecte le retrait d'une carte.
  */
boolean isCardRemoved() {
   if(NO_CARD_DETECTED == digitalRead(CARD_DETECTOR_PIN) && CARD_DETECTED == previousCardState) {
     previousCardState = NO_CARD_DETECTED;
     return true;
  }
  
  return false;
}

/**
 * Capture les entrées saisies au clavier numérique 
 * et lance les actions correspondantes.
 
void captureAndProcessUserEntries() {

  char customKey = customKeypad.getKey();
  
  if (customKey){
    if(customKey >= 48 && customKey <= 57) {
      userTypedCode = userTypedCode * BASE + (customKey - 48);
      log(userTypedCode);
    }
    
    if(customKey == '#') {
      if(userTypedCode == code) {
        STATE = GOOD_CODE;
      } else {
        STATE = WRONG_CODE;
      }
    }  
  }
  
}
*/

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
  //:TODO : get card data
  mockCollectSmartcardData();
  //
}


/*****************************************************************************/
/********************************* MOCK **************************************/
/*****************************************************************************/
void mockCollectSmartcardData() {
  name = "Elsa";
  code = 2436;
  pocketMoney = 300;
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
