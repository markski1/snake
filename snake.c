#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "structures.h"
// globals
snake  snk;
coords food;
bool   game_over;

#include "platform.h"
#include "screen.h"
#include "game_state.h"

int main(int argc, char const *argv[])
{
	// set the random number generator's seed to the current time
	time_t t;
	srand((unsigned) time(&t));

	// set the screensize
	set_scrsize();

	// set up
	create_game_field();
	setup_state();
	game_over = false;

	// game loop
	while (!game_over) {
		logic_run();
		wait_and_key();
	}

	clear_scr();
	goto_xy(0, 0);
	printf("Game over! Score: %i", snk.len);

	// prevent exiting too quickly after ending

	Sleep(1111);
	
	// wait for keystroke
	getch();
	return 0;
}