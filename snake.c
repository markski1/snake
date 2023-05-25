#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

#include "structures.h"

// globals
snake   snk;
coords  food;
bool    game_over = false;
int     movement_buffer[KB_BFR_SIZE];

#ifdef _WIN32
#include "platform_specific/win-platform.h"
#else
#include "platform_specific/lin-platform.h"
#endif

#include "system/screen.h"
#include "system/keyboard.h"

#include "game_state.h"

void main(int argc, char const *argv[])
{
	clear_scr();

	// set the random number generator's seed to the current time
	time_t t;
	srand((unsigned) time(&t));

	// set the screensize
	set_scrsize();

	printf("SNEPK!\n\nPress any key to start.\n\nIf running from a terminal, please ensure\nyou have at least %i lines of height.", GAME_HEIGHT);

	getch();

	pthread_t keyboard_thread;
	pthread_create(&keyboard_thread, NULL, handle_keystrokes, 0);

	while (true) {
		// set up
		create_game_field();
		setup_state();
		game_over = false;

		// game loop
		while (!game_over) {
			logic_run();
		}

		clear_scr();
		printf("Game over! Score: %i\n\n", snk.len - SNAKE_INITIAL_LENGTH);
		printf("Restarting in 3 seconds..");

		ms_sleep(3000);
	}
}