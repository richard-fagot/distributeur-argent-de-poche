#ifndef coin_pusher_h
#define coin_pusher_h
#include <arduino.h>
#include <Servo.h>

class CoinPusher {
  Servo servo;
  byte pin;
  int faceValue;
  
  int EJECTION_DELAY = 1000; //Vitesse d'ejection d'une pièce (le mouvement du poussoir va durer 1s).
  byte position = 0;
  
  unsigned long previousMillis;
  static const unsigned long MOVE_DELAY = 1000;
  
  enum servo_state {
    GOTO_INITIAL_POSITION,
    WAIT,
    CONNECT_SERVO,
    GOTO_PUSH_POSITION,
    READY_TO_MOVE,
    FINISH
  };
  
  servo_state STATE;
  servo_state nextState;
  
  public:
  CoinPusher(byte servoPin, int coinValue);
  
  void initialize();
  
  void pushCoin();
  
  boolean hasFinished();
  
  int getCoinValue();
};

#endif
