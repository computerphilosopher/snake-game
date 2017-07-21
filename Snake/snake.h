#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define BOARD_WIDTH 16
#define BOARD_HEIGHT 16

typedef struct cell {

	int cx; int cy;

	struct cell *next;
}cell;

void display_snake(cell *head);

void gotoxy(int x, int y);

void Cell_Move(int key, int *cx, int *cy);

cell *create_cell(int cx, int cy);

void add_cell(cell **snake, cell *new_node);

void Snake_Control(int key, cell *head);


