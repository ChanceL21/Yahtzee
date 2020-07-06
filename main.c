#include "PA5.h"

int main(void)
{
	srand(time(NULL)); // setting up random number generator for dice

	int option = 0, program_running = 1;

	while (program_running)
	{
		option = menu_select(); // displaying menu and returning satisfactory option

		switch (option)
		{
		case 1: display_rules();
			break;
		case 2: play_game();
			break;
		case 3: program_running = 0; // discontinuing while loop
			printf("Thanks for playing!\n");
			break;
		}
	}

	return 0;
}