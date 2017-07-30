
#include <stdio.h>

#include <conio.h> 

#include <windows.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#include "snake.h" 


 
int main() {

	cell *snake = NULL;
    
	food apple;

	bool food_already = false;
	

	int key=0;
	int i=0;

	

	add_cell(&snake, create_cell(9, 10));
	add_cell(&snake, create_cell(10, 10));

	
		
	while (1) {
		Sleep(300);

		if(_kbhit()) check_key(&key);
		
		snake_control(key, snake);

		generate_food(&apple, snake, &food_already);

		render_food(&apple);
	
		
	} 
	

	return 0;

}
void gotoxy(int x, int y) {

	COORD Pos = { x - 1, y - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

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

	gotoxy(1, 1);

	while (h) {
		printf("\n(%d, %d)\n", h->x, h->y);
		h = h->next;
	}
	
	return;
}

void render_snake(cell *head) {

	cell *c = head;
	
	system("cls");
	while (c) {
		
		gotoxy(c->x, c->y);
		printf("@");

		c = c->next;
	}
 
}


void render_food(food *apple) {
	
	gotoxy(apple->x, apple->y);
	printf("o");
}

bool out_of_board (int key, int x, int y) {

	switch (key) {
	case UP:
		if (1 > --y) return true;
		else return false;

	case DOWN:
		if (BOARD_HEIGHT < ++y) return true;
		else return false;
		
	case LEFT:
		if (1 > --x) return true;
		else return false;

	case RIGHT:
		if (BOARD_WIDTH < ++x) return true;
		else return false;
	}
	return 0;
		

	}

/* 뱀 머리가 꼬리쪽으로 향하는 상황 방지*/
int rotation_fail(int key, cell *c) {

	int cx = c->x;
	int cy = c->y;

	int nx = c->next->x;
	int ny = c->next->y;

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

    new_cell->x = x; new_cell->y = y;

	

	return (new_cell);
 
}

void add_cell(cell **head, cell *new_node){

	cell *h = *head;
	

	if (h == NULL) {
		new_node->next = NULL;
		*head = new_node;
	}

	else {
		while (h->next!=NULL) {
			h = h->next;
			}

	h->next = new_node;
	new_node->next = NULL;

		
	}

 
}




void follow_head(cell *head) {

	cell *prev = head;
	cell *cur = prev->next;

	while (cur) {

		cur->x = prev->x;
		cur->y = prev->y;
	

		prev = cur;
		cur = cur->next;
		
	}

 
}

	
void snake_control(int key, cell *head) {

	cell *c = head;
	
	if (rotation_fail(key, head)) {
		key = rotation_fail(key,head);
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

		render_snake(head);
		
			}


bool food_fail(food *apple, cell *snake) {

	while (snake) {
		
		if (apple->x == snake->x && apple->y == snake->y) return true;

		snake = snake->next;
	}

	return false;
}


void generate_food(food *apple, cell *snake, bool *flag) {

	if ( (*flag) == true) return; /* 먹이가 이미 있으면 생성하지 않음.*/

	do {

		srand((unsigned)time(NULL));

		int random_x = (rand() % BOARD_WIDTH - 1) + 1;
		int random_y = (rand() % BOARD_HEIGHT - 1) + 1;

		apple->x = random_x;
		apple->y = random_y;

	} while (food_fail(apple, snake)); /*먹이가 뱀과 같은 위치에 생성되면 다시 생성*/

	(*flag) = true;

	
}

 
bool function (cell *snake, food *apple){}
