#include <arduino.h>
#include "Displayer.h"

Displayer::Displayer() {
  lineIndex = 0;
}

void Displayer::initialize() {
  lcd.begin(NB_COLS, NB_ROWS);
  lcd.setBacklight(255);
  clear();
}

void Displayer::clear() {
  lcd.home(); lcd.clear();
  lineIndex = 0;
}

void Displayer::addLine(const char* msg) {
  lcd.setCursor(0, lineIndex);
  char centeredMsg[NB_COLS+1];
  centerText(msg, centeredMsg);
  lcd.print(centeredMsg);
  
  lineIndex++;
  if(lineIndex > (NB_ROWS-1)) {
    lineIndex = 0;
  }
}

void Displayer::centerText(const char *msg, char centeredMsg[21]) {  
  for(int i = 0 ; i < NB_COLS ; i++) {
    centeredMsg[i] = ' ';
  }
  centeredMsg[NB_COLS] = '\0';
  // strcpy(centeredMsg, "                    "); //:OPTIM : utilise 26 octets de plus que la boucle

  int whiteSpaceLength = (NB_COLS - strlen(msg))/2;
  
  int msgLength = strlen(msg);                 //:OPTIM : en faisant ça au lieu de le mettre dans la condition d'arrêt du for on économise 12 octets
  for( int i = 0 ; i < msgLength ; i++) {
    centeredMsg[i+whiteSpaceLength] = msg[i];
  } 
}