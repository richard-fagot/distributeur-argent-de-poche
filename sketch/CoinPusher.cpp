#include <arduino.h>
#include <Servo.h>
#include "CoinPusher.h"

CoinPusher::CoinPusher(byte servoPin, int coinValue) {
    pin = servoPin;
    faceValue = coinValue;
    STATE = READY_TO_MOVE;
}

void CoinPusher::initialize() {
    servo.attach(pin);
    servo.write(180);
    delay(2000); // on veut vraiment bloquer les actions de l'arduino en attendant que le servo ait fini son mouvement.
    servo.detach();
    STATE = READY_TO_MOVE;
}

void CoinPusher::pushCoin() {
    switch(STATE) {
      case READY_TO_MOVE:
      case CONNECT_SERVO:
        servo.attach(pin);
        STATE = GOTO_PUSH_POSITION;
        previousMillis = millis();
        position = 180;
      case GOTO_PUSH_POSITION:
        if(millis() - previousMillis > (EJECTION_DELAY/180)) {
          position -= 1;
          if(position < 0) position = 0;
          previousMillis = millis();
        }
      	servo.write(position);
        
        if(position == 0) {
          STATE = GOTO_INITIAL_POSITION;
          //STATE = WAIT;
          //nextState = GOTO_INITIAL_POSITION;
          previousMillis = millis();  
        }
      	break;
      case WAIT:
        if(millis() - previousMillis > MOVE_DELAY) {
          STATE = nextState;
        }
      	break;
      case GOTO_INITIAL_POSITION:
    	  servo.write(180);
      	STATE = WAIT;
      	nextState = FINISH;
      	previousMillis = millis();
      	break;
      case FINISH:
      	servo.detach();
      	STATE = READY_TO_MOVE;
      	break;
        
    } 
}

boolean CoinPusher::hasFinished() {
    return STATE == READY_TO_MOVE;
}

int CoinPusher::getCoinValue() {
    return faceValue;
  }
