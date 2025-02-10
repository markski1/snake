// all the code here is Windows specific
#include <synchapi.h>
#include <conio.h>

void set_scrsize()
{
	char str[30];
	sprintf(str, "mode %i, %i", GAME_WIDTH + 15, GAME_HEIGHT);
	system(str);

	// hide cursor
	printf("\e[?25l");

	// set title
	printf("\033]0; SNEPK! \007");
}

void ms_sleep(int ms)
{
	Sleep(ms);
}
