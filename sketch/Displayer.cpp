#include <arduino.h>
#include "Displayer.h"


Displayer::Displayer() {
  lineIndex = 0;
}

void Displayer::initialize() {
  OLED.begin();
  clear();
  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
}
void Displayer::clear() {
  OLED.clearDisplay();
  lineIndex = 0;
}

void Displayer::addLine(const char* msg) {
  OLED.setCursor(0, lineIndex*8);
  char centeredMsg[21];
  centerText(msg, centeredMsg);
  OLED.print(centeredMsg);
  OLED.display();
  
  lineIndex++;
  if(lineIndex > 3) {
    lineIndex = 0;
  }
}

void Displayer::centerText(const char *msg, char centeredMsg[21]) {  
  for(int i = 0 ; i < 20 ; i++) {
    centeredMsg[i] = ' ';
  }
  centeredMsg[20] = '\0';
  // strcpy(centeredMsg, "                    "); //:OPTIM : utilise 26 octets de plus que la boucle

  int whiteSpaceLength = (20 - strlen(msg))/2;
  
  int msgLength = strlen(msg);                 //:OPTIM : en faisant ça au lieu de le mettre dans la condition d'arrêt du for on économise 12 octets
  for( int i = 0 ; i < msgLength ; i++) {
    centeredMsg[i+whiteSpaceLength] = msg[i];
  } 
}
