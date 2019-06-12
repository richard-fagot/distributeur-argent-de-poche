#ifndef smart_card_h
#define smart_card_h
#include <arduino.h>
#include "SL44x2.h" //https://sourceforge.net/p/arduinosclib/wiki/Home/

#define SC_C2_RST A1
#define SC_C1_VCC A0
#define SC_C7_IO A2
#define SC_C2_CLK 9
#define SC_SWITCH_CARD_PRESENT 13
#define SC_SWITCH_CARD_PRESENT_INVERT false

class SmartCard {
    private:
    ///////////////////////////////////////////////////////////////////////////////
    //
    //  Paramètres du lecteur de carte à puce.
    //
    ///////////////////////////////////////////////////////////////////////////////
        
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