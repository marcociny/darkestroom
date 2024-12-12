#pragma once
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <climits>
#include <algorithm>
#include <list>
#include <ncurses.h>
#include <locale.h>
#include "globals.hpp"
#include "../assets/logo.hpp"
#include "../assets/messages.hpp"
#include "../assets/game_map.hpp"
#include "spinning_wheel.cpp"
#include "custom_ncurses.hpp"

#define DEBUG_MODE 0 // 0 - 4

#define DEBUG_VAR1 currentFloor 
#define DEBUG_VAR2 currentRoom
#define DEBUG_VAR3 gameMap.lightmap.size()

#define DEBUG_VAR1_TYPE "1: %d"
#define DEBUG_VAR2_TYPE "2: %d"
#define DEBUG_VAR3_TYPE "3: %d"

void print_centered(WINDOW* win, int line_offset, int col_offset, string str) {
    mvwprintw(win, getmaxy(win) / 2 + line_offset, getmaxx(win) / 2 - str.length() / 2 + col_offset, "%s\n", str.c_str());
    return;
}

class MessageLog {
	private:

	list<pair<string,int>> messageLog;
	
	
	public:

    /*----------------------------------------------*/
    void printMessages(WINDOW* win);
	void sendMessage(const char* line, int duration);
	void sendMessage(char* line, int duration);
	/*----------------------------------------------*/
		
}messageLog;

class Player {
    private:

    coord pos = {4, 10};
    
    bool lighterOn = true;
    bool movementLock = false;

    public:

    wchar_t icon = L'@';
    short facingDirection = 2;

    int health = ENABLE_HEALTH_BAR == true ? 20 : INT_MAX/2;
    float lighterFuel = ENABLE_LIGHTER_BAR == true ? 20 : INT_MAX/2;
    int maxHealth = ENABLE_HEALTH_BAR == true ? 20 : INT_MAX/2;
    float maxLighterFuel = ENABLE_LIGHTER_BAR == true ? 20 : INT_MAX/2;
    int lighterStrength = 6;
    float lighterFuelRegen = 0.7;
    float lighterFuelConsumption = 0.1;

    /*----------------------------------------------*/
    coord getPos();
    void setPos(int x, int y);
    void addHealth(int val);
    void setHealth(int val);
    void addLighterFuel(float val);
    void setLighterFuel(float val);
    void lockMovement();
    void move(int& in);
    void unlockMovement();
    bool isMovementLocked();
    void toggleLighter();
    bool isLighterOn();
    /*----------------------------------------------*/
    
}player;

class GUI {
    private:


    public:

    /*----------------------------------------------*/
    class MessageBox {
        private:
        void openAnim();
        void style();
        void writeMessage(wstring);
        WINDOW *messageBox;

        public:
        int borderStyle, borderColor, textStyle, textColor;
        wstring message;
        

        MessageBox(int borderStyle, int borderColor, int textStyle, int textColor) {
            this->borderStyle = borderStyle;
            this->borderColor = borderColor;
            this->textStyle = textStyle;
            this->textColor = textColor;
        }
        void send(wstring);

    };
    int pauseMenu();
    void credits();
    void keybindsMenu();
    void settings();
    int titleScreen(int start_selected);
    
    void cutscene(int);
    void setCG(int);
    void showBanner(string);
    /*----------------------------------------------*/
}gui;

class Map {
    private:

    public:

    bool fullbright = false;
    int floorLayoutX;
    int floorLayoutY;

    floor_data floor;

    vector<vector<short>>lightmap;

    /*----------------------------------------------*/
    void toggleFullbright();
    void loadFloor(int floor_n);
    void changeFloor(int floor_number, string change_text);
    void changeRoom(int room_number, int x, int y);
    void initFloorPickups(int floor_n);
    int spawnPickup(pickup p, int type, int x, int y, int room_n);
    void resetTile(int x, int y);
    void clearLightmap();
    int getLightLevel(int depth, int radius);
    void castLight(int x, int y, int radius);
    void castLightDirectional(int x, int y, int radius, int direction);
    void _castLight(int x, int y, int direction, int radius, int depth, vector<vector<int>>& visited);
    /*----------------------------------------------*/
    
}gameMap;

class Game {

    private:

    public:

    WINDOW* win;
    WINDOW* message_log;

    /*----------------------------------------------*/
    void init() {
        win = newwin((int)LINES * 0.75, COLS,0,0);
        nodelay(stdscr, TRUE);
        keypad(win, TRUE);

        message_log = newwin((int)LINES * 0.25, (int)COLS,LINES * 0.75, 0);;
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(win);
        wrefresh(message_log);
    }
    void introduction();
    void newGame();
    void checkForCutscenes();
    int update();
    int gameMain();
    void eventHandler(int x, int y);
    void deathSequence();
    void winSequence();
    void renderMap();
    void initPlayer();
    void validateScreenSize();
    /*----------------------------------------------*/

}game;

class Entity {
    public:

    coord pos;
    wchar_t icon;
    char color;
    char ID;
    int movementBehavior;
    int facingDirection;

    /*----------------------------------------------*/
    short canMove(int, int);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void patrolBehavior();
    /*----------------------------------------------*/
};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
