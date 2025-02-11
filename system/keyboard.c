// The 'keyboard' bit runs on a separate thread.
// This avoids an issue of delay which drives me nuts, usually present in text-based renditions of Snake.
// Instead of doing a input/logic/render loop, I do input as a separate concurrent thing, and inputs are dumped into a "buffer"
// This buffer is then checked by the logic run.

void * handle_keystrokes(void *ptr)
{
	int i;

	for (i = 0; i < KB_BFR_SIZE; ++i)
	{
		movement_buffer[i] = MOVE_NONE;
	}

	while (true)
	{
		// If the game is over, don't capture getch, that way 'press any key to restart' works in the game over prompt.
		if (game_over) {
			ms_sleep(50);
			continue;
		}

		// getch "blocks" (or rather, sleeps/waits) this thread here until keystroke, for which the character is stored.
		char input = getch();

		int entered_move = MOVE_NONE;

		switch (input)
		{
			/*
				Oddity: In testing, arrow keys equivalent to WASD were detected by getch as 'HKPM'.
				So that's what each 3 case for each direction is: WASD accounting for caps and normal, and then arrow.
			*/
			case 'W': case 'w':
			case 'H':
				entered_move = MOVE_UP;
				break;
			case 'S': case 's':
			case 'P':
				entered_move = MOVE_DOWN;
				break;
			case 'A': case 'a':
			case 'K':
				entered_move = MOVE_LEFT;
				break;
			case 'D': case 'd':
			case 'M':
				entered_move = MOVE_RIGHT;
				break;
			case 'O':
			case 'o':
				game_over = true;
		}

		if (entered_move == MOVE_NONE)
			continue;

		for (i = 0; i < KB_BFR_SIZE; ++i)
		{
			if (movement_buffer[i] == MOVE_NONE)
			{
				// do not fill the buffer with the same keystroke, this introduces a lot of delay if a key is held down.
				if (i > 0 && movement_buffer[i - 1] == entered_move) break;
				// if the buffer is empty, do not add a move if we're already going in that direction, this also introduces delay for meaningful inputs.
				if (i == 0)
				{
					if (snk.dir == entered_move) break;
				}
				movement_buffer[i] = entered_move;
				break;
			}
		}
	}
}