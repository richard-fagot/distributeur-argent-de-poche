#include "Mytime.h"

void MyTime::setup() {
    Wire.begin(); //start i2c (required for connection)
    DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)
}

void MyTime::refreshDate() {
    DS3231_get(&timeDetails);
}

byte MyTime::getWeekDay() {
    refreshDate();
    return timeDetails.wday;
}