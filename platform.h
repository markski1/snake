// all the code here is platform specific
// if you were to want to port this to other OS, all that must be changed is in here (i think)
#include <windows.h>
#include <conio.h>

#define BASE_WAIT 100

void set_scrsize() {
    char str[30];
    sprintf(str, "mode %i, %i", GAME_WIDTH + 15, GAME_HEIGHT);
    system(str);
}

// wait a given amount of time, less as the snake becomes longer,
// and check for keyboard input afterwards. update the snake's behaviour if required.
void wait_and_key() {
	int wait_amount = BASE_WAIT - (snk.len * 2);
    if (snk.dir == MOVE_UP || snk.dir == MOVE_DOWN)
        wait_amount *= 1.2;

    if (wait_amount < 25) wait_amount == 25;

	Sleep(wait_amount);

    if (kbhit())
    {
        switch (getch())
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
    }
}

// "escape" onto the given X and Y characters of the console.
void goto_xy(int x, int y)
{
    printf("%c[%i;%iH", CHAR_ESC, y, x);
}