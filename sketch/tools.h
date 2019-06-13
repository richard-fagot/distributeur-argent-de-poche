#ifndef daap_tools_h
#define daap_tools_h
#include <arduino.h>

class Tools {
  public:
  static int toInt(char c);
  static void toTwoChar(char* dest, byte b);
};
#endif
