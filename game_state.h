bool snake_state_invalid();
void spawn_new_food();
void draw_snake();
void logic_wait();
void wall_check();
void setup_state();
void logic_run();

#define BASE_WAIT   96

#define KB_BFR_SIZE 3

#define MOVE_NONE   0
#define MOVE_UP     1
#define MOVE_DOWN   2
#define MOVE_LEFT   3
#define MOVE_RIGHT  4

#define GAME_WIDTH  40
#define GAME_HEIGHT 20

#define CHAR_ESC    27

#define SNAKE_INITIAL_LENGTH 4

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct Snake snake;
typedef struct Coords coords;

struct Coords {
	int x;
	int y;
};

struct Snake {
	coords  pos;       // position
	coords  prev[GAME_WIDTH*GAME_HEIGHT]; // previous positions
	int     dir;       // direction
	int     len;       // length
	int     spe;       // speed
};

// globals
snake   snk;
coords  food;
bool    game_over = false;
int     movement_buffer[KB_BFR_SIZE];