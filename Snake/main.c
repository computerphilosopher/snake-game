
#include <stdio.h>

#include <conio.h> 

#include <windows.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#include "snake.h" 

#include<stdbool.h>
 
int main() {

	cell *snake = NULL;

	int key = RIGHT;
	int i=0;

	add_cell(&snake, create_cell(2,1 ));
	add_cell(&snake, create_cell(1,1 ));

	while (1) {
		Sleep(300);

		snake_control(RIGHT, snake);


	}
	return 0;

}
void gotoxy(int x, int y) {

	COORD Pos = { x - 1, y - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}




void display_location(cell *head) {
	
	cell *h = head;

	while (h) {
		printf("(%d, %d)\n", h->cx, h->cy);
		h = h->next;
	}
	
	return;
}

void render_snake(cell *head) {

	cell *c = head;
	
	system("cls");

	while (c) {
		
		gotoxy(c->cx, c->cy);
		printf("○");
		c = c->next;
	}

	
}

bool out_of_board (int key, int cx, int cy) {

	switch (key) {
	case UP:
		if (1 > --cy) return true;
		else return false;

	case DOWN:
		if (BOARD_HEIGHT < ++cy) return true;
		else return false;

	case LEFT:
		if (1 > --cx) return true;
		else return false;

	case RIGHT:
		if (BOARD_WIDTH < ++cx) return true;
		else return false;
	}
		

	}



void move_cell(int key, int *cx, int *cy) {

	if (out_of_board(key, *cx, *cy)) return;

	switch (key) {
	case UP:
		(*cy)--;
	case DOWN:
		 (*cy)++;
	case LEFT:
		(*cx)--;
	case RIGHT:
		(*cx)++;

			}

 } 


cell *create_cell(int cx, int cy) { 
	
	cell *new_cell;
	new_cell = (cell*)malloc(sizeof(cell));

    new_cell->cx = cx; new_cell->cy = cy;

	

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


int prev_cell_location(cell *prev) {	

	cell *cur = prev->next;

	if (prev->cx != cur->cx && prev->cy != cur->cy) {
		return ERROR;
	}
	
	if (prev->cx == cur->cx && prev->cy == cur->cy) {
		return SAME;
	}

	if (prev->cx > cur->cx) {
		return RIGHT;
	}

	else if (prev->cx < cur->cx) {
		return LEFT;
	}

	else if (prev->cy > cur->cy) {
		return DOWN ;
	}

	else if (prev->cy > cur->cy) {
		return UP;
	}


	
	}

void follow_head(cell *head) {

	cell *prev = head;
	cell *cur = prev->next;

	while (cur) {

		switch (prev_cell_location(prev)) {
		case UP: 
			move_cell(UP, &cur->cx, &cur->cy);
			break;
		
		case DOWN:
			move_cell(DOWN, &cur->cx, &cur->cy);
			break;

		case LEFT:
			move_cell(LEFT, &cur->cx, &cur->cy);
			break;

		case RIGHT: 
			move_cell(RIGHT, &cur->cx, &cur->cy);
			break;

		case SAME:
			return;
			break;

		case ERROR:
			fprintf(stderr, "세포 위치 에러");
			break;
			
		}

		prev = cur;
		cur = cur->next;
		
	}

 
}

	

void snake_control(int key, cell *head) {

	cell *c = head;

	int i = 0;


		switch (key) {

		case UP:
			follow_head(c);
			move_cell(UP, &c->cx, &c->cy);
			
			render_snake(head);
			break;


		case DOWN:
			
			follow_head(c);
			move_cell(DOWN, &c->cx, &c->cy);
			render_snake(head);
			break;



		case LEFT:

			follow_head(c); 	
			move_cell(LEFT, &c->cx, &c->cy);
			render_snake(head);
			break;


		case RIGHT:
			
			follow_head(c);
			move_cell(RIGHT, &c->cx, &c->cy);
			render_snake(head);
			
			break;

		}
	}









	









	