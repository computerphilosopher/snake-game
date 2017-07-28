#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SAME 0
#define ERROR -1

#define BOARD_WIDTH 1024 
#define BOARD_HEIGHT 1024
#define STRTING_POINT 512
 

typedef struct cell {

	int cx; int cy;

	struct cell *next;
}cell;

void display_location(cell *head); 

void render_snake(cell *head);

void gotoxy(int x, int y);

void move_cell(int key, cell *c);

cell *create_cell(int cx, int cy);

void add_cell(cell **snake, cell *new_node);

void follow_head(cell *head);


void snake_control(int key, cell *head);

void check_key(int *key);
