#include "Stats.h"
#include <ctime>
#include <cstdlib>

int calcDamage(Stats offense, Stats defense, int power)
{
	int bonus = 1;

	if (rand() % (100/offense.LUCK()) == 0)
		bonus = 2;
	return int(bonus*(double(offense.ATK())/offense.DEF())*power);

}
