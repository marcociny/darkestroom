#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
#include <list>
#include <ncurses.h>
#include <locale.h>
#include "floor_art.h"
#include "floor_lights.h"
#include "floor_collisions.h"
#include "messages.h"
using namespace std;

#define DEBUG_MODE 0

// start of global structures

typedef struct coord {
    int x;
    int y;
}coord;

vector<vector<short>>lightmap;

list<pair<string,int>>message_log;

// function prototypes

void print_centered(WINDOW* win, int line_offset, int col_offset, string str);
void print_messages();
void send_message(string line, int duration);
void clear_lightmap();
void cast_light(int x, int y, int radius, int depth);
void change_floor (int floor_number, string change_text);
void change_room(int room_number, int x, int y);
void event_handler(int room_n, int x, int y);
void move_player(int& in, vector<string>& room);
void HelpMenu ();
int TitleScreen(int start_selected);
void Settings();
void Game ();
int main ();

// start of global variables

// default framerate
float REFRESH_RATE = 16.666666;
int FRAMES_PER_SECOND = (1000/REFRESH_RATE);

// settings

int LANG_OPTION = 0;
int FRAMES_OPTION = 3;

// globals

char player_icon = '@';
coord player_pos;
int current_room;
int current_floor;
int lighter_strength = 5; // 2
bool took_torch = false;
bool lighter_on = true;

// keybinds

char keyConfirm = 'z';
char keyToggleLighter = 'x';
short keyUp = KEY_UP, keyDown = KEY_DOWN, keyLeft = KEY_LEFT, keyRight = KEY_RIGHT;

// start of game functions

// -------------- message logs and printing --------------

void print_centered(WINDOW* win, int line_offset, int col_offset, string str) {
    mvwprintw(win, win->_maxy / 2 + line_offset, win->_maxx / 2 - str.length() / 2 + col_offset, "%s\n", str.c_str());
    return;
}

void print_messages(WINDOW* win) {
    wattron(win, A_BOLD);
    for(auto it = message_log.begin(); it != message_log.end();) {
        if((*it).second <= 0) {
            it = message_log.erase(it);
        }
        else {
            wprintw(win, "\n  %s", (*it).first.c_str());
            (*it).second--;
            it++;
        }
    }
    wattroff(win, A_BOLD);
}

void send_message(string line, int duration) {
    message_log.push_back({line, duration});
}

// ---------------------- lightmap ----------------------

void clear_lightmap() {
    for(int i = 0; i < lightmap.size(); i++) {
        fill(lightmap[i].begin(), lightmap[i].end(), 0);
    }
}

int get_light_level(int depth, int radius) {
    if(depth < radius - 1) {
            return 3;
        }
        else if(depth == radius - 1) {
            return 2;
        }
        else return 1;
}

void _cast_light(int x, int y, int radius, int depth, vector<vector<int>>& visited) {

    typedef struct node {
        int x, y, depth;
    }node;
    queue<node> q;

    q.push({x, y, depth});
    visited[y][x] = true;

    int light_level;

    while(!q.empty()) {

        node curr = q.front();

        light_level = get_light_level(curr.depth, radius);
        
        if(lightmap[curr.y][curr.x] < light_level) {
            lightmap[curr.y][curr.x] = light_level;
        }

        if(floor_collisions[current_floor][current_room][curr.y][curr.x] == 'X') {
            q.pop();
            continue;
        }
        
        if(curr.depth >= radius) {
            q.pop();
            continue;
        }

        if(curr.y != 0 && !visited[curr.y-1][curr.x]) {
            q.push({curr.x, curr.y-1, curr.depth + 1});
            visited[curr.y-1][curr.x] = true;
        }
        if(curr.y != lightmap.size() - 1 && !visited[curr.y+1][curr.x]) {
            q.push({curr.x, curr.y+1, curr.depth + 1});
            visited[curr.y+1][curr.x] = true;
        }
        if(curr.x != 0 && !visited[curr.y][curr.x-1]) {
            if(curr.x % 2) {
                q.push({curr.x-1, curr.y, curr.depth});
            }
            else {
                q.push({curr.x-1, curr.y, curr.depth + 1});
            }
            visited[curr.y][curr.x-1] = true;
        }
        if(curr.x != lightmap[0].size() - 1 && !visited[curr.y][curr.x+1]) {
            if(curr.x % 2) {
                q.push({curr.x+1, curr.y, curr.depth});
            }
            else {
                q.push({curr.x+1, curr.y, curr.depth + 1});
            }
            visited[curr.y][curr.x+1] = true;
        }
        q.pop();
    }
}

void cast_light(int x, int y, int radius) {
    vector<vector<int>> visited(room[current_floor][current_room].size(), vector<int>(room[current_floor][current_room][0].size(), 0));
    _cast_light(x, y, radius, 0, visited);
}

// -------- zone changes and event handler ---------------

void change_floor (int floor_number, string change_text) {
    string floor_text = msgs[LANG_OPTION]["Floor"] + to_string(floor_number);
    current_floor = floor_number;
    WINDOW* txtbox = newwin(LINES,COLS,0,0);
    print_centered(txtbox, -2, 0, floor_text.c_str());
    print_centered(txtbox, 0, 0, change_text.c_str());
    wborder(txtbox, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(txtbox);
    napms(2300);
    delwin(txtbox);
    return;
}

void change_room(int room_number, int x, int y) {
    current_room = room_number;
    lightmap.resize(room[current_floor][current_room].size(), vector<short>(room[current_floor][current_room][0].size()));
    player_pos = {x,y};

    return;
}

void event_handler(int x, int y) {

    auto& active_room = room[current_floor][current_room];

    bool canMove = true;

    switch(current_floor) {
        case 0:
            switch(current_room) {
                case 0:
                if(x == 12 && y == 14) {
                    
                    if(active_room[14][12] == L'╲') {
                        active_room[14][12] = L'╱';
                        send_message(msgs[LANG_OPTION]["SwitchOn"], 60);
                    }
                    else if(active_room[14][12] == L'╱') {
                        active_room[14][12] = L'╲';
                        send_message(msgs[LANG_OPTION]["SwitchOff"], 60);
                    }
                    canMove = false;
                }
                if(x == 22 && y == 2) {
                    wchar_t &c = active_room[y][x];
                    if(c == L'╲') {
                        c = L'╱';
                        send_message(msgs[LANG_OPTION]["SwitchOff"], 60);
                    }
                    else if(c == L'╱') {
                        c = L'╲';
                        send_message(msgs[LANG_OPTION]["SwitchOn"], 60);
                    }
                    canMove = false;
                }
                break;
            }
        
        case 1:
            break;

        default:
        break;
    }

    if(floor_collisions[current_floor][current_room][y][x] != 'X' && floor_collisions[current_floor][current_room][y][x] != 'O' && canMove) {
        player_pos.x += (x - player_pos.x);
        player_pos.y += (y - player_pos.y);
    }

    return;
}

void move_player(int& in, vector<wstring>& room) {
    int x = 0, y = 0;

    if(in == keyLeft) x-=2;
    else if(in == keyUp) y--;
    else if(in == keyRight) x+=2;
    else if(in == keyDown) y++;

    if(in == keyToggleLighter) {
        lighter_on = !lighter_on;
        return;
    }

    event_handler(player_pos.x + x, player_pos.y + y);
    return;
}

// hud and game

void Game () {

    WINDOW* win = newwin((int)LINES * 0.75, COLS,0,0); // screen
    nodelay(stdscr, TRUE);
    keypad(win, TRUE);

    WINDOW* message_log = newwin((int)LINES * 0.25, (int)COLS,LINES * 0.75, 0);

    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');

    wrefresh(win);
    wrefresh(message_log);

    change_floor(0, msgs[LANG_OPTION]["Floor0Splash"]);
    change_room(0, 2, 6);
    
    unsigned int frame = 0;

    int in;
    int last_tick_lines = LINES, last_tick_cols = COLS;

    while(1) {

        if(last_tick_cols != COLS || last_tick_lines != LINES) {
            delwin(win);
            delwin(message_log);

            win = newwin((int)LINES * 0.75, COLS,0,0); // screen
            nodelay(stdscr, TRUE);
            keypad(win, TRUE);

            message_log = newwin((int)LINES * 0.25, (int)COLS,LINES * 0.75, 0);

            wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');
        }

        if(frame%20 == 0) {
            last_tick_lines = LINES;
            last_tick_cols = COLS;
        }

        napms(REFRESH_RATE);
        frame++;

        wclear(win);

        // add lights and print map
        {

        auto& active_room = room[current_floor][current_room];

        clear_lightmap();

        if(lighter_on) {
            cast_light(player_pos.x, player_pos.y, lighter_strength);
        }

        for(int i = 0; i < active_room.size(); i++) {
            for(int j = 0; j < active_room[i].size(); j++) {

                if(floor_lights[current_floor][current_room][i][j] == 46) {
                    continue;
                }

                if(floor_lights[current_floor][current_room][i][j]-48 > 0) {
                    cast_light(j, i, floor_lights[current_floor][current_room][i][j]-48);
                }

            }
        }
        
        for(int i = 0; i < active_room.size(); i++) {
            for(int j = 0; j < active_room[i].size(); j++) {
                
                if(lightmap[i][j] == 0) {
                    wprintw(win, " ");
                    continue;
                }

                if(i == player_pos.y && j == player_pos.x) {
                    wattron(win, COLOR_PAIR(lightmap[i][j]));
                    wprintw(win, "%c", player_icon);
                    wattroff(win, COLOR_PAIR(lightmap[i][j]));
                    continue;
                }

                

                wattron(win, COLOR_PAIR(lightmap[i][j]));
                wprintw(win, "%lc", active_room[i][j]);
                wattroff(win, COLOR_PAIR(lightmap[i][j]));
            }
            wprintw(win, "\n");
        }
        

        }

        if(DEBUG_MODE == 1) {
            wprintw(win, "\n\n");
            for(int i = 0; i < lightmap.size(); i++) {
                for(int j = 0; j < lightmap[0].size(); j++) {
                    wprintw(win, "%d", lightmap[i][j]);
                }
                wprintw(win, "\n");
            }
            wprintw(win, "%d %d", lightmap.size(), lightmap[0].size());
        }

        if(DEBUG_MODE == 2) {
            wprintw(win, "\n\nx: %d y: %d, frame %u, FPS = %d\n", player_pos.x, player_pos.y, frame, FRAMES_PER_SECOND);
        }

        wrefresh(win);
        wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(message_log);
        wclear(message_log);
        print_messages(message_log);

        in = getch();

        move_player(in, room[current_floor][current_room]);

        if(in == KEY_BACKSPACE) {
            // pause menu
            return;
        }
            
    }

    nodelay(stdscr, FALSE);

}

void Credits () {
    WINDOW* win = newwin(LINES,COLS,0,0);
    nodelay(win, FALSE);
    keypad(win, TRUE);

    vector<string>message = {
        "Title screen logo: patorjk.com/software/taag",
        "",
        "Made using the ncurses library",
        "",
        "Game created by Marco Cinieri",
        "",
        "",
        "",
        "PRESS ANY KEY TO GO BACK",
    };

    for(int i = 0; i < message.size(); i++) {
        mvwprintw(win, win->_maxy / 2 - message.size()/2 + i, win->_maxx / 2 - message[i].length() / 2, "%s\n", message[i].c_str());
    }

    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

    wrefresh(win);

    wgetch(win);

    delwin(win);
    return;
}

void KeybindsMenu () {
    WINDOW* win = newwin(LINES,COLS,0,0);
    keypad(win, TRUE);

    

    return;
}

void Settings() {

    WINDOW* win = newwin(LINES,COLS,0,0);
    keypad(win, TRUE);

    vector<string> logo = {
        " ____     __    ____  _  _  ____  ___  ____    ____  _____  _____  __  __ ",
        "(  _ \\   /__\\  (  _ \\( )/ )( ___)/ __)(_  _)  (  _ \\(  _  )(  _  )(  \\/  )",
        " )(_) ) /(__)\\  )   / )  (  )__) \\__ \\  )(     )   / )(_)(  )(_)(  )    ( ",
        "(____/ (__)(__)(_)\\_)(_)\\_)(____)(___/ (__)   (_)\\_)(_____)(_____)(_/\\/\\_)",
    };

    vector<string> options = {
        msgs[LANG_OPTION]["optFramerate"],
        msgs[LANG_OPTION]["optLanguage"],
        msgs[LANG_OPTION]["optKeybinds"],
        msgs[LANG_OPTION]["optBack"],
    };

    vector<int> fps_options = {
        15,
        30,
        45,
        60,
        75
    };

    vector<string> language_options = {
        "English",
        "Italiano"
    };

    int selected = 0, in, logo_offset = 7;

    while(1) {

        wclear(win);

        for(int i = 0; i < logo.size(); i++) {
            print_centered(win, (-logo_offset) + i, 0, logo[i]);
        }

        for(int i = 0; i < options.size(); i++) {
            // selection indicator
            if(i == selected) {
                //print_centered(win, i * 2, -options[i].length()/2 - 2 , ">");
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, ">");
            }
            else mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, " ");//print_centered(win, i * 2, -options[i].length()/2 - 2, " ");
            
            if(i == 0) {
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s%d", options[i].c_str(), fps_options[FRAMES_OPTION]);
            }
            if(i == 1) {
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s%s", options[i].c_str(), language_options[LANG_OPTION].c_str());
            }
            if(i == 2 || i == 3) {
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s", options[i].c_str());
            }
        }

        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(win);
        in = wgetch(win);
        
        if(in == keyDown) {
            selected++;
            selected%=options.size();
        }
        else if(in == keyUp) {
            selected--;
            selected%=options.size();
        }
        else if(in == keyConfirm) {
            switch(selected) {
                case 0:
                FRAMES_OPTION++;
                FRAMES_OPTION %= fps_options.size();
                FRAMES_PER_SECOND = fps_options[FRAMES_OPTION];
                REFRESH_RATE = 1000/FRAMES_PER_SECOND;
                break;

                case 1:
                LANG_OPTION++;
                LANG_OPTION %= language_options.size();
                break;

                case 2:
                KeybindsMenu();
                break;

                case 3:
                return;
                
            }
        }

    }

    
    delwin(win);
    return;

}

int TitleScreen(int start_selected) {

    WINDOW* win = newwin(LINES,COLS,0,0);
    keypad(win, TRUE);
    

    int in;

    vector<string> logo = {
        " ____     __    ____  _  _  ____  ___  ____    ____  _____  _____  __  __ ",
        "(  _ \\   /__\\  (  _ \\( )/ )( ___)/ __)(_  _)  (  _ \\(  _  )(  _  )(  \\/  )",
        " )(_) ) /(__)\\  )   / )  (  )__) \\__ \\  )(     )   / )(_)(  )(_)(  )    ( ",
        "(____/ (__)(__)(_)\\_)(_)\\_)(____)(___/ (__)   (_)\\_)(_____)(_____)(_/\\/\\_)",
    };

    vector<string> options = {
        msgs[LANG_OPTION]["optPlay"],
        msgs[LANG_OPTION]["optSettings"],
        msgs[LANG_OPTION]["optCredits"],
        msgs[LANG_OPTION]["optQuit"],
    };

    int logo_offset = 7;
    int selected = start_selected;

    while(1) {

        wclear(win);

        for(int i = 0; i < logo.size(); i++) {
            print_centered(win, (-logo_offset) + i, 0, logo[i]);
        }

        for(int i = 0; i < options.size(); i++) {
            // selection indicator
            if(i == selected) {
                //print_centered(win, i * 2, -options[i].length()/2 - 2 , ">");
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, ">");
            }
            else mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, " ");//print_centered(win, i * 2, -options[i].length()/2 - 2, " ");
            
            //print_centered(win, i * 2, 0, options[i].c_str());
            mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s", options[i].c_str());
        }

        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(win);

        in = wgetch(win);

        if(in == keyConfirm || in == KEY_ENTER || in == ' ') {
            delwin(win);
            clear();
            return selected;
        }

        if(in == keyUp) {
            selected--;
            selected %= options.size();
        }

        if(in == keyDown) {
            selected++;
            selected %= options.size();
        }
    }
}

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
    
    // colors for lighting
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLACK + 8, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    int in;
    int last_selection = 0;

    while(1) {
        in = TitleScreen(last_selection);

        switch(in) {
            case 0:
                // Play
                Game();
                break;
            case 1:
                // Settings
                Settings();
                last_selection = 1;
                break;
            case 2:
                // Credits
                Credits();
                last_selection = 2;
                break;
            case 3:
                // Quit
                endwin();
                return 0;
        }
    }
    

    return 0;

}
