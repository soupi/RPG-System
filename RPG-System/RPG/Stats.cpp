#include "Stats.h"
#include <ctime>
#include <cstdlib>

// calculate damage by stats and attack power
int calcDamage(Stats offense, Stats defense, int power)
{
	int critical = 1; // bonus scalar

	if (rand() % (100/offense.LUCK()) == 0) // higher luck means more chance for critical strike
		critical = 2;

	return int(critical*(double(offense.ATK())/offense.DEF())*power);

}
