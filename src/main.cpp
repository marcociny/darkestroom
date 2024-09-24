#include "include/methods.hpp"
#include <ctime>
#ifdef _WIN32
    #include <ncurses/ncurses.h>
#elif __linux__
    #include <ncurses.h>
#else
    #error "OS not supported!"
#endif

using namespace std;

int main () {

    // unicode unlock
    setlocale(LC_ALL, "");

    // ncurses initialization
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
    
    // random seed (might move)
    srand(time(0));
    
    // colors for lighting
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLACK+8, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK+8);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
    init_pair(7, COLOR_BLACK, COLOR_RED); // for death sequence
    
    init_pair(10, COLOR_RED, COLOR_BLACK);
    init_pair(11, COLOR_GREEN, COLOR_BLACK);
    init_pair(12, COLOR_BLUE, COLOR_BLACK);
    init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    init_pair(14, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(15, COLOR_CYAN, COLOR_BLACK);
    init_pair(20, COLOR_RED+8, COLOR_BLACK);
    init_pair(21, COLOR_GREEN+8, COLOR_BLACK);
    init_pair(22, COLOR_BLUE+8, COLOR_BLACK);
    init_pair(23, COLOR_YELLOW+8, COLOR_BLACK);
    init_pair(24, COLOR_MAGENTA+8, COLOR_BLACK);
    init_pair(25, COLOR_CYAN+8, COLOR_BLACK);

    gameMap.loadFloor(0);

    int in = 0, res;

    while(1) {
        in = gui.titleScreen(in);

        switch(in) {        
            case 1:
                game.newGame();
            case 0:
                res = game.gameMain();
                if(res == 2) {
                    game.deathSequence();
                }
                else if (res == 3){
                    game.winSequence();
                }
                break;
            case 2:
                gui.settings();
                break;
            case 3:
                gui.credits();
                break;
            case 4:
                endwin();
                return 0;
        }
    }

}