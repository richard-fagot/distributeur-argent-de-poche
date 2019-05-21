#include <arduino.h>
#include <Servo.h>
#include "CoinPusher.h"

CoinPusher::CoinPusher(byte servoPin, int coinValue) {
    pin = servoPin;
    faceValue = coinValue;
    STATE = READY_TO_MOVE;
}

void CoinPusher::initialize() {
    Serial.print("Initialize \t");
    Serial.println(pin);
    servo.attach(pin);
    servo.write(180);
    delay(2000);
    Serial.println("2s");
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
      	Serial.println("Goto push position");
      	break;
      case WAIT:
        if(millis() - previousMillis > MOVE_DELAY) {
          STATE = nextState;
          Serial.println("End waiting");
        }
      	break;
      case GOTO_INITIAL_POSITION:
    	  servo.write(180);
      	STATE = WAIT;
      	nextState = FINISH;
      	previousMillis = millis();
      	Serial.println("Goto end position");
      	break;
      case FINISH:
      	servo.detach();
      	STATE = READY_TO_MOVE;
      Serial.println("Finish move");
      	break;
        
    } 
}

boolean CoinPusher::hasFinished() {
    return STATE == READY_TO_MOVE;
}

int CoinPusher::getCoinValue() {
    return faceValue;
  }
