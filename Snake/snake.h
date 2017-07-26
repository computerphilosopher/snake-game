#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SAME 0
#define ERROR -1

#define BOARD_WIDTH 32 
#define BOARD_HEIGHT 32
 

typedef struct cell {

	int cx; int cy;

	struct cell *next;
}cell;

void display_location(cell *head); 

void display_snake(cell *head);

void gotoxy(int x, int y);

void Cell_Move(int key, int *cx, int *cy);

cell *create_cell(int cx, int cy);

void add_cell(cell **snake, cell *new_node);

void follow_head_x(int head_x, cell *c);

void follow_head_y(int head_y, cell *c);

void Snake_Control(int key, cell *head);


