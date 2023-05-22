typedef struct Snake snake;
typedef struct Coords coords;

struct Coords {
	int x;
	int y;
};

struct Snake {
	coords  pos;       // position
	coords  prev[256]; // previous positions
	int     dir;       // direction
	int     len;       // length
};

#define KEY_UP      72
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_DOWN    80

#define MOVE_UP     1
#define MOVE_DOWN   2
#define MOVE_LEFT   3
#define MOVE_RIGHT  4

#define GAME_WIDTH  50
#define GAME_HEIGHT 25

#define CHAR_ESC    27

#define SNAKE_INITIAL_LENGTH 3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"