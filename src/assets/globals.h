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