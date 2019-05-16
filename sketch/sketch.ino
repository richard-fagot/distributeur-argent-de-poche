#include <Keypad.h> //Keypad by Mark Stanley, Alexander Brevig Version 3.1.1
#include <Servo.h>  // Librairie par défaut

void display(String msg);
void display(String msg, int duration, void (*callback)());

///////////////////////////////////////////////////////////////////////////////
//
//  Paramètres du lecteur de carte à puce.
//
///////////////////////////////////////////////////////////////////////////////

static const byte CARD_DETECTOR_PIN = 13; // Interupteur de détection de carte.


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
  CAPTURE_USER_ENTRIES,
  GOOD_CODE,
  WRONG_CODE,
  WAIT_FOR_CARD_REMOVE,
  DISTRIBUTION
};

state STATE;


///////////////////////////////////////////////////////////////////////////////
//
// Définition des paramètres de distribution des pièces
//
///////////////////////////////////////////////////////////////////////////////

static const byte NUMBER_OF_COIN_TYPES = 2; // Nombre de type de pièces 
                                            // disponibles dans le distributeur.

static const byte coinsValues[] = {200,100}; // Liste des valeurs en centimes des
                                             // pièces disponibles dans le 
                                             // distributeur.

static const byte NO_COIN = 255; // Constante représentant la fin de séquence de
                                 // distribution. On laplace dans la variable
                                 // servoIndexSequence.

static const byte MAX_SEQUENCE_STEPS = 5; // Nombre maximal d'étapes dans la séquence de
                                          // distribution.

byte servoIndexSequence[MAX_SEQUENCE_STEPS]; // la séquence contient les index des 
                                             // servos ::servos[] correspondant
                                             // aux pièces décrites dans coinsValue.

Servo servo_2euro_pin10;
Servo servo_1euro_pin11;

Servo servos[] = {servo_2euro_pin10
                , servo_1euro_pin11}; // l'ordre des servos doit correspondre à
                                      // l'ordre des pièces dans ::coinsValues[]

byte servoPins[] = {10, 11};


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

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


static const int BASE = 10; // Le code tapé au clavier est en base 10.
int userTypedCode = 0; // variable contenant le code saisi par l'utilisateur.


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////** PROGRAMME ** //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);

  pinMode(CARD_DETECTOR_PIN, INPUT);
  
  initializeServos();
  
  STATE = BEGIN;
  
  // Tests unitaires
  //testSuiteDistributionSequence();
}



void loop() {
  
  switch(STATE) {
    case BEGIN:
    	display("Insère ta carte");
    	STATE = WAIT_FOR_CARD;
    	break;
    case WAIT_FOR_CARD:
     	if(isCardInserted()) {
        	STATE = COLLECT_CARD_DATA;
          	log("Une carte a été insérée");
      	}
    	break;
    case COLLECT_CARD_DATA:
    	collectSmartcardData();
    	STATE = SAY_HELLO;
    	break;
    case SAY_HELLO:
    	display("Bonjour " + name + ", entre ton code");
    	STATE = CAPTURE_USER_ENTRIES;
    case CAPTURE_USER_ENTRIES:
    	captureAndProcessUserEntries();
    	break;
    case GOOD_CODE:
    	display("Code bon, retire ta carte");
    	STATE = WAIT_FOR_CARD_REMOVE;
    	break;
    case WRONG_CODE:
    	display("Code Faux", 2000, returnToSayHelloState);
    	break;
    case WAIT_FOR_CARD_REMOVE:
    	if(isCardRemoved()) {
          	String msg = "Distribution de ";
          	msg.concat(pocketMoney / 100);
          	msg.concat(" €");
      		display(msg);
          	STATE = DISTRIBUTION;
    	}
    	break;
    case DISTRIBUTION:
    	giveMyMoney();
    	display("Au revoir " + name);
    	delay(2000);
    	STATE = BEGIN;
    	break;
    default: break;
  }

}

/**
  * Fonction utilitaire pour le débogage.
  */
void log(String msg) {
  	String logMsg = "Log - ";
  	logMsg.concat(msg);
  
	Serial.println(logMsg);  
}


/**
  * Affiche le message sur l'écran LCD
  */
void display(String msg) {
  //:TODO
  Serial.println(msg);
}

void display(String msg, int duration, void (*callback)()) {
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
  * Configuration et mise en position initiale des servos.
  */
void initializeServos() {
  for(int servoIndex = 0 ; servoIndex < NUMBER_OF_COIN_TYPES ; servoIndex++) {
    servos[servoIndex].attach(servoPins[servoIndex]);
    servos[servoIndex].write(0);
  }
  
  delay(3000);
  
  for(int servoIndex = 0 ; servoIndex < NUMBER_OF_COIN_TYPES ; servoIndex++) {
    servos[servoIndex].detach();
  } // Le fait de détacher les servos permet de les laisser dans leur position
    // sans avoir le bruit qu'ils font quand ils essaient de la maintenir.
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
      log(String(userTypedCode));
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

/**
  * Distribue les pièces dans la quantité indiquée
  * dans la carte.
  */
void giveMyMoney() {
  distributionSequence(pocketMoney);    
  startDistributionSequence(); 
}

/**
  * Détermine la séquence de distribution des pièces
  * dans un tableau du type [pièce de 2€, pièce de 2€, pièce de 1€, RIEN, RIEN]
  */
void distributionSequence(int valueToDistribute) {
  byte sequenceIndex = 0;
  int remainingValueToDistribute = valueToDistribute;
  byte coinValueIndex = 0;
  byte coinsCount = 0;
  
  // Initialisation avec une séquence vide
  emptySequence(servoIndexSequence);
  
  while(remainingValueToDistribute != 0) {
    
    // Si il n'y a pas suffisamment de type de valeurs faciales
    // pour faire le montant à distribuer, on vide la séquence
    // et on s'arrête ==> pas de distribution de pièce.
    if(coinValueIndex >= NUMBER_OF_COIN_TYPES) {
      emptySequence(servoIndexSequence);
      return;
    }
    
    // Combien de pièces de la valeur faciale courante y-a-t'il
    // dans ce qu'il reste à distribuer ?
    coinsCount = remainingValueToDistribute / coinsValues[coinValueIndex];
      
    for(byte i = 0 ; i < coinsCount ; i++) {
      servoIndexSequence[sequenceIndex] = coinValueIndex;
      sequenceIndex++;
      
      if(sequenceIndex >= MAX_SEQUENCE_STEPS) {
        emptySequence(servoIndexSequence);
        return;
      }
    }

    remainingValueToDistribute -= coinsValues[coinValueIndex]*coinsCount;
    coinValueIndex++;
      
  }
}

/**
  * Exécute la sequence de distribution en activant les
  * servos correspondants les uns après les autres.
  */
void startDistributionSequence() {
  byte servoIndex;
  for(int sequenceIndex = 0 ; sequenceIndex < MAX_SEQUENCE_STEPS ; sequenceIndex++) {
    servoIndex = servoIndexSequence[sequenceIndex];
    Serial.println(servoIndex);
    
    // Détection de la fin de la séquence si elle ne rempli pas tout le tableau
    if(NO_COIN == servoIndex) break;
    dropCoin(servoIndex);
  }
}

/**
 * Lance les actions sur les servos pour faire tomber la pièce.
 */
void dropCoin(byte servoIndex) {
  Servo servo = servos[servoIndex];
  byte servoPin = servoPins[servoIndex];
  
  servo.attach(servoPin);
  
  servo.write(180);
  delay(3000);
  servo.write(0);
  delay(3000);
  
  servo.detach();
}


/**
  * Initialise un tableau de séquence 
  */
void emptySequence(byte sequence[]) {
  for(int j = 0 ; j < MAX_SEQUENCE_STEPS ; j++) {
    sequence[j] = NO_COIN;
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

/*****************************************************************************/
/******************************* UNIT TESTS **********************************/
/*****************************************************************************/
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