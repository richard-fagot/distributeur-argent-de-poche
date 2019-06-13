#include "tools.h"

int Tools::toInt(char c) {
  return (int)(c - 48);
}

void Tools::toTwoChar(char* dest, byte b) {
  byte dizaines = b / 10 ;
  byte unites = b - dizaines*10;

  dest[0] = '0' + dizaines;
  dest[1] = '0' + unites;
  dest[2] = '\0';
  
}
