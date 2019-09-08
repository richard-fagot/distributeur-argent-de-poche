//#define DAAP_DEBUG 1

#include <Servo.h>  // Librairie par défaut
#include <string.h>
#include "PocketMoneyDistributor.h"
#include "Displayer.h"
#include "StateMachineEnum.h"
#include "SmartCard.h"
#include "MyKeypad.h"
#include "MyTime.h"
#include "DistributionAllower.h"
#include "LastDistribution.h"


void printTime(boolean = false);
SmartCard sc;
MyKeypad kp;
PocketMoneyDistributor distributor;
Displayer displayer;
MyTime time;
DistributionAllower allower;
///////////////////////////////////////////////////////////////////////////////
//
// États de l'automate fini.
//
///////////////////////////////////////////////////////////////////////////////
state STATE;
state nextState;
unsigned long delayInterval;
unsigned long previousMillis;



static const int BASE = 10; // Le code tapé au clavier est en base 10.
unsigned int userTypedCode = 0; // variable contenant le code saisi par l'utilisateur.

void(* resetFunc) (void) = 0;//declare reset function at address 0

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////** PROGRAMME ** //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void setup() {
  #ifdef DAAP_DEBUG
  Serial.begin(9600);
  Serial.println("Debug Mode");
  #endif
  
  time.setup();

  displayer.initialize();
  displayer.addLine("Initialisation");
  displayer.addLine("en cours...");

  // Crée un distributeur contenant 3 types de pièces :
  // - des pièces de 2€ dont le servo est relié à la broche 3 ;
  // - des pièces de 1€ dont le servo est relié à la broche 5 ;
  // - des pièces de 0.20€ dont le servo est relié à la broche 6 ;
  distributor.setup(3, 3, 200, 5, 100, 6, 10);
  distributor.initialize();

  STATE = BEGIN;
  
  // Tests unitaires
  //testSuiteDistributionSequence();
}



void loop() {

  #ifdef DAAP_DEBUG
  captureAndProcessUserEntries();
  #endif
  
  switch(STATE) {

    case BEGIN:
      displayer.clear();
      displayer.addEmptyLine();
      displayer.addEmptyLine();
    	displayer.addLine("Insere ta carte");
      printTime(true);
    	STATE = WAIT_FOR_CARD;
    	break;
    
    case WAIT_FOR_CARD:
      printTime();
     	if(sc.cardInserted()) {
          delay(500);
        	STATE = COLLECT_CARD_DATA;
     	}
    	break;
    
    case COLLECT_CARD_DATA:
      sc.collectSmartcardData(); // appel bloquant.
      time.refreshDate();
      if (allower.isAllowed(sc.getName(), time)) {
        STATE = SAY_HELLO;
      }
      else {
        STATE = NOT_THE_GOOD_DAY;
      }

      break;
    
    case SAY_HELLO: 
    {
      displayer.clear();
      displayer.addLine("Bonjour");
      displayer.addLine(sc.getName());
      displayer.addLine("Entre ton code");
      displayer.addLine("____");
      resetCode();
    	STATE = CAPTURE_USER_ENTRIES;
    }
      break;
    
    case NOT_THE_GOOD_DAY:
    {
      displayer.clear();
      displayer.addLine("Retire ta carte.");
      displayer.addLine("Ce n'est pas le bon");
      char msg[21] = "jour ";
      strcat(msg, sc.getName());
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
      delayInterval = 3000;
      nextState = SAY_HELLO;
      STATE = WAIT;
      previousMillis = millis();
    	break;
    
    case WAIT_FOR_CARD_REMOVE:
    	if(!sc.cardInserted()) {
        sc.cardRemoved();
        STATE = nextState;
    	}
    	break;

    case DISPLAY_DISTRIBUTION:
    {
      displayer.clear();
      displayer.addLine("Distribution de");
      unsigned int pocketMoney = sc.getPocketMoney();

      char totalToDistribute = pocketMoney / 100;
      byte cents = (pocketMoney - totalToDistribute * 100) / 10;
      char msg[21] = {(char)('0' + totalToDistribute), ',', (char)('0' + cents), '0', '\0'};
      strcat(msg, " euro(s)");
      displayer.addLine(msg);

      LastDistribution ld;
      ld.save(sc.getName(), time.getDay(), time.getMonth());

      delayInterval = 1500;
      nextState = DISTRIBUTION;;
      STATE = WAIT;
      previousMillis = millis();
    }
      break;
    
    case DISTRIBUTION:
    {
      distributor.distribute(sc.getPocketMoney());
      if(distributor.hasFinished()) {
        STATE = SAY_GOODBYE;  
      }
    }
    	break;
    
    case SAY_GOODBYE:
      displayer.clear();
      displayer.addLine("Au revoir");
      displayer.addLine(sc.getName());
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

uint8_t previousMinute = 100;

void printTime(boolean force) {
  time.refreshDate();
  if(force || (time.getMinute() != previousMinute)) {
    char timeString[21];
    time.getStringTime(timeString);
    displayer.print(0, timeString);
    previousMinute = time.getMinute();
  }
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


char star[5] = "____";// chaîne de caractère représentant à l'écran l'endroit ou vont apparaître les étoiles à chaque saisie d'une touche pour le code.
byte keyCount = 0;
/**
 * Capture les entrées saisies au clavier numérique 
 * et lance les actions correspondantes.
 */
void captureAndProcessUserEntries() {

  char customKey = kp.getKey();
  
  if (customKey){
    if(customKey >= 48 && customKey <= 57 && keyCount < 4) { // Saisie du code.
      userTypedCode = userTypedCode * BASE + (customKey - 48);
      star[keyCount] = '*';
      keyCount++;
      
      if(STATE == CAPTURE_USER_ENTRIES) displayer.print(3, star);// on affiche unniquement lorsqu'on est en train de faire la saisie du code.
    }
    
    if(customKey == 'D') { //Validation du code.
      if(sc.checkCode(userTypedCode)) {
        STATE = GOOD_CODE;
      } else {
        STATE = WRONG_CODE;
      }
    }  

    if(customKey == 'B') {
      resetFunc();
    }
    
    if(customKey == 'C') {
      STATE = SAY_HELLO;    
    }

    #ifdef DAAP_DEBUG
    if(customKey == 'A') {
      LastDistribution ld;
      switch(userTypedCode) {
        case 1:
          ld.showEEPROMContent();
          break;
       case 2:
          ld.eraseEEPROMContent();
          break;
      }
      userTypedCode=0;
    }
    #endif
  }
  
}

void resetCode() {
  userTypedCode = 0;
  keyCount = 0;
  strcpy(star, "____");
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
