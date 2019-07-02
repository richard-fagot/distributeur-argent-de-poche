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
      case GOTO_PUSH_POSITION:
      	servo.attach(pin);
      	servo.write(0);
      	STATE = WAIT;
      	nextState = GOTO_INITIAL_POSITION;
      	previousMillis = millis();
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
