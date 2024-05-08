typedef struct coord {
    int x;
    int y;
}coord;

char player_icon = '@';
coord player_pos = {4, 6};
bool movement_lock = false;

int current_room;
int current_floor = 0;
int lighter_strength = 6;

int floor_layout_x = 1;
int floor_layout_y = 1;

int health = 20;
int max_health = 20;

float max_lighter_fuel = 20;
float lighter_fuel = 20;

float lighter_fuel_regen = 0.7;
float lighter_fuel_consumption = 0.1;//1.0;

bool lighter_on = true;

float REFRESH_RATE = 16.666666;
int FRAMES_PER_SECOND = (1000/REFRESH_RATE);
int LANG_OPTION = 0;
int FRAMES_OPTION = 3;

char keyConfirm = 'z';
char keyToggleLighter = 'x';
short keyUp = 0403, keyDown = 0402, keyLeft = 0404, keyRight = 0405;
