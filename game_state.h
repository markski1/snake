bool snake_state_invalid();
void spawn_new_food();
void draw_snake();
void logic_wait();
void wall_check();

void setup_state()
{
	// Spawn the snake in a random location on the left side of the playing field.
	snk.pos.x = (rand() % (GAME_WIDTH  / 2)) + 2;
	snk.pos.y = (rand() % (GAME_HEIGHT - 1)) + 3;
	snk.len = SNAKE_INITIAL_LENGTH;
	snk.spe = 1;
	snk.dir = MOVE_RIGHT;

	// move the first couple previous location coords outside the screen
	for (int i = 0; i <= SNAKE_INITIAL_LENGTH; ++i) {
		snk.prev[i].x = GAME_WIDTH + 20;
		snk.prev[i].y = GAME_HEIGHT;
	}

	update_score();

	spawn_new_food();
}

int count = 0;

// every "frame", if you will.
void logic_run()
{
	// record the last location of the snake
	snk.prev[0].x = snk.pos.x;
	snk.prev[0].y = snk.pos.y;

	// check movement buffer
	if (movement_buffer[0] != MOVE_NONE) {
		switch(movement_buffer[0]) {
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

		for (int i = 0; i < KB_BFR_SIZE - 1; ++i) {
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
		if (snk.len < 50) snk.spe += 1;
		else snk.spe += rand() % 2;
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
	for (int i = snk.len; i >= 1; --i) {
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
	goto_xy(food.x, food.y);
	printf(ANSI_COLOR_YELLOW "#" ANSI_COLOR_RESET);
}

void wall_check() {
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

void draw_snake() {
	int i;
	
	// shift every previous position one space back, since we're moving
	for (i = snk.len; i >= 1; --i)
	{
		snk.prev[i].x = snk.prev[i-1].x;
		snk.prev[i].y = snk.prev[i-1].y;
	}

	// draw the prevous head of the snake as the body
	goto_xy(snk.prev[0].x, snk.prev[0].y);
	printf(ANSI_COLOR_GREEN "@" ANSI_COLOR_RESET);

	// erase the tail-end of our snake
	goto_xy(snk.prev[snk.len].x, snk.prev[snk.len].y);
	printf(" ");

	// draw the new head of the snake
	goto_xy(snk.pos.x, snk.pos.y);
	switch (snk.dir)
	{
		case MOVE_UP:
			printf(ANSI_COLOR_GREEN "^" ANSI_COLOR_RESET);
			break;
		case MOVE_DOWN:
			printf(ANSI_COLOR_GREEN "v" ANSI_COLOR_RESET);
			break;
		case MOVE_LEFT:
			printf(ANSI_COLOR_GREEN "<" ANSI_COLOR_RESET);
			break;
		case MOVE_RIGHT:
			printf(ANSI_COLOR_GREEN ">" ANSI_COLOR_RESET);
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