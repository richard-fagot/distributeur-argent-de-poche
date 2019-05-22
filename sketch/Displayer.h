#ifndef DISPLAYER_H
#define DISPLAYER_H
#include <arduino.h>

/////////////// A REMPLACER PAR LCD /////////////////////////
// OLED Display
#include <Adafruit_GFX.h>     // Adafruit GFX Library by Adafruit
#include <Adafruit_SSD1306.h> // Adafruit SSD1306 by Adafruit


class Displayer {
  private:
  Adafruit_SSD1306 OLED = Adafruit_SSD1306(0);
  byte lineIndex;
  void centerText(const char *msg, char centeredMsg[21]);
  
  public:
    void initialize();
    Displayer();
    void clear();
    void addLine(const char* msg);
};

#endif
