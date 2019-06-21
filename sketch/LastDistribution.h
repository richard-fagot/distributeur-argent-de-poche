#ifndef LAST_DISTRIBUTION_H
#define LAST_DISTRIBUTION_H
#include <Arduino.h>

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
};

#endif