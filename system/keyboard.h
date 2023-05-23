// runs on it's own thread
void * handle_keystrokes(void *ptr) {
    while (true) {
        char input = getch();

        switch (input)
        {
            // on each key, make sure we're not moving the opposite direction.
            // snake can't do a 180 into itself.
            case 'W':
            case 'w':
                if (snk.dir != MOVE_DOWN)
                    snk.dir = MOVE_UP;
                break;
            case 'S':
            case 's':
                if (snk.dir != MOVE_UP)
                    snk.dir = MOVE_DOWN;
                break;
            case 'A':
            case 'a':
                if (snk.dir != MOVE_RIGHT)
                    snk.dir = MOVE_LEFT;
                break;
            case 'D':
            case 'd':
                if (snk.dir != MOVE_LEFT)
                    snk.dir = MOVE_RIGHT;
                break;
            // escape exits the game.
            case 'O':
            case 'o':
                game_over = true;
        }

        // quick sleep this thread to avoid illegal states if keys are switched too fast
        int wait_amount = BASE_WAIT - (snk.len * 2);
        if (wait_amount < 30) wait_amount = 30;
        ms_sleep(wait_amount - (wait_amount / 4));
    }
}