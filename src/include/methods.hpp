#pragma once
#include "classes.hpp"
#include <chrono>

void MessageLog::printMessages(WINDOW* win) {
    wattron(win, A_BOLD);
    for(auto it = messageLog.begin(); it != messageLog.end();) {
        if((*it).second <= 0) {
            it = messageLog.erase(it);
        }
        else {
            wprintw(win, "\n  %s", (*it).first.c_str());
            (*it).second--;
            it++;
        }
    }
    wattroff(win, A_BOLD);
}

void MessageLog::sendMessage(const char* line, int duration) {
    messageLog.push_back({line, duration});
}

void MessageLog::sendMessage(char* line, int duration) {
    messageLog.push_back({line, duration});
}


coord Player::getPos() {
    return pos; 
}

void Player::setPos (int x, int y) {
    pos = {x, y};
}

void Player::addHealth(int val) {
    health += val;
    health = min(health, maxHealth);
    return;
}

void Player::setHealth(int val) {
    health = val;
    health = min(health, maxHealth);
    return;
}

void Player::addLighterFuel(float val) {
    lighterFuel += val;
    lighterFuel = min(lighterFuel, maxLighterFuel);
    return;
}

void Player::setLighterFuel(float val) {
    lighterFuel = val;
    lighterFuel = min(lighterFuel, maxLighterFuel);
    return;
}

void Player::lockMovement() {
    movementLock = true; return;
}

void Player::unlockMovement() {
    movementLock = false; return;
}

bool Player::isMovementLocked() {
    return movementLock;
}

void Player::toggleLighter() {
    lighterOn = !lighterOn;
    return;
}

bool Player::isLighterOn() {
    return lighterOn;
}


int GUI::pauseMenu() {
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

        if(in == keyDeny) {
            delwin(win);
            return 0;
        }

        if(in == keyConfirm) {
            if(selected == 0) {
                delwin(win);
                return 0;
            }
            if(selected == 1) {
                settings();
            }
            if(selected == 2) {
                //save_to_file();
                saved = true;
            }
            if(selected == 3) {
                //save_to_file();
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

void GUI::credits() {
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
        char str[128];
        snprintf(str, 128, "%s\n", message[i].c_str());
        //mvwprintw(win, win->_maxy / 2 - message.size()/2 + i, win->_maxx / 2 - message[i].length() / 2, "%s\n", message[i].c_str());
        print_centered(win, -message.size()/2+i, -message[i].length() / 2, str);
    }

    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

    wrefresh(win);

    wgetch(win);

    delwin(win);
    return;
}

void GUI::keybindsMenu() {
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
        keyDeny,
        keyUp,
        keyDown,
        keyLeft,
        keyRight
    };

    int selected = 0, in, logo_offset = 7;

    while(1) {
        werase(win);

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
                keyDeny = keybinds[1];
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

void GUI::settings() {

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

        werase(win);

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
                keybindsMenu();
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

int GUI::titleScreen(int start_selected) {

    WINDOW* win = newwin(LINES,COLS,0,0);
    keypad(win, TRUE);

    int in;

    vector<string> options = {
        msgs[LANG_OPTION]["optContinue"],
        msgs[LANG_OPTION]["optPlay"],
        msgs[LANG_OPTION]["optSettings"],
        msgs[LANG_OPTION]["optCredits"],
        msgs[LANG_OPTION]["optQuit"],
    };

    int logo_offset = 7;
    int selected = start_selected;

    while(1) {

        werase(win);

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
            erase();
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

void GUI::sendMessageBox(const char* message, int border_style, int border_color, int text_color) {
    WINDOW* messageBox = newwin(10, 60, LINES/2-5, COLS/2-30);
    switch(border_style) {
        case 0:
            wborder(messageBox, '|', '|', '-', '-', '+', '+', '+', '+');
        break;
        case 1:
            for(int i = 1; i < 59; i++) {
                mvwprintw(messageBox, 0, i, "%lc", L'─');
                mvwprintw(messageBox, 9, i, "%lc", L'─');
            }
            for(int i = 0; i < 10; i++) {
                mvwprintw(messageBox, i, 0, "%lc", L'│');
                mvwprintw(messageBox, i, 59, "%lc", L'│');
            }
            mvwprintw(messageBox, 0, 0, "%lc", L'┌');
            mvwprintw(messageBox, 0, 59, "%lc", L'┐');
            mvwprintw(messageBox, 9, 0, "%lc", L'└');
            mvwprintw(messageBox, 9, 59, "%lc", L'┘');
            
            // V cringe and doesnt work V
            //wborder(messageBox, L'│', L'│', L'─', L'┌', L'┐', L'└', L'┘');
        break;
        case 2:
            wborder(messageBox, '|', '|', '-', '-', '+', '+', '+', '+');
        break;
    }
    
    string a = "Lorem ipsum dolor sit amet....";
    mvwprintw(messageBox, 1, 2, a.c_str());
    mvwprintw(messageBox, 3, 2, a.c_str());
    wrefresh(messageBox);
    back:
    int in = wgetch(messageBox);
    if(in != keyConfirm && in != keyDeny) {
        goto back;
    }
    delwin(messageBox);
    return;
}

void Map::changeFloor(int floor_number, string change_text) {

    string floorText = msgs[LANG_OPTION]["Floor"] + to_string(floor_number);
    currentFloor = floor_number;
    WINDOW* txtbox = newwin(LINES,COLS,0,0);
    print_centered(txtbox, -2, 0, floorText.c_str());
    print_centered(txtbox, 0, 0, change_text.c_str());
    wborder(txtbox, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(txtbox);
    napms(2300);
    
    delwin(txtbox);
    
    return;
}

void Map::changeRoom(int room_number, int x, int y) {
    currentRoom = room_number;
    auto& active_room = floor.room[currentRoom];

    lightmap.resize(active_room.art.size(), vector<short>(active_room.art[0].size()));
    player.setPos(x,y);

    return;
}

void Map::initFloorPickups(int floor_n) {

    auto active_floor = floor;

    switch(floor_n) {

        case 0:

            // spawn:
            // 10 notes
            // 12 lighter fuel
            // 60-120 spikes

            int rand_room, rand_line, rand_col;
            //for(int i = 0; i < 120; i++) {
            //    rand_room = rand()%active_floor.room.size();
            //    rand_line = 1 + (rand() % (active_floor.room[rand_room].art.size()-1 ) );
            //    rand_col = 2 + 2 * (rand() % (active_floor.room[rand_room].art[0].size()/2 - 1 ) );
            //    if(spawnPickup(spike_object, i, rand_col, rand_line, rand_room) != 0) {
            //        i--;
            //    }
            //}
            for(int i = 0; i < 10; i++) {
                rand_room = rand()%active_floor.room.size();
                rand_line = 1 + (rand() % (active_floor.room[rand_room].art.size()-1 ) );
                rand_col = 2 + 2 * (rand() % (active_floor.room[rand_room].art[0].size()/2 - 1 ) );
                if(spawnPickup(note_pickup, i, rand_col, rand_line, rand_room) != 0) {
                    i--;
                }
            }

            for(int i = 0; i < 12; i++) {
                rand_room = rand()%active_floor.room.size();
                rand_line = 1 + (rand() % (active_floor.room[rand_room].art.size()-1 ) );
                rand_col = 2 + 2 * (rand() % (active_floor.room[rand_room].art[0].size()/2 - 1 ) );
                if(spawnPickup(lighter_fuel_pickup, 3, rand_col, rand_line, rand_room) != 0) {
                    i--;
                }
            }

        break;

        case 2:
            return;
        break;

    }

}

int Map::spawnPickup(pickup p, int type, int x, int y, int room_n) {
    auto& r = floor.room[room_n];

    if(r.pickups[y][x] != ' ' && r.pickups[y][x] != '.') {
        return -1;
    }

    r.art[y][x] = p.icon;
    int n = x;
    if(player.getPos().x % 2 == 0) {
        n += 1;
    }
    r.colors[y][x] = p.color;
    r.events[y][x] = p.ID;
    r.pickups[y][x] = type;

    return 0;

}

void Map::resetTile(int x, int y) {
    auto& r = floor.room[currentRoom];

    r.art[y][x] = floor_art_source[currentFloor][currentRoom][y][x];
    r.colors[y][x] = floor_colors_source[currentFloor][currentRoom][y][x];
    r.events[y][x] = floor_events_source[currentFloor][currentRoom][y][x];
    r.pickups[y][x] = floor_pickups_source[currentFloor][currentRoom][y][x];
}

void Map::clearLightmap() {
    for(int i = 0; i < lightmap.size(); i++) {
        fill(lightmap[i].begin(), lightmap[i].end(), 0);
    }
}

int Map::getLightLevel(int depth, int radius) {
    if(depth < radius - 1) {
            return 3;
        }
        else if(depth == radius - 1) {
            return 2;
        }
        else return 1;
}

void Map::castLight(int x, int y, int radius) {
    auto& active_room = floor.room[currentRoom];
    vector<vector<int>> visited(active_room.art.size(), vector<int>(active_room.art[0].size(), 0));
    _castLight(x, y, 0, radius, 0, visited);
}

void Map::castLightDirectional(int x, int y, int radius, int direction) {
    auto& active_room = floor.room[currentRoom];
    vector<vector<int>> visited(active_room.art.size(), vector<int>(active_room.art[0].size(), 0));
    _castLight(x, y, direction, radius, 0, visited);
}

void Map::_castLight(int x, int y, int direction, int radius, int depth, vector<vector<int>>& visited) {
    int light_level = getLightLevel(depth, radius);
    auto& active_room = floor.room[currentRoom];

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

    // bad hack; will not fix
    int n = x;
    if(player.getPos().x % 2 == 0) {
        n += 1;
    }

    // 1 2 3
    // 4 0 5
    // 6 7 8
    switch(direction) {
        case 0:
        _castLight(x-1, y-1, 1, radius, depth+1+(n%2), visited);
        _castLight(x, y-1, 2, radius, depth+1, visited);
        _castLight(x+1, y-1, 3, radius, depth+1+(n%2), visited);

        _castLight(x-1, y, 4, radius, depth+(n%2), visited);
        _castLight(x+1, y, 5, radius, depth+(n%2), visited);
        
        _castLight(x-1, y+1, 6, radius, depth+1+(n%2), visited);
        _castLight(x, y+1, 7, radius, depth+1, visited);
        _castLight(x+1, y+1, 8, radius, depth+1+(n%2), visited);
        return;

        case 1:
        _castLight(x-1, y-1, 1, radius, depth+1+(n%2), visited);
        return;
        
        case 2:
        _castLight(x-1, y-1, 1, radius, depth+1+(n%2), visited);
        _castLight(x, y-1, 2, radius, depth+1, visited);
        _castLight(x+1, y-1, 3, radius, depth+1+(n%2), visited);
        return;

        case 3:
        _castLight(x+1, y-1, 3, radius, depth+1+(n%2), visited);
        return;

        case 4:
        _castLight(x-1, y-1, 1, radius, depth+1+(n%2), visited);
        _castLight(x-1, y, 4, radius, depth+(n%2), visited);
        _castLight(x-1, y+1, 6, radius, depth+1+(n%2), visited);
        return;

        case 5:
        _castLight(x+1, y-1, 3, radius, depth+1+(n%2), visited);
        _castLight(x+1, y, 5, radius, depth+(n%2), visited);
        _castLight(x+1, y+1, 8, radius, depth+1+(n%2), visited);
        return;

        case 6:
        _castLight(x-1, y+1, 6, radius, depth+1+(n%2), visited);
        return;

        case 7:
        _castLight(x-1, y+1, 6, radius, depth+1+(n%2), visited);
        _castLight(x, y+1, 7, radius, depth+1, visited);
        _castLight(x+1, y+1, 8, radius, depth+1+(n%2), visited);
        return;

        case 8:
        _castLight(x+1, y+1, 8, radius, depth+1+(n%2), visited);
        return;

    }
}

void Map::loadFloor(int floor_n) {
    
    floor.room.resize(floor_art_source[floor_n].size());
    floor.layout = floor_layout_source[floor_n];

    for(int i = 0; i < floor_art_source[floor_n].size(); i++) {
        floor.room[i].art = floor_art_source[floor_n][i];
        floor.room[i].collisions = floor_collisions_source[floor_n][i];
        floor.room[i].colors = floor_colors_source[floor_n][i];
        floor.room[i].events = floor_events_source[floor_n][i];
        floor.room[i].lights = floor_lights_source[floor_n][i];
        floor.room[i].pickups = floor_pickups_source[floor_n][i];
    }
    changeRoom(floor_starting_rooms[floor_n], floor_starting_coords[floor_n].first, floor_starting_coords[floor_n].second);
    gameMap.floorLayoutY = starting_room_layout_index[floor_n].first;
    gameMap.floorLayoutX = starting_room_layout_index[floor_n].second;

    coord playerPos = player.getPos();
    playerPos.x = floor_starting_coords[floor_n].first;
    playerPos.y = floor_starting_coords[floor_n].second;

    gameMap.initFloorPickups(floor_n);

    return;
}  

void Game::introduction () {

//wip
//WINDOW* txtbox = newwin(LINES,COLS,0,0);
//wattron(txtbox, COLOR_PAIR(2));
//print_centered(txtbox, -2, 0, msgs[LANG_OPTION]["IntroductoryText1"]);
//print_centered(txtbox, 0, 0, msgs[LANG_OPTION]["IntroductoryText2"]);
//print_centered(txtbox, 2, 0, msgs[LANG_OPTION]["IntroductoryText3"]);
//print_centered(txtbox, 4, 0, msgs[LANG_OPTION]["IntroductoryText4"]);
//wattroff(txtbox, COLOR_PAIR(2));

//wborder(txtbox, '|', '|', '-', '-', '+', '+', '+', '+');
//wrefresh(txtbox);
//wgetch(txtbox);



//wclear(txtbox);
//print_centered(txtbox, 0, 0, msgs[LANG_OPTION]["IntroductoryText5"]);
//wborder(txtbox, '|', '|', '-', '-', '+', '+', '+', '+');
//wgetch(txtbox);

//delwin(txtbox);

return;
}

void Game::newGame () {
    gameMap.loadFloor(0);
    gameMap.changeFloor(0, "{ PLACEHOLDER }");
    game.initPlayer();
    return;
}

int Game::update (WINDOW* win, WINDOW* message_log) {

    static unsigned long frame = 0;
    static int last_tick_lines = LINES, last_tick_cols = COLS;
    static wchar_t spinning_wheel = '/';

    coord playerPos = player.getPos();

    if(player.health <= 0) { // death check
        return 2;
    }

    // debug
    if(frame == 120) {
        gui.sendMessageBox("asd",1, 0, 0);
    }

    frame++;
    
    game.renderMap(win);
    
    // debug
    {
    if(DEBUG_MODE == 1) {
        wprintw(win, "\n\n");
        wattron(win, COLOR_PAIR(3));
        for(int i = 0; i < gameMap.lightmap.size(); i++) {
            for(int j = 0; j < gameMap.lightmap[0].size(); j++) {
                wprintw(win, "%d", gameMap.lightmap[i][j]);
            }
            wprintw(win, "\n");
        }
        wattroff(win, COLOR_PAIR(3));
        wprintw(win, "%d %d", gameMap.lightmap.size(), gameMap.lightmap[0].size());
    }
    if(DEBUG_MODE == 2) {
        wattron(win, COLOR_PAIR(3));
        wprintw(win, "\n\nx: %d y: %d, frame %u, FPS = %d\n", playerPos.x, playerPos.y, frame, FRAMES_PER_SECOND);
        wattroff(win, COLOR_PAIR(3));
    }
    if(DEBUG_MODE == 3) {
        wattron(win, COLOR_PAIR(3));
        wprintw(win, "\n\n%s\n", gameMap.floor.room[currentRoom].art[0].c_str());
        wattroff(win, COLOR_PAIR(3));
    }
    if(DEBUG_MODE == 4) {
        mvwprintw(message_log, 2, COLS * 0.91, "%f", player.lighterFuel);
        mvwprintw(message_log, 2, COLS * 0.20, DEBUG_VAR1_TYPE, DEBUG_VAR1);
        mvwprintw(message_log, 2, COLS * 0.25, DEBUG_VAR2_TYPE, DEBUG_VAR2);
        mvwprintw(message_log, 2, COLS * 0.30, DEBUG_VAR3_TYPE, DEBUG_VAR3);
    }
    }

    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(message_log);
    wrefresh(win);

    werase(message_log);
    messageLog.printMessages(message_log);

    // lighter fuel and health GUI
    {
        
        int consumption_speed = FRAMES_PER_SECOND/(player.lighterFuelConsumption*4);
        int regen_speed = (FRAMES_PER_SECOND/(player.lighterFuelRegen*4));



        // lighter fuel bar rendering
        if(ENABLE_LIGHTER_BAR) {
            if(frame % (consumption_speed == 0 ? 1 : consumption_speed) == 0) {
                if(player.isLighterOn()) {
                    spinning_wheel = spin_counterclockwise(spinning_wheel);
                }

            }
            if(frame % (regen_speed == 0 ? 1 : consumption_speed) == 0) {
                if(!player.isLighterOn() && player.lighterFuel < player.maxLighterFuel){
                    spinning_wheel = spin_clockwise(spinning_wheel);
                } 
            }

            mvwprintw(message_log, 2, COLS * 0.88 - 2, "%lc", spinning_wheel);
            mvwprintw(message_log, 2, COLS * 0.88, msgs[LANG_OPTION]["Fuel"].c_str());
            for(int i = 0; i < player.maxLighterFuel; i+=5) {
                // █ ▓ ░ ▮▯
                if(player.lighterFuel - i <= 0) {
                    mvwprintw(message_log, 3, COLS * 0.88 + i/5, "░");
                }
                else if(player.lighterFuel - i < 5) {
                    mvwprintw(message_log, 3, COLS * 0.88 + i/5, "█");
                }
                else if(player.lighterFuel - i >= 5) {
                    mvwprintw(message_log, 3, COLS * 0.88 + i/5, "█");
                }
            }
        }


        // health bar rendering
        if(ENABLE_HEALTH_BAR) {
            mvwprintw(message_log, 6, COLS * 0.88, msgs[LANG_OPTION]["Health"].c_str());
            for(int i = 0; i < player.maxHealth; i+=5) {
                if(player.health - i <= 0) {
                    mvwprintw(message_log, 7, COLS * 0.88 + i/5, "░");
                }
                else if(player.health - i < 5) {
                    mvwprintw(message_log, 7, COLS * 0.88 + i/5, "█");
                }
                else if(player.health - i >= 5) {
                    mvwprintw(message_log, 7, COLS * 0.88 + i/5, "█");
                }
            }

        }

    }

    int in = getch();
    if(in != -1) {
        player.move(in);
    }

    if(in == 'p' || in == 'P') {
        if(gui.pauseMenu()) {
            delwin(win);
            return 1;
        }
    }

    return 0;
    
}

int Game::gameMain () {

    //if(!load_save_file()) {
    //    introduction();
    //}

    WINDOW* win = newwin((int)LINES * 0.75, COLS,0,0);
    nodelay(stdscr, TRUE);
    keypad(win, TRUE);
    WINDOW* message_log = newwin((int)LINES * 0.25, (int)COLS,LINES * 0.75, 0);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(message_log, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
    wrefresh(message_log);
    
    string floor_splash = "Floor"; floor_splash += (char)currentFloor+48; floor_splash += "Splash";

    coord playerPos = player.getPos();

    flushinp();

    while(1) {
        auto time_begin = chrono::steady_clock::now();
        int status_code = game.update(win, message_log);
        auto time_end = chrono::steady_clock::now();
        
        if(status_code != 0) {
            return status_code;
        }

        auto total_elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_begin).count();
        napms(REFRESH_RATE - total_elapsed_time);
    }

    nodelay(stdscr, FALSE);

    return -1;

}

void Game::eventHandler(int x, int y) {

    auto& active_room = gameMap.floor.room[currentRoom];
    int active_room_lines = active_room.art.size();
    int active_room_cols = active_room.art[0].size();

    if(x<0 || x > active_room.art[0].size()-1) return;
    if(y<0 || y > active_room.art.size()-1) return;

    bool canMove = true;

    int new_room;
    char* s = (char*)malloc(128 * sizeof(char));
    int item_type = active_room.pickups[y][x];
    coord playerPos = player.getPos();
    switch(active_room.events[y][x]) {
        case '.': break;

        case 'a': // move a room left
            new_room = (int)gameMap.floor.layout[gameMap.floorLayoutY][--gameMap.floorLayoutX]-48;
            gameMap.changeRoom(new_room, active_room_cols-3, playerPos.y);
            // find 'c', go left by one.
        break;

        case 'b': // move a room up
            new_room = (int)gameMap.floor.layout[--gameMap.floorLayoutY][gameMap.floorLayoutX]-48;
            gameMap.changeRoom(new_room, playerPos.x, active_room_lines-2);
            // find 'd', go up by one.
        break;

        case 'c': // move a room right
            new_room = (int)gameMap.floor.layout[gameMap.floorLayoutY][++gameMap.floorLayoutX]-48;
            gameMap.changeRoom(new_room, 2, playerPos.y);
            // find 'a', go right by one.
        break;

        case 'd': // move a room down
            new_room = (int)gameMap.floor.layout[++gameMap.floorLayoutY][gameMap.floorLayoutX]-48;
            gameMap.changeRoom(new_room, playerPos.x, 1);
            // find 'b', go down by one.
        break;

        case 'n':
            gameMap.changeFloor(0, (char*)"sus");
        break;
        

        case '1':

            player.addLighterFuel( item_type );
            snprintf(s, 128, "Picked up some lighter fuel (%d).", item_type);
            messageLog.sendMessage(s, 4*FRAMES_PER_SECOND);
            gameMap.resetTile(x, y);

        break;

        case '2':

            snprintf(s, 128, "Picked up note number %d.", item_type);
            messageLog.sendMessage(s, 4*FRAMES_PER_SECOND);
            gameMap.resetTile(x, y);

        break;

        case '3':

            snprintf(s, 128, "Used a band-aid (+%d health)", item_type);
            player.addHealth(item_type);
            messageLog.sendMessage(s, 4*FRAMES_PER_SECOND);
            gameMap.resetTile(x, y);

        break;

        case '4':

            snprintf(s, 128, "Used a medkit. (+%d health)", item_type);
            player.addHealth(item_type);
            messageLog.sendMessage(s, 4*FRAMES_PER_SECOND);
            gameMap.resetTile(x, y);

        break;

        case '5':

            player.addHealth(-item_type);
            snprintf(s, 128, "Ow! Stepped on a spike (-%d)", item_type);
            messageLog.sendMessage(s, 4*FRAMES_PER_SECOND);

        break;
    }
    free(s);

    if(active_room.collisions[y][x] != 'X' && active_room.collisions[y][x] != 'O' && canMove) {
        player.setPos(x, y);
    }

    return;
    
}

void Game::deathSequence() {
    WINDOW* win = newwin(LINES, COLS, 0, 0);
    keypad(win, true);

    wbkgd(win, COLOR_PAIR(7));
    wrefresh(win);
    napms(1200);

    wbkgd(win, COLOR_PAIR(3));
    print_centered(win, -5, 0, "You lost!");
    wrefresh(win);
    napms(1000);
    print_centered(win, -3, 0, "Died from: ?");
    wrefresh(win);
    napms(1000);
    print_centered(win, -1, 0, "Score: ?");
    wrefresh(win);
    napms(1000);
    print_centered(win, 1, 0, "Press any key to continue");
    flushinp();
    wgetch(win);


    delwin(win);

    return;
}

void Game::winSequence() {
    return;
}

void Player::move(int& in) {

    if(player.isMovementLocked()) return;

    int x = 0, y = 0;

    if(in == keyLeft){ x--; player.facingDirection = 4;}
    else if(in == keyUp){ y--; player.facingDirection = 2;}
    else if(in == keyRight){ x++; player.facingDirection = 5;}
    else if(in == keyDown){ y++; player.facingDirection = 7;}

    if(in == keyDeny) {
        player.toggleLighter();
        return;
    }

    coord pos = player.getPos();
    game.eventHandler(pos.x + x, pos.y + y);
    return;
}

void Game::initPlayer() {

    player.setHealth(player.maxHealth);
    player.setLighterFuel(player.maxLighterFuel);

    return;
}

void Game::renderMap(WINDOW *win) {

    auto& active_room = gameMap.floor.room[currentRoom];
    int active_room_lines = active_room.art.size();
    int active_room_cols = active_room.art[0].size();
    coord playerPos = player.getPos();

    for(int i = 0; i < active_room_lines; i++) {
        for(int j = 0; j < active_room_cols; j++) {

            if(active_room.lights[i][j] == 46) continue;

            if(active_room.lights[i][j]-48 > 0) {
                gameMap.castLight(j, i, active_room.lights[i][j]-48);
            }

        }
    }

    for(int i = 0; i < active_room_lines; i++) {
        
        wmove(win, (LINES-active_room_lines-((int)LINES*0.25))/2+i, (COLS-active_room_cols)/2);

        for(int j = 0; j < active_room_cols; j++) {
            
            if(gameMap.lightmap[i][j] == 0 || gameMap.lightmap[i][j] == 1) {
                wattron(win, COLOR_PAIR(1));
                wprintw(win, " ");
                wattroff(win, COLOR_PAIR(1));
                continue;
            }

            if(i == playerPos.y && j == playerPos.x) {
                wattron(win, COLOR_PAIR(gameMap.lightmap[i][j]));
                wprintw(win, "%lc", player.icon);
                wattroff(win, COLOR_PAIR(gameMap.lightmap[i][j]));
                continue;
            }

            int attr_number;
            switch(active_room.colors[i][j]) {
                    case 'R':
                    wattron(win, COLOR_PAIR(10+(gameMap.lightmap[i][j]==3)*10));
                    attr_number = 10+(gameMap.lightmap[i][j]==3)*10;
                    break;
                    case 'G':
                    wattron(win, COLOR_PAIR(11+(gameMap.lightmap[i][j]==3)*10));
                    attr_number = 11+(gameMap.lightmap[i][j]==3)*10;
                    break;
                    case 'B':
                    wattron(win, COLOR_PAIR(12+(gameMap.lightmap[i][j]==3)*10));
                    attr_number = 12+(gameMap.lightmap[i][j]==3)*10;
                    break;
                    case 'Y':
                    wattron(win, COLOR_PAIR(13)+(gameMap.lightmap[i][j]==3)*10);
                    attr_number = 13+(gameMap.lightmap[i][j]==3)*10;
                    break;
                    case 'M':
                    wattron(win, COLOR_PAIR(14)+(gameMap.lightmap[i][j]==3)*10);
                    attr_number = 14+(gameMap.lightmap[i][j]==3)*10;
                    break;
                    case 'C':
                    wattron(win, COLOR_PAIR(15+(gameMap.lightmap[i][j]==3)*10));
                    attr_number = 15+(gameMap.lightmap[i][j]==3)*10;
                    break;
                    case 'g':
                    wattron(win, COLOR_PAIR(2));
                    attr_number = 2;
                    break;
                    default:
                    wattron(win, COLOR_PAIR(gameMap.lightmap[i][j]));
                    attr_number = gameMap.lightmap[i][j];
                    break;
            }

            wprintw(win, "%lc", active_room.art[i][j]);
            wattroff(win, attr_number);
            
        }
        wprintw(win, "\n");

    }

    gameMap.clearLightmap();

    if(player.isLighterOn()) {
        gameMap.castLight(playerPos.x, playerPos.y, player.lighterStrength);
        player.addLighterFuel(-player.lighterFuelConsumption/FRAMES_PER_SECOND);
        if(player.lighterFuel <= 0) {
            if(player.isLighterOn()) {
                player.toggleLighter();
            }
        }
    }
    else {
        player.addLighterFuel(player.lighterFuelRegen/FRAMES_PER_SECOND);
    }

}

short Enemy::canMove(int x, int y) {
    vector<wstring>& collisions = gameMap.floor.room[currentRoom].collisions;
    if (collisions[y][x] != 'X' || collisions[y][x] != 'O') {
        return 1;
    }
    else return 0;
}

void Enemy::moveUp () {
    this->pos.y--;
    this->facingDirection = 2;
    return;
}

void Enemy::moveDown () {
    this->pos.y++;
    this->facingDirection = 7;
    return;
}

void Enemy::moveLeft () {
    this->pos.x--;
    this->facingDirection = 4;
    return;
}

void Enemy::moveRight () {
    this->pos.x++;
    this->facingDirection = 5;
    return;
}

void Enemy::patrolBehavior () {
    
    int y = this->pos.y;
    int x = this->pos.x;
    switch(this->facingDirection) {

        // up
        case 2:
            if (canMove(x, y-1)) {
                moveUp();
            }
            else if (canMove(x+1, y)) {
                moveRight();
            }
            else if (canMove(x-1, y)) {
                moveLeft();
            }
            else if (canMove(x, y+1)) {
                moveDown();
            }
        break;

        // left
        case 4:
            if (canMove(x-1, y)) {
                moveLeft();
            }
            else if (canMove(x, y-1)) {
                moveUp();
            }
            else if (canMove(x, y+1)) {
                moveDown();
            }
            else if (canMove(x+1, y)) {
                moveRight();
            }
        break;

        // right
        case 5:
            if (canMove(x+1, y)) {
                moveRight();
            }
            else if (canMove(x, y+1)) {
                moveDown();
            }
            else if (canMove(x, y-1)) {
                moveUp();
            }
            else if (canMove(x-1, y)) {
                moveLeft();
            }


        break;

        // down
        case 7:
            if (canMove(x, y+1)) {
                moveDown();
            }
            else if (canMove(x-1, y)) {
                moveLeft();
            }
            else if (canMove(x+1, y)) {
                moveRight();
            }
            else if (canMove(x, y-1)) {
                moveUp();
            }
        break;
    }
}
