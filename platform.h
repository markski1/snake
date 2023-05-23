// all the code here is platform specific
// if you were to want to port this to other OS, all that must be changed is in here (i think)
#include <windows.h>
#include <conio.h>

#define BASE_WAIT 100

void set_scrsize() {
    char str[30];
    sprintf(str, "mode %i, %i", GAME_WIDTH + 15, GAME_HEIGHT);
    system(str);

    SetConsoleTitle("SNEPK!");
}

// wait a given amount of time, less as the snake becomes longer,
// and check for keyboard input afterwards. update the snake's behaviour if required.
void wait_and_key()
{
	int wait_amount = BASE_WAIT - (snk.len * 2);

    // if moving vertically slow things down, since vertical characters are higher
    if (snk.dir == MOVE_UP || snk.dir == MOVE_DOWN)
        wait_amount *= 1.3;

    if (wait_amount < 32) wait_amount == 32;
    else if (wait_amount < 50) wait_amount * 1.07;
    else if (wait_amount < 75) wait_amount * 1.15;
    
	Sleep(wait_amount);
}

// "escape" onto the given X and Y characters of the console.
void goto_xy(int x, int y)
{
    printf("%c[%i;%iH", CHAR_ESC, y, x);
}

// runs on it's own thread
void * handle_keystrokes(void *ptr) {
    while (true) {
        char input = getch();

        switch (input)
        {
            // on each key, make sure we're not moving the opposite direction.
            // snake can't do a 180 into itself.
            case KEY_UP:
                if (snk.dir != MOVE_DOWN)
                    snk.dir = MOVE_UP;
                break;
            case KEY_DOWN:
                if (snk.dir != MOVE_UP)
                    snk.dir = MOVE_DOWN;
                break;
            case KEY_LEFT:
                if (snk.dir != MOVE_RIGHT)
                    snk.dir = MOVE_LEFT;
                break;
            case KEY_RIGHT:
                if (snk.dir != MOVE_LEFT)
                    snk.dir = MOVE_RIGHT;
                break;
            // escape exits the game.
            case CHAR_ESC:
                game_over = true;
        }

        // quick sleep this thread to avoid illegal states if keys are switched too fast
        int wait_amount = BASE_WAIT - (snk.len * 2);
        if (wait_amount < 30) wait_amount = 30;
        Sleep(wait_amount / 2);
    }
}