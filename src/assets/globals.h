typedef struct coord {
    int x;
    int y;
}coord;

char player_icon = '@';
coord player_pos = {4, 6};
int current_room = 0;
int current_floor = 0;
int lighter_strength = 5;
bool lighter_on = true;

float REFRESH_RATE = 16.666666;
int FRAMES_PER_SECOND = (1000/REFRESH_RATE);
int LANG_OPTION = 0;
int FRAMES_OPTION = 3;
char keyConfirm = 'z';
char keyToggleLighter = 'x';
short keyUp = 0403, keyDown = 0402, keyLeft = 0404, keyRight = 0405;