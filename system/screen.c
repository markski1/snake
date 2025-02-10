// "escape" onto the given X and Y characters of the console.
void goto_xy(int x, int y)
{
	printf("%c[%i;%iH", CHAR_ESC, y, x);
}

void print_xy(int x, int y, char text[])
{
	printf("%c[%i;%iH%s", CHAR_ESC, y, x, text);
}

// fill the screen space with void.
void clear_scr()
{
	int i, j;

	for (i = 0; i <= GAME_HEIGHT * 2; ++i)
	{
		print_xy(0, i, "                                                                                    ");
	}

	ms_sleep(250);

	goto_xy(0, 0);
}

void update_score()
{
	goto_xy(GAME_WIDTH + 11, 5);
	printf("%i", snk.len - SNAKE_INITIAL_LENGTH);
}

void create_game_field()
{
	// set field color as BLUE
	printf(ANSI_COLOR_BLUE);
	clear_scr();
	int i, j;
	// print the upper and lower borders border
	print_xy(0, 0, "========================================");
	print_xy(0, GAME_HEIGHT, "========================================");

	// and the side borders, too
	for (i = 0; i < GAME_HEIGHT + 1; ++i)
	{
		print_xy(GAME_WIDTH, i, "|");
		print_xy(0, i, "|");
	}

	// reset color to console default
	printf(ANSI_COLOR_RESET);

	// and off to the right, a score counter.
	print_xy(GAME_WIDTH + 3, 5, "Score: ");

	print_xy(GAME_WIDTH + 5, 2, ANSI_COLOR_CYAN "SNEPK!" ANSI_COLOR_RESET);
}