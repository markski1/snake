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