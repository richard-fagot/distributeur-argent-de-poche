#ifndef LAST_DISTRIBUTION_H
#define LAST_DISTRIBUTION_H
#include <Arduino.h>
//#define DAAP_DEBUG 1

struct DistributionDate {
  char name[21];
  byte day;
  byte month;
};

class LastDistribution {
  	DistributionDate distributionDate;
  	int EEPROMAdress;
  
	public:
  	boolean retrieveLastDistribution(const char* name);
  	void save(char* name, byte day, byte month);
  	void create(char* name, byte day, byte month);
  	void set(char* name, byte day, byte month, int index);
  	void persist();
    byte getDay();
    byte getMonth();
    
    #ifdef DAAP_DEBUG
    void showEEPROMContent();
    void eraseEEPROMContent();
    #endif

    private:
      void clearDistributionDate();
};

#endif
