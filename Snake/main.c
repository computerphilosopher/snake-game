
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

	int key=0;
	int i=0;

	add_cell(&snake, create_cell(9, 10));
	add_cell(&snake, create_cell(10, 10));

	
		
	while (1) {
		Sleep(300);
		if(_kbhit()) check_key(&key);
		snake_control(key, snake);
		
		render_snake(snake);

		
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

	while (h) {
		printf("\n(%d, %d)\n", h->cx, h->cy);
		h = h->next;
	}
	
	return;
}

void render_snake(cell *head) {

	cell *c = head;
	
	system("cls");
	while (c) {
		
		gotoxy(c->cx, c->cy);
		printf("@");

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
	return 0;
		

	}



void move_cell(int key, cell *c) {

	

	if (out_of_board(key, c->cx, c->cy)) return;

	switch (key) {
	case UP:
		(c->cy)--;
		break;
	case DOWN:
		(c->cy)++;
		break;
	case LEFT:
		(c->cx)--;
		break;
	case RIGHT:
		(c->cx)++;
		break;

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




void follow_head(cell *head) {

	cell *prev = head;
	cell *cur = prev->next;

	while (cur) {

		cur->cx = prev->cx;
		cur->cy = prev->cy;
	

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
			move_cell(UP, head);
			
			render_snake(head);
			break;


		case DOWN:
			
			follow_head(c);
			move_cell(DOWN, head);
			render_snake(head);
			break;



		case LEFT:

			follow_head(c); 	
			move_cell(LEFT, head);
			render_snake(head);
			break;


		case RIGHT:
			
			follow_head(c);
			move_cell(RIGHT, head);
			render_snake(head);
			
			break;

		}
	}









	









	