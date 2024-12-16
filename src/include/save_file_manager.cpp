#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "globals.hpp"
#include "classes.hpp"

using namespace std;

string save_file_path = "assets/.savefile.txt";

int load_save_file() {
    if(filesystem::exists(save_file_path)) {
        ifstream save_file(save_file_path);
        save_file >> REFRESH_RATE >> FRAMES_PER_SECOND  >> LANG_OPTION >> FRAMES_OPTION; 
        save_file >> keyConfirm >> keyDeny >> keyUp >> keyDown >> keyLeft >> keyRight;
        save_file >> player.maxLighterFuel >> player.lighterFuel;
        save_file >> currentFloor >> currentRoom >> player.getPos().x >> player.getPos().y;
        save_file.close();
        return 1;
    }
    else return 0;
}

void save_to_file() {
    ofstream save_file(save_file_path);
    save_file << REFRESH_RATE << ' ' << FRAMES_PER_SECOND << ' '  << LANG_OPTION << ' '  << FRAMES_OPTION << '\n'; 
    save_file << keyConfirm << ' ' << keyDeny << ' ' << keyUp << ' ' << keyDown << ' ' << keyLeft << ' ' << keyRight << '\n';
    save_file << player.maxLighterFuel << ' ' << player.lighterFuel << '\n';
    save_file << currentFloor << ' ' << currentRoom << '\n' << player.getPos().x << ' ' << player.getPos().y;
    save_file.close();
    return;
}