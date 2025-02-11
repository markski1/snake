#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

#include "game_state.h"

// These functions vary by platform.
#ifdef _WIN32
#include "platform_specific/win-platform.c"
#else
#include "platform_specific/lin-platform.c"
#endif

// While usually a sin to include C files directly instead of building separately and linking,
// I am not about to make building a text-based snake game complicated for the sake of chasing standards.
#include "system/screen.c"
#include "system/keyboard.c"

/*

	MAIN GAME LOOP

*/

void main(int argc, char const *argv[])
{
	clear_scr();

	// set the random number generator's seed to the current time
	time_t t;
	srand((unsigned) time(&t));

	// set the screensize
	set_scrsize();

	printf("SNEPK!");
	printf("\n\n");
	printf("Press any key to start.");
	printf("\n\n");
	printf("Controls: Arrows, WASD. Press 'o' to exit.");

	getch();

	// Keyboard input is a separate thread.
	pthread_t keyboard_thread;
	pthread_create(&keyboard_thread, NULL, handle_keystrokes, 0);

	// game loop: setup, input, logic, render, restart
	while (true)
	{
		// set up
		create_game_field();
		setup_state();
		game_over = false;

		// run the game each "frame" long as the game is not over.
		while (!game_over)
		{
			logic_run();
		}

		clear_scr();
		printf("Game over! Score: %i\n\n", snk.len - SNAKE_INITIAL_LENGTH);
		printf("Push any key to restart.");

		ms_sleep(200);

		getch();
	}
}


/*
	
	GAME STATE; LOGIC

*/

void setup_state()
{
	// Spawn the snake in a random location on the left side of the playing field.
	snk.pos.x = (rand() % (GAME_WIDTH  / 2)) + 2;
	snk.pos.y = (rand() % (GAME_HEIGHT - 1)) + 3;
	snk.len = SNAKE_INITIAL_LENGTH;
	snk.spe = 1;
	snk.dir = MOVE_RIGHT;

	// move the first couple previous location coords outside the screen
	for (int i = 0; i <= SNAKE_INITIAL_LENGTH; ++i)
	{
		snk.prev[i].x = GAME_WIDTH + 20;
		snk.prev[i].y = GAME_HEIGHT;
	}

	spawn_new_food();
}

// every "frame", if you will.
void logic_run()
{
	// record the last location of the snake
	snk.prev[0].x = snk.pos.x;
	snk.prev[0].y = snk.pos.y;

	// check movement buffer
	if (movement_buffer[0] != MOVE_NONE)
	{
		switch(movement_buffer[0])
		{
			case MOVE_UP:
				if (snk.dir != MOVE_DOWN)
					snk.dir = MOVE_UP;
				break;
			case MOVE_DOWN:
				if (snk.dir != MOVE_UP)
					snk.dir = MOVE_DOWN;
				break;
			case MOVE_LEFT:
				if (snk.dir != MOVE_RIGHT)
					snk.dir = MOVE_LEFT;
				break;
			case MOVE_RIGHT:
				if (snk.dir != MOVE_LEFT)
					snk.dir = MOVE_RIGHT;
				break;
		}

		for (int i = 0; i < KB_BFR_SIZE - 1; ++i)
		{
			movement_buffer[i] = movement_buffer[i + 1];
		}

		movement_buffer[KB_BFR_SIZE - 1] = MOVE_NONE;
	}

	// move in whichever direction it is we're moving
	switch (snk.dir)
	{
		case MOVE_UP:
			snk.pos.y -= 1;
			break;
		case MOVE_DOWN:
			snk.pos.y += 1;
			break;
		case MOVE_LEFT:
			snk.pos.x -= 1;
			break;
		case MOVE_RIGHT:
			snk.pos.x += 1;
			break;
	}
	
	wall_check();

	draw_snake();

	// if we've moved out of bounds, or ran into ourselves, game over.
	if (snake_state_invalid())
	{
		game_over = true;
		return;
	}

	// detect food consumption
	if (food.x == snk.pos.x && food.y == snk.pos.y)
	{
		snk.len++;
		if (snk.len < 25) snk.spe += 1;
		else if (snk.len < 50)
		{
			if (snk.spe % 2) snk.spe += 1;
		}
		spawn_new_food();
		update_score();
	}

	// move cursor out of the way
	goto_xy(GAME_WIDTH + 15, GAME_HEIGHT);

	logic_wait();
}

bool snake_state_invalid()
{
	// check collision on self
	for (int i = snk.len - 1; i >= 0; --i)
	{
		if (snk.pos.x == snk.prev[i].x && snk.pos.y == snk.prev[i].y)
			return true;
	}

	return false;
}

bool food_state_invalid()
{
	// check food isn't outside the bounds of the game
	if (food.x <= 1 || food.y <= 1)
	{
		return true;
	}
	if (food.x >= GAME_WIDTH || food.y >= GAME_HEIGHT)
	{
		return true;
	}

	// check food isn't spawning in the snake's head
	if (food.x == snk.pos.x && food.y == snk.pos.y)
		return true;

	// check food isn't spawning in the snake's body
	for (int i = snk.len; i >= 1; --i)
	{
		if (food.x == snk.prev[i].x && food.y == snk.prev[i].y)
			return true;
	}

	return false;
}

void spawn_new_food()
{
	// give the food a new position, repeat if it's not in a valid place.
	do
	{
		food.x = (rand() % (GAME_WIDTH - 5))  + 3;
		food.y = (rand() % (GAME_HEIGHT - 4)) + 3;
	}
	while (food_state_invalid());

	// draw the food
	print_xy(food.x, food.y, ANSI_COLOR_YELLOW "#" ANSI_COLOR_RESET);
}

void wall_check()
{
	// if the snake pos runs into a wall, move it to the other end.
	if (snk.pos.x <= 1)
		snk.pos.x = GAME_WIDTH - 1;

	if (snk.pos.x >= GAME_WIDTH)
		snk.pos.x = 2;

	if (snk.pos.y <= 1)
		snk.pos.y = GAME_HEIGHT - 1;

	if (snk.pos.y >= GAME_HEIGHT)
		snk.pos.y = 2;
}

void draw_snake()
{
	int i;
	
	// shift every previous position one space back, since we're moving
	for (i = snk.len; i >= 1; --i)
	{
		snk.prev[i].x = snk.prev[i-1].x;
		snk.prev[i].y = snk.prev[i-1].y;
	}

	// draw the prevous head of the snake as the body
	print_xy(snk.prev[0].x, snk.prev[0].y, ANSI_COLOR_GREEN "@" ANSI_COLOR_RESET);

	// erase the tail-end of our snake
	print_xy(snk.prev[snk.len].x, snk.prev[snk.len].y, " ");

	// draw the new head of the snake
	switch (snk.dir)
	{
		case MOVE_UP:
			print_xy(snk.pos.x, snk.pos.y, ANSI_COLOR_GREEN "^" ANSI_COLOR_RESET);
			break;
		case MOVE_DOWN:
			print_xy(snk.pos.x, snk.pos.y, ANSI_COLOR_GREEN "v" ANSI_COLOR_RESET);
			break;
		case MOVE_LEFT:
			print_xy(snk.pos.x, snk.pos.y, ANSI_COLOR_GREEN "<" ANSI_COLOR_RESET);
			break;
		case MOVE_RIGHT:
			print_xy(snk.pos.x, snk.pos.y, ANSI_COLOR_GREEN ">" ANSI_COLOR_RESET);
			break;
	}
}

// wait a given amount of time, less as the snake becomes longer,
// and check for keyboard input afterwards. update the snake's behaviour if required.
void logic_wait()
{
	// wait reduced by the snake's speed.
	long wait_amount = BASE_WAIT - snk.spe;

	// if moving vertically slow things down, since vertical characters are higher
	if (snk.dir == MOVE_UP || snk.dir == MOVE_DOWN)
		wait_amount *= 1.35;

	ms_sleep(wait_amount);
}