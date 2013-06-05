#include "Stats.h"
#include <ctime>
#include <cstdlib>

int calcDamage(Stats offense, Stats defense)
{
	int bonus = 1;
	//srand(unsigned(time(NULL)));
	if (rand() % (50/offense.LUCK()) == 0)
		bonus = 2;
	return int(bonus*(double(offense.ATK())/offense.DEF())*20);

}
