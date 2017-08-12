
#include <stdio.h>

#include <conio.h> 

#include <windows.h>

#include <stdlib.h>

#include <time.h>

#include <math.h>

#include "snake.h" 


 
int main() {

	bool food_flag = false; /* 음식이 이미 생성되었는지 체크하는 변수*/
 
	int key = RIGHT;
	int i = 0;
    cell *snake = NULL; 
	food apple;
	cell *tail;

	buf buffer;

	add_cell(&snake, create_cell(20, 20));

	tail = snake;
    
	game_init(*snake, &apple, &buffer, &food_flag);

	
	while (true) {

		Sleep(300);

		if (_kbhit()) {
			check_key(&key);
		}

		snake_control(key, snake);
		check_collision(key, &snake, &apple, &food_flag);
		render_obj(*snake, apple, buffer);

		while (tail->next) {
			tail = tail->next;
		}
 
		gotoxy(1, 1);
		printf("food: (%d, %d)", apple.x, apple.y);
		display_location(snake);
		printf("tail:(%d,%d)", tail->x, tail->y);
		
	}


	return 0;

}
void gotoxy(int x, int y) {

	COORD Pos = { x - 1, y - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

}

void game_init(cell snake, food *apple, buf *buffer, food *flag) {

	
	(*apple) = generate_food(apple, &snake, flag);
 
	buffer->snake = snake;
	buffer->apple = *apple;

	render_snake(snake);
 
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

void display_buffer(buf *b) {
	
	cell *c = &b->snake;
	food *f = &b->apple;
	

	while (c) {
		printf("snake:(%d, %d)\n", c->x, c->y);
		c = c->next; 
	}

	printf("food:(%d,%d)", f->x, f->y);
	
}




void fill_buffer(cell snake, food apple, buf *b) {

	b->apple = apple;
	b->snake = snake;
	
}

/*버퍼에 있는 위치와 달라졌을떄만 새로 그리는 함수*/
void render_obj(cell snake, food apple, buf buffer) {

    cell *new_c = &snake;
	cell *old_c = &buffer.snake;

    food *old_f = &buffer.apple;

	system("cls");

    render_snake(snake);

	gotoxy(apple.x, apple.y);
	printf("*");
 
}

 
bool out_of_board (int key, int x, int y) {

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

/* 뱀 머리가 꼬리쪽으로 향하는 상황 방지*/
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

void add_cell(cell **head, cell *new_node){

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
	
	if (rotation_fail(key,head)) {
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
}


bool food_fail(food *apple, cell *snake) {

	while (snake) {
		
		if (apple->x == snake->x && apple->y == snake->y) return true; 
		snake = snake->next;
	}

	return false;
}


food generate_food(food *apple, cell *snake, bool *flag) {

	food new_apple;

	if ( (*flag) == true) return *apple; /* 먹이가 이미 있으면 생성하지 않음.*/

	do {

		srand((unsigned)time(NULL));

		int random_x = (rand() % BOARD_WIDTH)+1;
		int random_y = (rand() % BOARD_HEIGHT)+1;

		new_apple.x = random_x;
		new_apple.y = random_y;

		(*flag) = true;
	} while (food_fail(apple, snake)); /*먹이가 뱀과 같은 위치에 생성되면 다시 생성*/ 

	return new_apple;
	
}

 
bool meet_food(cell snake, food apple) {

	return (snake.x == apple.x && snake.y == apple.y);

}

int head_direction(cell *head) {

	cell *h = head;
    cell *n = h->next; 

	if (h->x == n->x && h->y == n->y) return ERROR;

	else if (h->x != n->x && h->y != n->y) return ERROR;

	else if (h->y < n->y) return UP;

	else if (h->y > n->y) return DOWN;

	else if (h->x > n->x) return RIGHT;

	else if (h->x < n->x) return LEFT;

	return 0;
 
}

int cell_direction(cell head, cell current, int key) {

	cell *prev = &head; 
	cell *cur = &current;

	while (prev->next) {
		
		if (prev->next == cur) {
			break;
		}
		
		prev = prev->next;
		
	}

	if (&head == cur) return key;

	if (prev->x == cur->x && cur->y == cur->y) return ERROR;

	else if (prev->x != cur->x && prev->y != cur->y) return ERROR;

	else if (prev->x > cur->x) return RIGHT;

	else if (prev->x < cur->x) return LEFT;

	else if (prev->y > cur->y) return UP;

	else if (prev->y < cur->y) return DOWN;
	
 
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
		add_cell(head, create_cell(px, py+2));
		break;

	case DOWN:
		add_cell(head, create_cell(px, py+1));
		break;

	case RIGHT:
		add_cell(head, create_cell(px-1, py));
		break;

	case LEFT:
		add_cell(head, create_cell(px+1, py));
		break;
	}

}

		

void check_collision(int key, cell **head, food *apple, bool *flag) {

		 
	if (meet_food(**head, *apple)) {

		attach_tail(head, key);
		
	    *flag = false;
		*apple = generate_food(apple, head, flag);
		return;
		

	}

    else return;

}
 