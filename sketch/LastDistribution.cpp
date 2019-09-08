#include "LastDistribution.h"
#include <EEPROM.h>

void LastDistribution::create(char* name, byte day, byte month) {
  Serial.print("Create in EEPROM ");Serial.println(name);
  byte lastSavedNameIndex = EEPROM.read(0);
  if(lastSavedNameIndex == 0xFF) {
    lastSavedNameIndex = 0;
  } else {
    lastSavedNameIndex++;
  }
  
  set(name, day, month, lastSavedNameIndex);
  persist();
  
}

void LastDistribution::set(char* name, byte day, byte month, int index) {
  clearDistributionDate();
  
  strcpy(distributionDate.name, name);
  distributionDate.day = day;
  distributionDate.month = month;
  EEPROMAdress = index;
}

void LastDistribution::persist() {
  EEPROM.write(0, EEPROMAdress);
  EEPROM.put(1 + EEPROMAdress*sizeof(DistributionDate), distributionDate);
}
               
boolean LastDistribution::retrieveLastDistribution(const char* name) {
  byte lastSavedNameIndex = EEPROM.read(0);
  boolean hasFound = false;
  
  if(!(lastSavedNameIndex == 255)) {
    for(int i = 0 ; i <= lastSavedNameIndex ; i++) {
      	int a = sizeof(DistributionDate);
		    EEPROM.get(1 + i*a, distributionDate);
      	if(strcmp(name, distributionDate.name) == 0) {
          hasFound = true;
          break;
      	}
    }
  }
  
  return hasFound;
  
}

void LastDistribution::save(char* name, byte day, byte month) {
  if(retrieveLastDistribution(name)) {
    set(name, day, month, EEPROM.read(0));
    persist();
  } else {
    create(name, day, month);
  }
}

byte LastDistribution::getDay() {
    return distributionDate.day;
}

byte LastDistribution::getMonth() {
    return distributionDate.month;
}

void LastDistribution::clearDistributionDate() {
  for(int i = 0 ; i < 21 ; i++) {
    distributionDate.name[i] = 0xFF;
    distributionDate.day = 0xFF;
    distributionDate.month = 0xFF;
  }
}


#ifdef DAAP_DEBUG
void LastDistribution::eraseEEPROMContent() {
  for(int i =0 ; i < 70 ; i++) {
    EEPROM.write(i,255);
  }
  showEEPROMContent();
}

void LastDistribution::showEEPROMContent() {
  Serial.print('#');
  for(int i =0 ; i < 70 ; i++) {
    byte t = EEPROM.read(i);
    if((t >= 'A' && t <= 'Z') || (t >= 'a' && t <= 'z') ) {
      Serial.print((char)t); 
    } else {
      Serial.print(t, HEX);
    }
  }
  Serial.println('#');
}

#endif
