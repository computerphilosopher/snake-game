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

	struct cell *prev;

	struct cell *next;
	
}cell;

typedef struct food {
	int x; int y;
}food;


typedef struct buf {

	cell snake;
	food apple;
	
}buf;

void screen_init(cell *snake, food *apple);

void display_location(cell *head); 

void render_obj(cell *head, food *apple);

void gotoxy(int x, int y);

void move_cell(int key, cell *c);

cell *create_cell(int cx, int cy);

void add_cell(cell **snake, cell *new_node);

void follow_head(cell *head);
 
void snake_control(int key, cell *head);

void check_key(int *key); 

bool food_fail(food *apple, cell *snake);

food generate_food(food *apple, cell *snake, bool *flag);

bool meet_food(cell *snake, food *apple);

void eat_food(int key, cell *snake, food *apple, bool *flag);

void attach_tail(cell *head, int direction);

void render_snake(cell *head);

void render_food(food *apple, bool *flag);

void fill_buffer(cell *snake, food *apple, buf *b);

void display_buffer(buf *b);

void game_init(cell *snake, food *apple, buf *buffer, bool *flag);

void screen_flipping(cell *snake, food *apple, buf *buffer);
