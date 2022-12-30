#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "culebrilla.h"

char board[GRID][GRID];

int main (int argc, char *argv[]) {
	coord_t s_pos;
	int dir;

	snake_t snake;
	food_t food;

	// para empezar en una direccion
	dir = R; 

	srand(0);


	startup_board();
	snake = spawn_snake();
	spawn_food(&food, &snake);

	while (snake.die == 0) {
		change_direction(&dir);

		// TODO: pensar mas elegante
		s_pos = snake.body[snake.length - 1];
		leds_off(s_pos.x, s_pos.y);
		move_snake(&snake, dir);

		eat(&snake, &food);

		if (food.eaten == 1) {
			spawn_food(&food, &snake);
		}

		update_board(&snake, &food);
		print_board();
		printf("\n");
		//sleep(1);
	}
	printf("MORISTE :(\n");
}
