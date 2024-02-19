#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "assets/globals.h"

using namespace std;

string save_file_path = "assets/.savefile.txt";

int load_save_file() {
    if(filesystem::exists(save_file_path)) {
        ifstream save_file(save_file_path);
        save_file >> current_floor >> current_room >> player_pos.x >> player_pos.y;
        save_file.close();
        return 1;
    }
    else return 0;
}

void save_to_file() {
    ofstream save_file(save_file_path);
    save_file << current_floor << " " << current_room << "\n" << player_pos.x << " " << player_pos.y;
    save_file.close();
    return;
}