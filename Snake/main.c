﻿#include <stdio.h>

#include <conio.h> 

#include <windows.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#include "snake.h" 



int main() {

	bool food_flag = false; /*음식이 이미 생성되어 있는지 체크하는 변수 */
	int key = RIGHT;
	cell *snake = NULL;
	food apple;

	bool restart;


	do{
		
		snake = NULL;
		restart = false;
 
	    game_init(&snake, &apple, &food_flag);
	
		while (true) {
			
			Sleep(300);

			if (_kbhit()) {
				check_key(&key);
			}

			snake_control(key, snake);	
			check_collision(key, &snake, &apple, &food_flag, &restart);
			render_obj(*snake, apple);

			gotoxy(1, 1);
	
			printf("%d\n", snake->length);
			printf("%d", food_fail(apple, *snake));
		

			if (restart == true) break;

		}
	} while (restart);
 
	return 0;

}
void gotoxy(int x, int y) {

	COORD Pos = { x - 1, y - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

void game_init(cell **snake, food *apple, bool *flag) {

	system("mode con:cols=50 lines=25");
 
	add_cell(snake, create_cell(BOARD_WIDTH/2, BOARD_HEIGHT/2));

	(*snake)->length = 0;

	(*apple) = generate_food(apple, *snake, flag);

	render_snake(**snake);

}

void render_snake(cell head) {
	cell *h = &head;

	while (h) {
		gotoxy(h->x, h->y);
		printf("@");
		h = h->next;
	}
}

void delete_snake(cell head) {

	cell *h = &head;

	while (h) {
		gotoxy(h->x, h->y);
		printf(" ");
		h = h->next;
	}

}


void check_key(int *key) {

	(*key) = _getch();

	if ((*key) == 224) {
		(*key) = _getch();
	}

	return;

}



void display_location(cell *head) {

	cell *h = head;


	while (h) {
		printf("\n(%d, %d)\n", h->x, h->y);
		h = h->next;
	}
}




void render_obj(cell snake, food apple) {

	system("cls");

	render_snake(snake);

	gotoxy(apple.x, apple.y);
	printf("*");

}


bool out_of_board(int key, int x, int y){

	switch (key) {
	case UP:
		if (1 > --y) return true;
		else return false;
		break;

	case DOWN:
		if (BOARD_HEIGHT < ++y) return true;
		else return false;
		break;

	case LEFT:
		if (1 > --x) return true;
		else return false;
		break;

	case RIGHT:
		if (BOARD_WIDTH < ++x) return true;
		else return false;
		break;
	}
	return 0;


}

/* 180도 회전 방지*/
int rotation_fail(int key, cell *c) {

	int cx = c->x;
	int cy = c->y;

	int nx, ny;

	if (c->next == NULL) return 0;

	nx = c->next->x;
	ny = c->next->y;

	switch (key) {
	case UP:
		if (--cy == ny) return DOWN;
		else return false;
		break;

	case DOWN:
		if (++cy == ny) return UP;
		else return false;
		break;

	case LEFT:
		if (--cx == nx) return RIGHT;
		else return false;
		break;

	case RIGHT:
		if (++cx == nx) return LEFT;
		else return false;
		break;

	}
	return false;
}






void move_cell(int key, cell *c) {



	if (out_of_board(key, c->x, c->y)) return;

	switch (key) {
	case UP:
		(c->y)--;
		break;
	case DOWN:
		(c->y)++;
		break;
	case LEFT:
		(c->x)--;
		break;
	case RIGHT:
		(c->x)++;
		break;

	}

}


cell *create_cell(int x, int y) {

	cell *new_cell;
	new_cell = (cell*)malloc(sizeof(cell));

	new_cell->x = x;
	new_cell->y = y;

	return (new_cell);

}

void add_cell(cell **head, cell *new_node) {

	cell *h = *head;


	if (h == NULL) {
		new_node->next = NULL;
		*head = new_node;
	}

	else {
		while (h->next) {
			h = h->next;
		}

		h->next = new_node;
		new_node->next = NULL;
	
	}


}




void follow_head(cell *head) {

	cell *prev = head;
	cell *cur = prev->next;

	int px, py, temp_x, temp_y;


	px = prev->x;
	py = prev->y;


	while (cur) {

		temp_x = cur->x;
		temp_y = cur->y;

		cur->x = px;
		cur->y = py;

		px = temp_x;
		py = temp_y;

		prev = cur;
		cur = cur->next;

	}


}


void snake_control(int key, cell *head) {

	cell *c = head;

	if (rotation_fail(key, head)) {
		key = rotation_fail(key, head);
	}

	switch (key) {

	case UP:
		follow_head(c);
		move_cell(UP, head);
		break;


	case DOWN:
		follow_head(c);
		move_cell(DOWN, head);
		break;

	case LEFT:
		follow_head(c);
		move_cell(LEFT, head);
		break;

	case RIGHT:
		follow_head(c);
		move_cell(RIGHT, head);
		break;
	}
}


bool food_fail(food apple, cell snake) {

	cell *c = snake.next;
	
	while (c) {

		if (apple.x == c->x && apple.y == c->y) {
			return true;
		}
		
		else c = c->next;

	}

	return false;
}


food generate_food(food *apple, cell *snake, bool *flag) {

	food new_apple = { 0,0 };

	int random_x, random_y;

	if ( (*flag) == true) return *apple;
 
	do{
		srand((unsigned)time(NULL));

		random_x = (rand() % BOARD_WIDTH) + 1;
		random_y = (rand() % BOARD_HEIGHT) + 1;

		new_apple.x = random_x;
		new_apple.y = random_y;

		(*flag) = true;

	} while (food_fail(*apple,*snake));
 
	return new_apple;

}


bool meet_food(cell snake, food apple) {

	return (snake.x == apple.x && snake.y == apple.y);

}


void attach_tail(cell **head, int key) {

	cell *prev = *head;

	int px, py;

	while (prev->next) {
		prev = prev->next;
	}

	px = prev->x;
	py = prev->y;

	switch (key) {
	case UP:
		add_cell(head, create_cell(px, py + 2));
		break;

	case DOWN:
		add_cell(head, create_cell(px, py + 1));
		break;

	case RIGHT:
		add_cell(head, create_cell(px - 1, py));
		break;

	case LEFT:
		add_cell(head, create_cell(px + 1, py));
		break;
	}

}


bool collide_itself(cell head) {

	cell *c = head.next;

	if (c == NULL) {
		return false;
	}

	else {

		while (c) {

			if (c->x == head.x && c->y == head.y) {
				return true;
			}

			c = c->next;
		}
	}

	return false;

}

bool collide_with_map(cell head) {

	return (head.x == 1 || head.x == BOARD_WIDTH || head.y == 1 || head.y == BOARD_HEIGHT);

}



void check_collision(int key, cell **head, food *apple, bool *flag, bool *restart) {


	if (meet_food(**head, *apple)) {

		attach_tail(head, key);

		*flag = false;
		*apple = generate_food(apple, *head, flag);

		(*head)->length += 1;

		return;
		
	}

	else if (collide_itself(**head) || collide_with_map(**head)) {

		game_over(restart);
			
	} 

	else return;

}

void game_over(bool *restart) {

	(*restart) = true;

	int HalfWidth = BOARD_WIDTH / 2;
	int HalfHeight = BOARD_HEIGHT / 2;

	system("cls");
	gotoxy(HalfWidth,HalfHeight);
	printf("YOU DIED\n");
	
	Sleep(2000);
	gotoxy(HalfWidth-8, HalfHeight+1);
	printf("please any key to regame");
	getchar();
	
}
