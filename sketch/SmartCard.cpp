#include "SmartCard.h"
#include "tools.h"

boolean SmartCard::cardInserted() {
    return sl44x2.cardInserted();
}

void SmartCard::cardRemoved() {
    sl44x2.cardRemoved();
}

void SmartCard::collectSmartcardData() {
    if (sl44x2.cardReady()) { // appel bloquant
        uint8_t data[1 + 4 + 3 + 20]; // 1 octet pour le nombre de caractères dans le prénom de l'enfant
                                      // 4 octets pour le code secret (écrit en string)
                                      // 3 octets pour le montant à distribuer (écrit en string)
                                      // 20 octets pour le prénom de l'enfant
                                      //
                                      // ==> = 28 octets
        uint16_t i = sl44x2.readMainMemory(0x60, data, 28); 

        int length = data[0];
        this->secretCode = Tools::toInt(data[1]) * 1000 + Tools::toInt(data[2]) * 100 + Tools::toInt(data[3]) * 10 + Tools::toInt(data[4]);
        this->pocketMoney = Tools::toInt(data[5]) * 100 + Tools::toInt(data[6]) * 10 + Tools::toInt(data[7]);
        strncpy(this->name, (const char *)(data + 8), length);
        this->name[length] = '\0';
    }
}


char* SmartCard::getName() {
    return this->name;
}

boolean SmartCard::checkCode(unsigned int code) {
    return this->secretCode == code;
}

unsigned int SmartCard::getPocketMoney() {
    return this->pocketMoney;
}
