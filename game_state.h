bool snake_state_invalid();
void spawn_new_food();
void draw_snake();

void setup_state()
{
	// Spawn the snake in a random location on the left side of the playing field.
	// The snake will spawn at a length of SNAKE_INITIAL_LENGTH, moving to the right.
	snk.pos.x = (rand() % (GAME_WIDTH  / 2)) + 2;
	snk.pos.y = (rand() % (GAME_HEIGHT - 1)) + 3;
	snk.len = SNAKE_INITIAL_LENGTH;
	snk.dir = MOVE_RIGHT;

	update_score();

	spawn_new_food();
}

// every "frame", if you will.
void logic_run()
{
	// record the last location of the snake
	snk.prev[0].x = snk.pos.x;
	snk.prev[0].y = snk.pos.y;

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
		spawn_new_food();
		update_score();
	}
}

bool snake_state_invalid()
{
	// check we're not outside the bounds.
	if (snk.pos.x <= 1 || snk.pos.y <= 1)
	{
		return true;
	}
	if (snk.pos.x >= GAME_WIDTH || snk.pos.y >= GAME_HEIGHT)
	{
		return true;
	}

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

	// erase the tail-end of our snake
	goto_xy(snk.prev[snk.len].x, snk.prev[snk.len].y);
	printf(" ");
}