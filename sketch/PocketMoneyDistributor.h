#ifndef pocket_money_distributor_h
#define pocket_money_distributor_h
#include <arduino.h>
#include "CoinPusher.h"

#define STOP_SEQUENCE NULL // je ne sais pas pourquoi mais avec la déclaration
                           // dans la classe le compilateur dit 'undefined
                           // reference to 'PocketMoneyDistributor::STOP_SEQUENCE'.

class PocketMoneyDistributor {
  
  static const byte MAX_COIN_PUSHERS = 2;
  static const byte MAX_SEQUENCE_STEPS = 5;
  //static const CoinPusher *STOP_SEQUENCE = NULL; // voir le #define
  
  CoinPusher *coinPusher[MAX_COIN_PUSHERS];
  CoinPusher *pusherSequence[MAX_SEQUENCE_STEPS];
  
  byte sequenceIndex = 0;
  
  enum distributor_state {
    READY_TO_DISTRIBUTE,
    START_SEQUENCE,
    NEXT
  };
  
  distributor_state STATE;
  
  public:
  
  PocketMoneyDistributor();
  
  void distribute(int pocketMoneyAmount);
  
  boolean hasFinished();

  void setup(int nbCoinTypes, ...);
  void initialize();

  private:
  void computeDistributionSequence(int pocketMoneyAmount);
  
  void emptySequence();

};



#endif
