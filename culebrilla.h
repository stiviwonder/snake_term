#define GRID 8
#define SPEED 200
#define R 0
#define L 1
#define U 2
#define D 3

typedef struct Coord {
	int x;
	int y;
} coord_t;

typedef struct Snake {
	coord_t body[GRID*GRID];
	int length;
	int die;
} snake_t;

typedef struct Food {
	coord_t pos;
	int eaten;
} food_t;

extern char board[GRID][GRID];

//snake_t snake;
//int die;
//
//coord_t food;
//int eaten;
//
//int dir; // 0 der, 1 izq, 2 arr, 3 abj

void leds_on (int x, int y);
void leds_off(int x, int y);
void change_direction(int * dir);

void startup_board();
void print_board();
void update_board(snake_t * snake, food_t * food);
int rand_in_range(int min, int max);
snake_t spawn_snake();
void move_snake(snake_t * snake, int dir);
int is_in_snake(coord_t * c, snake_t * snake);
void eat(snake_t * snake, food_t * food);
void spawn_food (food_t * food, snake_t * snake);
