#ifndef DISPLAYER_H
#define DISPLAYER_H
#include <arduino.h>
#include <LiquidCrystal_PCF8574.h> // by Mathias Hertel


class Displayer {
  private:
  LiquidCrystal_PCF8574 lcd = LiquidCrystal_PCF8574(0x27);
  byte NB_COLS = 20;
  byte NB_ROWS = 4;
  byte lineIndex;

  void centerText(const char *msg, char centeredMsg[21]);
  
  public:
    void initialize();
    Displayer();
    void clear();
    void addLine(const char* msg);
};

#endif
