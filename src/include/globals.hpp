#pragma once

typedef struct coord {
    int x;
    int y;
}coord;

int currentRoom;
int currentFloor;

float REFRESH_RATE = 16.666666;
int FRAMES_PER_SECOND = (1000/REFRESH_RATE);
int LANG_OPTION = 0;
int FRAMES_OPTION = 3;

bool ENABLE_LIGHTER_BAR = false;
bool ENABLE_HEALTH_BAR = false;

char keyConfirm = 'z';
char keyDeny = 'x';
char keyPause = 'q';
short keyUp = 0403, keyDown = 0402, keyLeft = 0404, keyRight = 0405;