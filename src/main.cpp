#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
#include <list>
#include <ncurses.h>
#include <locale.h>
#include "assets/logo.h"
#include "assets/messages.h"
#include "assets/save_file_manager.cpp"
#include "assets/floor_loader.cpp"
#include "assets/spinning_wheel.cpp"

using namespace std;

#define DEBUG_MODE 0

// global structures

vector<vector<short>>lightmap;

list<pair<string,int>>message_log;

// function prototypes

void print_centered(WINDOW*, int, int, string);
void print_messages(WINDOW*);
void send_message(string, int);
void clear_lightmap();
int get_light_level(int, int);
void _cast_light(int, int, int, int, vector<vector<int>>&);
void cast_light(int, int, int);
void change_floor (int, string);
void change_room(int, int, int);
void event_handler(int, int);
void move_player(int&, vector<string>&);
void add_lighter_fuel(int);
void set_lighter_fuel(int);
void Introduction();
int TitleScreen(int);
int PauseMenu();
void Settings();
void Game ();
int main ();

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

// Directions:
// 1 2 3
// 4 0 5
// 6 7 8
void _cast_light2(int x, int y, int direction, int radius, int depth, vector<vector<int>>& visited) {
    int light_level = get_light_level(depth, radius);
    auto& active_room = floors[current_floor].room[current_room];

    if(y < 0 || y >= active_room.art.size()) return;
    if(x < 0 || x >= active_room.art[0].size()) return;

    if(visited[y][x]) {
        return;
    }
    visited[y][x] = true;

    if(lightmap[y][x] < light_level) {
        lightmap[y][x] = light_level;
    }

    if(active_room.collisions[y][x] == 'X') return;
    if(depth >= radius) return;

    switch(direction) {
        case 0:
        _cast_light2(x-1, y-1, 1, radius, depth+1+!(x%2), visited);
        _cast_light2(x, y-1, 2, radius, depth+1, visited);
        _cast_light2(x+1, y-1, 3, radius, depth+1+!(x%2), visited);

        _cast_light2(x-1, y, 4, radius, depth+!(x%2), visited);
        _cast_light2(x+1, y, 5, radius, depth+!(x%2), visited);
        
        _cast_light2(x-1, y+1, 6, radius, depth+1+!(x%2), visited);
        _cast_light2(x, y+1, 7, radius, depth+1, visited);
        _cast_light2(x+1, y+1, 8, radius, depth+1+!(x%2), visited);
        return;

        case 1:
        _cast_light2(x-1, y-1, 1, radius, depth+1+!(x%2), visited);
        return;
        
        case 2:
        _cast_light2(x-1, y-1, 1, radius, depth+1+!(x%2), visited);
        _cast_light2(x, y-1, 2, radius, depth+1, visited);
        _cast_light2(x+1, y-1, 3, radius, depth+1+!(x%2), visited);
        return;

        case 3:
        _cast_light2(x+1, y-1, 3, radius, depth+1+!(x%2), visited);
        return;

        case 4:
        _cast_light2(x-1, y-1, 1, radius, depth+1+!(x%2), visited);
        _cast_light2(x-1, y, 4, radius, depth+!(x%2), visited);
        _cast_light2(x-1, y+1, 6, radius, depth+1+!(x%2), visited);
        return;

        case 5:
        _cast_light2(x+1, y-1, 3, radius, depth+1+!(x%2), visited);
        _cast_light2(x+1, y, 5, radius, depth+!(x%2), visited);
        _cast_light2(x+1, y+1, 8, radius, depth+1+!(x%2), visited);
        return;

        case 6:
        _cast_light2(x-1, y+1, 6, radius, depth+1+!(x%2), visited);
        return;

        case 7:
        _cast_light2(x-1, y+1, 6, radius, depth+1+!(x%2), visited);
        _cast_light2(x, y+1, 7, radius, depth+1, visited);
        _cast_light2(x+1, y+1, 8, radius, depth+1+!(x%2), visited);
        return;

        case 8:
        _cast_light2(x+1, y+1, 8, radius, depth+1+!(x%2), visited);
        return;

    }
}

void _cast_light(int x, int y, int radius, int depth, vector<vector<int>>& visited) {

    auto& active_room = floors[current_floor].room[current_room];

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

        if(active_room.collisions[curr.y][curr.x] == 'X') {
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
    auto& active_room = floors[current_floor].room[current_room];
    vector<vector<int>> visited(active_room.art.size(), vector<int>(active_room.art[0].size(), 0));
    _cast_light2(x, y, 0, radius, 0, visited);
}

// ----------- zone changes and event handler ------------

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
    auto& active_room = floors[current_floor].room[current_room];

    lightmap.resize(active_room.art.size(), vector<short>(active_room.art[0].size()));
    player_pos = {x,y};

    return;
}

void event_handler(int x, int y) {

    auto& active_room = floors[current_floor].room[current_room];
    int active_room_lines = active_room.art.size();
    int active_room_cols = active_room.art[0].size();

    if(x<0 || x > active_room.art[0].size()-1) return;
    if(y<0 || y > active_room.art.size()-1) return;

    bool canMove = true;

    int new_room;
    switch(active_room.events[y][x]) {
        case '.': break;

        case 'a': // move a room left
            new_room = (int)floors[current_floor].layout[floor_layout_y][--floor_layout_x]-48;
            change_room(new_room, active_room_cols-3, player_pos.y);

        break;

        case 'b': // move a room up
            new_room = (int)floors[current_floor].layout[--floor_layout_y][floor_layout_x]-48;
            change_room(new_room, player_pos.x, active_room_lines-2);

        break;

        case 'c': // move a room right
            new_room = (int)floors[current_floor].layout[floor_layout_y][++floor_layout_x]-48;
            change_room(new_room, 2, player_pos.y);

        break;

        case 'd': // move a room down
            new_room = (int)floors[current_floor].layout[++floor_layout_y][floor_layout_x]-48;
            change_room(new_room, player_pos.x, 2);
            
        break;

        case '1':
            lighter_fuel += 5;
            lighter_fuel = min(lighter_fuel, max_lighter_fuel);
            send_message("Picked up some lighter fuel.", 20);

        break;

        case '2':

        break;

        case '3':

        break;

        case '4':

        break;
    }

    if(active_room.collisions[y][x] != 'X' && active_room.collisions[y][x] != 'O' && canMove) {
        player_pos.x += (x - player_pos.x);
        player_pos.y += (y - player_pos.y);
    }

    return;
}

void move_player(int& in) {
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

// -------------------- game functions --------------------

void add_lighter_fuel(int val) {
    lighter_fuel += val;
    lighter_fuel = min(lighter_fuel, max_lighter_fuel);
    return;
}

void set_lighter_fuel(int val) {
    lighter_fuel = val;
    lighter_fuel = min(lighter_fuel, max_lighter_fuel);
    return;
}

// ---------------- title screen and game -----------------

void Introduction () {
    WINDOW* txtbox = newwin(LINES,COLS,0,0);
    wattron(txtbox, COLOR_PAIR(2));
    print_centered(txtbox, -2, 0, msgs[LANG_OPTION]["IntroductoryText1"]);
    print_centered(txtbox, 0, 0, msgs[LANG_OPTION]["IntroductoryText2"]);
    print_centered(txtbox, 2, 0, msgs[LANG_OPTION]["IntroductoryText3"]);
    print_centered(txtbox, 4, 0, msgs[LANG_OPTION]["IntroductoryText4"]);
    wattroff(txtbox, COLOR_PAIR(2));

    wborder(txtbox, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(txtbox);
    wgetch(txtbox);

    

    wclear(txtbox);
    print_centered(txtbox, 0, 0, msgs[LANG_OPTION]["IntroductoryText5"]);
    wborder(txtbox, '|', '|', '-', '-', '+', '+', '+', '+');
    wgetch(txtbox);

    delwin(txtbox);
    return;
}

void Game () {

    if(!load_save_file()) {
        Introduction();
    }

    WINDOW* win = newwin((int)LINES * 0.75, COLS,0,0); // screen
    nodelay(stdscr, TRUE);
    keypad(win, TRUE);

    WINDOW* message_log = newwin((int)LINES * 0.25, (int)COLS,LINES * 0.75, 0);

    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');

    wrefresh(win);
    wrefresh(message_log);
    

    string floor_splash = "Floor"; floor_splash += (char)current_floor+48; floor_splash += "Splash";

    change_floor(current_floor, msgs[LANG_OPTION][floor_splash]);
    change_room(current_room, player_pos.x, player_pos.y);
    
    unsigned int frame = 0;

    int in;
    int last_tick_lines = LINES, last_tick_cols = COLS;
    wchar_t spinning_wheel = '/';

    while(1) {
        // handle screen resizing

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

        // lighting and lighter fuel
        {

        auto& active_room = floors[current_floor].room[current_room];
        int active_room_lines = active_room.art.size();
        int active_room_cols = active_room.art[0].size();

        clear_lightmap();

        if(lighter_on) {
            cast_light(player_pos.x, player_pos.y, lighter_strength);
            lighter_fuel -= lighter_fuel_consumption/FRAMES_PER_SECOND;
            if(lighter_fuel <= 0) {
                lighter_on = false;
            }
        }
        else {
            lighter_fuel += lighter_fuel_regen/FRAMES_PER_SECOND;
            lighter_fuel = min(lighter_fuel, max_lighter_fuel);
        }

        for(int i = 0; i < active_room_lines; i++) {
            for(int j = 0; j < active_room_cols; j++) {

                if(active_room.lights[i][j] == 46) {
                    continue;
                }

                if(active_room.lights[i][j]-48 > 0) {
                    cast_light(j, i, active_room.lights[i][j]-48);
                }

            }
        }
        
        for(int i = 0; i < active_room_lines; i++) {
            
            wmove(win, (LINES-active_room_lines-((int)LINES*0.25))/2+i, (COLS-active_room_cols)/2);

            for(int j = 0; j < active_room_cols; j++) {
                
                if(lightmap[i][j] == 0 || lightmap[i][j] == 1) {
                    wattron(win, COLOR_PAIR(1));
                    wprintw(win, " ");
                    wattroff(win, COLOR_PAIR(1));
                    continue;
                }

                if(i == player_pos.y && j == player_pos.x) {
                    wattron(win, COLOR_PAIR(lightmap[i][j]));
                    wprintw(win, "%c", player_icon);
                    wattroff(win, COLOR_PAIR(lightmap[i][j]));
                    continue;
                }

                int attr_number;
                switch(active_room.colors[i][j]) {
                        case 'R':
                        wattron(win, COLOR_PAIR(10+(lightmap[i][j]==3)*10));
                        attr_number = 10+(lightmap[i][j]==3)*10;
                        break;
                        case 'G':
                        wattron(win, COLOR_PAIR(11+(lightmap[i][j]==3)*10));
                        attr_number = 11+(lightmap[i][j]==3)*10;
                        break;
                        case 'B':
                        wattron(win, COLOR_PAIR(12+(lightmap[i][j]==3)*10));
                        attr_number = 12+(lightmap[i][j]==3)*10;
                        break;
                        case 'Y':
                        wattron(win, COLOR_PAIR(13)+(lightmap[i][j]==3)*10);
                        attr_number = 13+(lightmap[i][j]==3)*10;
                        break;
                        case 'M':
                        wattron(win, COLOR_PAIR(14)+(lightmap[i][j]==3)*10);
                        attr_number = 14+(lightmap[i][j]==3)*10;
                        break;
                        case 'C':
                        wattron(win, COLOR_PAIR(15+(lightmap[i][j]==3)*10));
                        attr_number = 15+(lightmap[i][j]==3)*10;
                        break;
                        case 'g':
                        wattron(win, COLOR_PAIR(2));
                        attr_number = 2;
                        break;
                        default:
                        wattron(win, COLOR_PAIR(lightmap[i][j]));
                        attr_number = lightmap[i][j];
                        break;
                }

                wprintw(win, "%lc", active_room.art[i][j]);
                wattroff(win, attr_number);
                
            }
            wprintw(win, "\n");
        }
        

        }

        if(DEBUG_MODE == 1) {
            wprintw(win, "\n\n");
            wattron(win, COLOR_PAIR(3));
            for(int i = 0; i < lightmap.size(); i++) {
                for(int j = 0; j < lightmap[0].size(); j++) {
                    wprintw(win, "%d", lightmap[i][j]);
                }
                wprintw(win, "\n");
            }
            wattroff(win, COLOR_PAIR(3));
            wprintw(win, "%d %d", lightmap.size(), lightmap[0].size());
        }
        if(DEBUG_MODE == 2) {
            wattron(win, COLOR_PAIR(3));
            wprintw(win, "\n\nx: %d y: %d, frame %u, FPS = %d\n", player_pos.x, player_pos.y, frame, FRAMES_PER_SECOND);
            wattroff(win, COLOR_PAIR(3));
        }
        if(DEBUG_MODE == 3) {
            wattron(win, COLOR_PAIR(3));
            wprintw(win, "\n\n%s\n", floors[current_floor].room[current_room].art[0].c_str());
            wattroff(win, COLOR_PAIR(3));
        }

        wrefresh(win);
        wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(message_log);
        wclear(message_log);
        print_messages(message_log);
        mvwprintw(message_log, 2, COLS * 0.88, msgs[LANG_OPTION]["Fuel"].c_str());

        int consumption_speed = FRAMES_PER_SECOND/(lighter_fuel_consumption*4);
        int regen_speed = (FRAMES_PER_SECOND/(lighter_fuel_regen*4));

        if(frame % (consumption_speed == 0 ? 1 : consumption_speed) == 0) {
            if(lighter_on) {
                spinning_wheel = spin_counterclockwise(spinning_wheel);
            }

        }

        if(frame % (regen_speed == 0 ? 1 : consumption_speed) == 0) {
            if(!lighter_on && lighter_fuel < max_lighter_fuel){
                spinning_wheel = spin_clockwise(spinning_wheel);
            } 
        }

        mvwprintw(message_log, 3, COLS * 0.88 - 2, "%lc", spinning_wheel);

        for(int i = 0; i < max_lighter_fuel; i+=5) {
            // █ ▓ ░ ▮▯
            if(lighter_fuel - i <= 0) {
                mvwprintw(message_log, 3, COLS * 0.88 + i/5, "░");
            }
            else if(lighter_fuel - i < 5) {
                mvwprintw(message_log, 3, COLS * 0.88 + i/5, "█");
            }
            else if(lighter_fuel - i >= 5) {
                mvwprintw(message_log, 3, COLS * 0.88 + i/5, "█");
            }
        }
        

        in = getch();

        move_player(in);

        if(in == 'p' || in == 'P') {
            if(PauseMenu()) {
                delwin(win);
                return;
            }
        }
            
    }

    nodelay(stdscr, FALSE);

}

int PauseMenu () {
    vector<string> options = {
        msgs[LANG_OPTION]["Resume"],
        msgs[LANG_OPTION]["Settings"],
        msgs[LANG_OPTION]["Save"],
        msgs[LANG_OPTION]["SaveAndExit"]
    };

    WINDOW* win = newwin(LINES,COLS,0,0);
    keypad(win, TRUE);

    int selected = 0, logo_offset = 7;
    bool saved = false;

    while(1) {

        wclear(win);
        if(saved) {
            mvwprintw(win, LINES - 3, COLS - 10, "%s", msgs[LANG_OPTION]["Saved!"].c_str());
            saved = false;
        }

        for(int i = 0; i < logo.size(); i++) {
            print_centered(win, (-logo_offset) + i, 0, logo[i]);
        }

        for(int i = 0; i < options.size(); i++) {
            if(i == selected) {
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, ">");
            }
            else mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, " ");

            mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s", options[i].c_str());
        }

        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(win);

        int in = wgetch(win);

        if(in == KEY_BACKSPACE) {
            delwin(win);
            return 0;
        }

        if(in == keyConfirm) {
            if(selected == 0) {
                delwin(win);
                return 0;
            }
            if(selected == 1) {
                Settings();
            }
            if(selected == 2) {
                save_to_file();
                saved = true;
            }
            if(selected == 3) {
                save_to_file();
                delwin(win);
                return 1;
            }
        }

        if(in == keyUp) {
            selected--;
            if(selected == -1) selected = options.size()-1;
            selected %= options.size();
        }

        if(in == keyDown) {
            selected++;
            selected %= options.size();
        }
    }


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

    vector<string> options = {
        msgs[LANG_OPTION]["keybConfirm"],
        msgs[LANG_OPTION]["keybToggleLighter"],
        msgs[LANG_OPTION]["keybUp"],
        msgs[LANG_OPTION]["keybDown"],
        msgs[LANG_OPTION]["keybLeft"],
        msgs[LANG_OPTION]["keybRight"],
        msgs[LANG_OPTION]["optBack"]
    };

    vector<short> keybinds = {
        keyConfirm,
        keyToggleLighter,
        keyUp,
        keyDown,
        keyLeft,
        keyRight
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
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, ">");
            }
            else mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, " ");
            
            if(i == options.size()-1) {
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s", options[i].c_str());
            }
            else mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s%d (%c)", options[i].c_str(), keybinds[i], keybinds[i]);
        }

        mvwprintw(win, LINES/2 - 2 + 2*options.size()+2, COLS/2 - 38, "%s", msgs[LANG_OPTION]["msgChanges"].c_str());

        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(win);
        in = wgetch(win);
        
        if(in == keyDown) {
            selected++;
            selected%=options.size();
        }
        else if(in == keyUp) {
            selected--;
            if(selected == -1) selected = options.size()-1;
            selected%=options.size();
        }
        else if(in == keyConfirm) {

            if(selected == options.size()-1) {
                keyConfirm = keybinds[0];
                keyToggleLighter = keybinds[1];
                keyUp = keybinds[2];
                keyDown = keybinds[3];
                keyLeft = keybinds[4];
                keyRight = keybinds[5];
                delwin(win);
                return;
            }
            
            mvwprintw(win, LINES/2 - 2 + 2*selected, COLS/2 - 38, "%s%s", options[selected].c_str(), "_                  ");
            in = wgetch(win);
            
            keybinds[selected] = in;

        }
    }

    
    
    return;
}

void Settings() {

    WINDOW* win = newwin(LINES,COLS,0,0);
    keypad(win, TRUE);

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
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, ">");
            }
            else mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, " ");
            
            if(i == 0) {
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s%d FPS", options[i].c_str(), fps_options[FRAMES_OPTION]);
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
            if(selected == -1) selected = options.size()-1;
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
                delwin(win);
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
            if(i == selected) {
                mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, ">");
            }
            else mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 40, " ");

            mvwprintw(win, LINES/2 - 2 + 2*i, COLS/2 - 38, "%s", options[i].c_str());
        }

        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
        wrefresh(win);

        in = wgetch(win);

        if(in == keyConfirm) {
            delwin(win);
            clear();
            return selected;
        }

        if(in == keyUp) {
            selected--;
            if(selected == -1) selected = options.size()-1;
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
    init_pair(2, COLOR_BLACK+8, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK+8);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
    
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

    load_floor(0);

    while(1) {
        int in = TitleScreen(in);

        switch(in) {
            case 0:
                Game();
                break;
            case 1:
                Settings();
                break;
            case 2:
                Credits();
                break;
            case 3:
                endwin();
                return 0;
        }
    }
    
    return 0;

}
