// all the code here is Windows specific
#include <windows.h>
#include <conio.h>

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

void ms_sleep(int ms) {
    Sleep(ms);
}