#include "DistributionAllower.h"
#include <Arduino.h>
#include "LastDistribution.h"
#define DAAP_DEBUG 1


boolean DistributionAllower::badDate(MyTime &time) {
    boolean isBadDate = true;

    byte today = time.getWeekDay();
    if(today == ALLOWED_DAYS[0] || today == ALLOWED_DAYS[1]) {
        isBadDate = false;
    }

    return isBadDate; 
}

boolean DistributionAllower::yetDistributed(const char *name, MyTime &time) {
    boolean isYetDistributed = false;
    LastDistribution ld;

    #ifdef DAAP_DEBUG
      Serial.print("Found ");
      Serial.print(name);
      Serial.print(" in EEPROM ? : ");
      Serial.println(ld.retrieveLastDistribution(name));
    #endif
    
    if( ld.retrieveLastDistribution(name) ) {    
      byte day = time.getDay();
      byte month = time.getMonth();
      int year = time.getYear();
        
      byte pDay, pMonth;
      getPreviousDay(day, month, year, pDay, pMonth);

      if( (day == ld.getDay() && month == ld.getMonth())
         || (pDay == ld.getDay() && pMonth == ld.getMonth()) ) {
             isYetDistributed = true;
      }
    }

    return isYetDistributed;
}

boolean DistributionAllower::isAllowed(const char *name, MyTime &time) {
    boolean isAllowed = true;
    
    #ifdef DAAP_DEBUG
      Serial.print("Bad date (");
      Serial.print(time.getWeekDay());
      Serial.print(") : ");
      Serial.println(badDate(time));
    #endif
    
    if(/*badDate(time) ||*/ yetDistributed(name, time)) {
        isAllowed = false;
    }

    return isAllowed;
}

void DistributionAllower::getPreviousDay(byte day, byte month, int year, byte &pday, byte &pmonth) {
  byte monthsDays[] = {31,29,31,30,31,30,31,31,30,31,30,31};
  
  if(day > 1) { // je ne suis pas le premier jour du mois
    pday = day - 1;
    pmonth = month;
  } else if (month != 3){ // je suis le premier jour du mois qui n'est pas mars (car février est plus compliqué)
    pmonth = month -1;
   	if(pmonth == 0) pmonth = 12;
    pday = monthsDays[pmonth-1];
  } else { // je suis le 1er mars
    pmonth = 2;
    
    int yearBy4 = year / 4;
    int yearBy100 = year / 100;
    int yearBy400 = year / 400;
    
    boolean isDivisibleBy4 = (year - yearBy4 * 4) == 0;
    boolean isNotDivisibleBy100 = (year - yearBy100*100) > 0;
    boolean isDivisibleBy400 = (year - yearBy400*400) == 0;
    
    if( (isDivisibleBy4 and isNotDivisibleBy100) || isDivisibleBy400) {
      pday = 29;
    } else {
      pday = 28;
    }
  }
}
