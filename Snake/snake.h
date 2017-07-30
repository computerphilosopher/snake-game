#include <stdbool.h>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SAME 0
#define ERROR -1

#define BOARD_WIDTH 100 
#define BOARD_HEIGHT 100
#define STRTING_POINT 512
 
#define FOOD_COUNT  15

typedef struct cell {

	int x; int y;

	struct cell *next;
	
}cell;

typedef struct food {
	int x; int y;
}food;

void display_location(cell *head); 

void render_snake(cell *head);

void gotoxy(int x, int y);

void move_cell(int key, cell *c);

cell *create_cell(int cx, int cy);

void add_cell(cell **snake, cell *new_node);

void follow_head(cell *head);
 
void snake_control(int key, cell *head);

void check_key(int *key); 

bool food_fail(food *apple, cell *snake);

void generate_food(food *apple, cell *snake, bool *flag);

void render_food(food *apple);