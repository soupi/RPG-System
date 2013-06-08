#include "Controller.h"


int main()
{
	srand(unsigned(time(NULL)));

	Controller ctrl;
	ctrl.run();

	return EXIT_SUCCESS;
}