#ifndef my_keypad_h
#define my_keypad_h
#include <Keypad.h> //Keypad by Mark Stanley, Alexander Brevig Version 3.1.1

class MyKeypad {
    static const byte ROWS = 4; 
    static const byte COLS = 4; 

    char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
  
    byte rowPins[ROWS] = {7, 4, 2, A3}; 
    byte colPins[COLS] = {12, 11, 10, 8}; 

    Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

    public:
        char getKey();
};

#endif