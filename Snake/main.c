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

	add_cell(&snake, create_cell(2,1 ));
	add_cell(&snake, create_cell(1,1 ));

	Snake_Control(key, snake);
	
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

void display_snake(cell *head) {

	cell *c = head;

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



void Cell_Move(int key, int *cx, int *cy) {

	if (out_of_board(key, *cx, *cy)) return;

	switch (key) {
	case UP:
		gotoxy(*cx,(*cy)--);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("○");

	case DOWN:
		gotoxy(*cx, (*cy)++);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("○");

	case LEFT:
		gotoxy((*cx)--, *cy);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("○");

	case RIGHT:
		gotoxy((*cx)++, *cy);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("○");
	
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

void follow_prev_cell(cell *head) {

	cell *prev = head;
	cell *cur = prev->next;

	while (cur) {

		switch (prev_cell_location(prev)) {
		case UP: 
			Cell_Move(UP, &cur->cx, &cur->cy);
			break;
		
		case DOWN:
			Cell_Move(DOWN, &cur->cx, &cur->cy);
			break;

		case LEFT:
			Cell_Move(LEFT, &cur->cx, &cur->cy);
			break;

		case RIGHT: 
			Cell_Move(RIGHT, &cur->cx, &cur->cy);
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

	

void Snake_Control(int key, cell *head) {

	cell *c = head;

	int head_x = head->cx;
	int head_y = head->cy;
 
	int i = 0;


		switch (key) {

		case UP:
			follow_prev_cell(c);
			
			Cell_Move(UP, &c->cx, &c->cy);
			break;


		case DOWN:
			follow_prev_cell(c);
			Cell_Move(DOWN, &c->cx, &c->cy);
			
			break;



		case LEFT:
			follow_prev_cell(c); 
			Cell_Move(LEFT, &c->cx, &c->cy);
			
			break;


		case RIGHT:
			
			follow_prev_cell(c);
			Cell_Move(RIGHT, &c->cx, &c->cy);
			
			
			break;

		}
	}









	









	