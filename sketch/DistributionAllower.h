#ifndef DISTRIBUTION_ALLOWER_H
#define DISTRIBUTION_ALLOWER_H
#include "MyTime.h"

class DistributionAllower {
    const byte ALLOWED_DAYS_COUNT = 2;
    const byte ALLOWED_DAYS[ALLOWED_DAYS_COUNT] = {5, 6}

    private:
        boolean badDate(MyTime &time);
        boolean yetDistributed(const char *name, MyTime &time);
        void void getPreviousDay(byte day, byte month, int year, byte &pday, byte &pmonth);

    public:
        boolean isAllowed(const char *name, MyTime &time);
}
#endif