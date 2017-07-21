#include <stdio.h>

#include <conio.h> 

#include <windows.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#include "snake.h" 
 
int main() {

	cell *snake=NULL;

	add_cell(&snake, create_cell(3,2));

	add_cell(&snake, create_cell(3,1));

 
	display_snake(snake);
	

	
 
	return 0;
}

void gotoxy(int x, int y) {

	COORD Pos = { x - 1, y - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}


void display_snake(cell *head) {
	
	cell *h = head;

	while (h) {
		printf("(%d, %d)\n", h->cx, h->cy);
		h = h->next;
	}
	
	return;
}



void Cell_Move(int key, int *cx, int *cy) {

	switch (key) {
	case UP:
		gotoxy(*cx,(*cy)++);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("¡Û");

	case DOWN:
		gotoxy(*cx, (*cy)--);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("¡Û");

	case LEFT:
		gotoxy((*cx)--, *cy);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("¡Û");

	case RIGHT:
		gotoxy((*cx)++, *cy);
		printf(" ");
		gotoxy(*cx, *cy);
		printf("¡Û");
	
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

void follow_head_x(int head_x , int *cx, int *cy) {

	
	int i = 0;

	int k = head_x - (*cx);

	if (k > 0) {
		for (i = 0; i < k; i++) {
			Cell_Move(RIGHT, cx, cy);
		}
	}

	else if (k < 0) {
		for (i = 0; i < abs(k); i++) {
			Cell_Move(LEFT, cx, cy);
		}
	}

	else return;

}
		

void follow_head_y(int head_y, int *cx, int *cy) {

	
	
	int i = 0;

	int k = head_y - (*cy);

	if (k > 0) {
		for (i = 0; i < k; i++) {
			Cell_Move(DOWN, cx, cy);
		}
	}

	else if (k < 0) {
		for (i = 0; i < abs(k); i++) {
			Cell_Move(UP, cx, cy);
		}
	}

	else return;

}


	

void Snake_Control(int key, cell *head) {

	cell *c = head;

	int head_x = head->cx;
	int head_y = head->cy;
 
	int i = 0;


	while (c) {

		switch (key) {

		case UP:
			follow_head_x(head_x, &c->cx, &c->cy);
			Cell_Move(UP, &c->cx, &c->cy);
			c = c->next;
			break;


		case DOWN:
			follow_head_x(head_x, &c->cx, &c->cy);
			Cell_Move(DOWN, &c->cx, &c->cy);
			c = c->next;
			break;



		case LEFT:
			follow_head_y(head_y, &c->cx, &c->cy);
			Cell_Move(LEFT, &c->cx, &c->cy);
			c = c->next;
			break;


		case RIGHT:
			follow_head_y(head_y, &c->cx, &c->cy);
			Cell_Move(RIGHT, &c->cx, &c->cy);
			c = c->next;
			break;

		}
	}
}








	









	