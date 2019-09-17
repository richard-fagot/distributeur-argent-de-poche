#ifndef my_time_h
#define my_time_h

#include <Wire.h>
#include <ds3231.h> //ds3231FS by Petre Rodan
/*
enum DAYS {
    MONDAY = 0,
    TUESDAY = 1,
    WEDNESDAY = 2,
    THIRSDAY = 3,
    FRIDAY = 4,
    SATURDAY = 5,
    SUNDAY = 6
};
    */
class MyTime {
    const char wdays [7][3+1] = 
    {
        "LUN", "MAR", "MER", "JEU", "VEN", "SAM", "DIM"
    };

    const char months[12][3+1] =
    {
       "JAN", "FEV", "MAR", "AVR", "MAI", "JUN", "JUI", "AOU", "SEP", "OCT", "NOV", "DEC"
    };

    ts timeDetails;
    

    public:
    void setup();
    byte getWeekDay();
    byte getMinute();
    byte getDay();
    byte getMonth();
    int getYear();
    void getStringTime(char* timeString);
    void refreshDate();
};
#endif
