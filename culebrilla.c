#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "culebrilla.h"

void leds_on (int x, int y) {
	board[y][x] = '*'; }
void leds_off(int x, int y) {
	board[y][x] = '-';
}
void change_direction(int * dir) {
	initscr();
	cbreak();
	noecho();
	timeout(SPEED);
	keypad(stdscr, TRUE);
	switch(getch()) {
		case 'w':
		case 'W':
		case KEY_UP:
			if (*dir != D)
				*dir = U;
			break;
		case 'a':
		case 'A':
		case KEY_LEFT:
			if (*dir != R)
				*dir = L;
			break;
		case 's':
		case 'S':
		case KEY_DOWN:
			if (*dir != U)
				*dir = D;
			break;
		case 'd':
		case 'D':
		case KEY_RIGHT:
			if (*dir != L)
				*dir = R;
			break;
		default:
			break;
	}
	endwin();
}

void startup_board() {
	int i, j;
	for (i=0; i<GRID; i++) {
		for (j=0; j<GRID; j++) {
			leds_off(i, j);
		}
	}

}

void print_board() {
	int i, j;
	system("clear");
	for (i=0; i<GRID; i++) {
		for (j=0; j<GRID; j++) {
			if (board[i][j] == '*')
				printf("\x1b[31m");

			printf("%c \x1b[0m",board[i][j]);
		}
		printf("\n");
	}
}

void update_board(snake_t * snake, food_t * food) {
	int i;
	coord_t s_pos;

	for (i=0; i<snake->length; i++) {
		s_pos = snake->body[i];
		leds_on(s_pos.x, s_pos.y);
	}
	
	leds_on(food->pos.x, food->pos.y);
}

int rand_in_range(int min, int max) {
	return (rand()%(max - min + 1)) + min;
}

snake_t spawn_snake() {
	snake_t snake;
	coord_t head;
	head.x = rand_in_range(0, GRID-1);
	head.y = rand_in_range(0, GRID-1);

	printf("SNAKE: x = %d, y = %d\n", head.x, head.y);

	snake.body[0] = head;
	snake.length = 1;
	snake.die = 0;

	return snake;
}

void move_snake(snake_t * snake, int dir) {
	int i;
	coord_t head_next = snake->body[0];

	switch (dir) {
		case R:
			head_next.x = (head_next.x + 1) % GRID;
			break;
		case L:
			if (head_next.x == 0) 
				head_next.x = GRID-1;
			else 
				head_next.x--;
			break;
		case D:
			head_next.y = (head_next.y + 1) % GRID;
			break;
		case U:
			if (head_next.y == 0) 
				head_next.y = GRID-1;
			else 
				head_next.y--;
			break;
	}

	for (i=snake->length-1; i>0; i--) {
		snake->body[i] = snake->body[i-1];
	}

	// check if is is dead
	if (is_in_snake(&head_next, snake)) {
		snake->die = 1;
	}
	snake->body[0] = head_next;

}

int is_in_snake(coord_t * c, snake_t * snake) {
	int i;
	for (i=0; i<snake->length; i++) {
		if (snake->body[i].x == c->x && snake->body[i].y == c->y) {
			return 1;
		}
	}
	return 0;
}

void eat(snake_t * snake, food_t * food) {
	if (snake->body[0].x == food->pos.x && snake->body[0].y == food->pos.y) {
		food->eaten = 1;
		snake->body[snake->length] = snake->body[0];
		snake->length ++;
		printf("AM AM AM AMM length = %d\n", snake->length);
	}
}

void spawn_food (food_t* food, snake_t * snake) {
	while (is_in_snake(&(food->pos), snake)) {
		food->pos.x = rand_in_range(0, GRID-1);
		food->pos.y = rand_in_range(0, GRID-1);
	}

	food->eaten = 0;
	printf("FOOD: x = %d, y = %d\n", food->pos.x, food->pos.y);
}
