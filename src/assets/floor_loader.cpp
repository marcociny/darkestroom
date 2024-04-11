#include <vector>
#include <string>
#include "floor_data.h"
#include "pickups_n_enemies.h"
#include "map/floor_art.h"
#include "map/floor_collisions.h"
#include "map/floor_colors.h"
#include "map/floor_events.h"
#include "map/floor_lights.h"
#include "map/floor_layout.h"
#include "map/floor_entities.h"
#include "map/floor_pickups.h"
using namespace std;


void load_floor(int floor_n) {
    
    floors[floor_n].room.resize(floor_art_source[floor_n].size());
    floors[floor_n].layout = floor_layout_source[floor_n];

    for(int i = 0; i < floor_art_source[floor_n].size(); i++) {
        floors[floor_n].room[i].art = floor_art_source[floor_n][i];
        floors[floor_n].room[i].collisions = floor_collisions_source[floor_n][i];
        floors[floor_n].room[i].colors = floor_colors_source[floor_n][i];
        floors[floor_n].room[i].events = floor_events_source[floor_n][i];
        floors[floor_n].room[i].lights = floor_lights_source[floor_n][i];
        floors[floor_n].room[i].entities = floor_entities_source[floor_n][i];
        floors[floor_n].room[i].pickups = floor_pickups_source[floor_n][i];
    }

    current_room = (int)floors[floor_n].layout[floor_layout_y][floor_layout_x]-48;

    return;
}