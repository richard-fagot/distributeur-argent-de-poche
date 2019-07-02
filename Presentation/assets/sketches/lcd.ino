#include <LiquidCrystal_PCF8574.h> // by Mathias Hertel

LiquidCrystal_PCF8574 lcd = LiquidCrystal_PCF8574(0x27);

lcd.setCursor(col, row);
lcd.print(message);