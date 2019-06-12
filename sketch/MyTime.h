#ifndef my_time_h
#define my_time_h

#include <Wire.h>
#include <ds3231.h> //ds3231FS by Petre Rodan

class MyTime {
    ts timeDetails;
    
    private:
    void refreshDate();

    public:
    void setup();
    byte getWeekDay();
};
#endif