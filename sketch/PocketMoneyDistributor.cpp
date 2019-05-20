#include <arduino.h>
#include "PocketMoneyDistributor.h"

PocketMoneyDistributor::PocketMoneyDistributor(){
    for(int i = 0 ; i < MAX_COIN_PUSHERS ; i++) {
      coinPusher[i] = NULL;
    }

    for (int i = 0; i < MAX_SEQUENCE_STEPS; i++){
        pusherSequence[i] = STOP_SEQUENCE;
    }

    STATE = READY_TO_DISTRIBUTE;
}

void PocketMoneyDistributor::distribute(int pocketMoneyAmount){

    switch (STATE){

    case READY_TO_DISTRIBUTE:
    case START_SEQUENCE:
        computeDistributionSequence(pocketMoneyAmount);
        sequenceIndex = 0;

        if (pusherSequence[sequenceIndex] != STOP_SEQUENCE){
            pusherSequence[sequenceIndex]->pushCoin();
            STATE = NEXT;
        }

        break;

    case NEXT:

        pusherSequence[sequenceIndex]->pushCoin();
        if (pusherSequence[sequenceIndex]->hasFinished()){
            sequenceIndex++;

            if (MAX_SEQUENCE_STEPS < sequenceIndex || STOP_SEQUENCE == pusherSequence[sequenceIndex]){
                STATE = READY_TO_DISTRIBUTE;
                break;
            }
        }

        break;
    }
}

boolean PocketMoneyDistributor::hasFinished(){
    return STATE == READY_TO_DISTRIBUTE;
}

void PocketMoneyDistributor::setup(int nbCoinTypes, ...) {
    va_list ap;
    va_start(ap, nbCoinTypes);
    
    for( int i = 0; i < nbCoinTypes; i++) {
      int coinPusherPin = va_arg(ap,int);
      int coinValue = va_arg(ap,int);
       
      CoinPusher *cp = new CoinPusher(coinPusherPin, coinValue);
      coinPusher[i] = cp;
      coinPusher[i]->initialize();
    }
	va_end(ap); 
}

void PocketMoneyDistributor::computeDistributionSequence(int pocketMoneyAmount) {
    byte sequenceIndex = 0;
  	int remainingValueToDistribute = pocketMoneyAmount;
  	byte coinValueIndex = 0;
  	byte coinsCount = 0;
	  
  	// Initialisation avec une séquence vide
  	emptySequence();
	  
  	while(remainingValueToDistribute != 0) {
	    
	    // Si il n'y a pas suffisamment de type de valeurs faciales
	    // pour faire le montant à distribuer, on vide la séquence
	    // et on s'arrête ==> pas de distribution de pièce.
	    if(coinValueIndex >= MAX_COIN_PUSHERS) {
	      emptySequence();
	      return;
	    }
	    
	    // Combien de pièces de la valeur faciale courante y-a-t'il
	    // dans ce qu'il reste à distribuer ?
	    coinsCount = remainingValueToDistribute / coinPusher[coinValueIndex]->getCoinValue();
	      
	    for(byte i = 0 ; i < coinsCount ; i++) {
	      pusherSequence[sequenceIndex] = coinPusher[coinValueIndex];
	      sequenceIndex++;
	      
	      if(sequenceIndex >= MAX_SEQUENCE_STEPS) {
	        emptySequence();
	        return;
	      }
	    }
	
	    remainingValueToDistribute -= coinPusher[coinValueIndex]->getCoinValue()*coinsCount;
	    coinValueIndex++;      
  	}
    
  }//

  void PocketMoneyDistributor::emptySequence() {
    for(int j = 0 ; j < MAX_SEQUENCE_STEPS ; j++) {
    	pusherSequence[j] = STOP_SEQUENCE;
  	}
  }