#define MAX_PUSHER_COUNT 3

class CoinPusher {
    byte facialValue;
};

CoinPusher *coinPushers[MAX_PUSHER_COUNT];
CoinPusher *sequence[MAX_SEQUENCE_COUNT];

void setup() {
    int pocketMoney = 300;
    int remaining = pocketMoney;
    byte pusherIndex = 0;
    byte sequenceIndex = 0;

    while(remaining != 0) {
        int actualFacialValue = coinPushers[pusherIndex]->getFacialValue();
        byte pushCount = remaining / actualFacialValue;
        for(int i = 0 ; i < pushCount ; i++) {
            sequence[sequenceIndex] = coinPushers[pusherIndex];
            sequenceIndex++;
        }
        remaining -= actualFacialValue * pushCount;
    }
}

void loop() {...}