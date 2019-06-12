#ifndef smart_card_h
#define smart_card_h
#include <arduino.h>
#include "SL44x2.h" //https://sourceforge.net/p/arduinosclib/wiki/Home/



class SmartCard {
    private:
    ///////////////////////////////////////////////////////////////////////////////
    //
    //  Paramètres du lecteur de carte à puce.
    //
    ///////////////////////////////////////////////////////////////////////////////
        static const uint8_t SC_C2_RST = A1;
        static const uint8_t SC_C1_VCC = A0;
        static const uint8_t SC_C7_IO = A2;
        static const uint8_t SC_C2_CLK = 9;
        static const uint8_t SC_SWITCH_CARD_PRESENT = 13;
        static const boolean SC_SWITCH_CARD_PRESENT_INVERT = false;
        SL44x2 sl44x2 = SL44x2(SC_C7_IO, SC_C2_RST, SC_C1_VCC, SC_SWITCH_CARD_PRESENT, SC_C2_CLK, SC_SWITCH_CARD_PRESENT_INVERT);;

        char name[20 + 1]; // 20 caractères max pour le prénom + caractère nul
        unsigned int secretCode;
        unsigned int pocketMoney;

    public:
    boolean cardInserted();
    void cardRemoved();
    void collectSmartcardData();
    char* getName();
    boolean checkCode(unsigned int code);
    unsigned int getPocketMoney();
};

#endif