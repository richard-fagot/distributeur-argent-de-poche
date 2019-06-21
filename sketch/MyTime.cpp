#include "Mytime.h"
#include "tools.h"

void MyTime::setup() {
    Wire.begin(); //start i2c (required for connection)
    DS3231_init(DS3231_INTCN); //register the ds3231 (DS3231_INTCN is the default address of ds3231, this is set by macro for no performance loss)
}

void MyTime::refreshDate() {
    DS3231_get(&timeDetails);
}

byte MyTime::getWeekDay() {
    return timeDetails.wday;
}

byte MyTime::getDay() {
    return timeDetails.mday;
}

byte MyTime::getMonth() {
    return timeDetails.mon;
}

byte MyTime::getMinute() {
    return timeDetails.min;
}

int MyTime::getYear() {
    return timeDetails.year;
}

/**
 * LUN 03 MAR     11:43
 */
void MyTime::getStringTime(char* timeString) {
    strcpy(timeString, wdays[timeDetails.wday]);
    strcat(timeString, " ");
    char mday[3];
    Tools::toTwoChar(mday, timeDetails.mday);
    strcat(timeString, mday);
    strcat(timeString, " ");
    strcat(timeString, months[timeDetails.mon - 1]);
    strcat(timeString, "     ");
    char hour[3];
    Tools::toTwoChar(hour, timeDetails.hour);
    strcat(timeString, hour);
    strcat(timeString, ":");
    char minute[3];
    Tools::toTwoChar(minute, timeDetails.min);
    strcat(timeString, minute);
}
