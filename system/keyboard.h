// runs on it's own thread
void * handle_keystrokes(void *ptr) {
    while (true) {
        char input = getch();

        if (keystroke_unread) continue;
        
        switch (input)
        {
            // on each key, make sure we're not moving the opposite direction.
            // snake can't do a 180 into itself.
            case 'W':
            case 'w':
                if (snk.dir != MOVE_DOWN) {
                    keystroke_unread = true;
                    snk.dir = MOVE_UP;
                }
                break;
            case 'S':
            case 's':
                if (snk.dir != MOVE_UP) {
                    keystroke_unread = true;
                    snk.dir = MOVE_DOWN;
                }
                break;
            case 'A':
            case 'a':
                if (snk.dir != MOVE_RIGHT) {
                    keystroke_unread = true;
                    snk.dir = MOVE_LEFT;
                }
                break;
            case 'D':
            case 'd':
                if (snk.dir != MOVE_LEFT) {
                    keystroke_unread = true;
                    snk.dir = MOVE_RIGHT;
                }
                break;
            // escape exits the game.
            case 'O':
            case 'o':
                game_over = true;
        }
    }
}