#include <vector>
#include <string>
#include "floor_data.h"
#include "map/floor_art.h"
#include "map/floor_collisions.h"
#include "map/floor_colors.h"
#include "map/floor_events.h"
#include "map/floor_lights.h"
using namespace std;

void load_floor(int floor_n) {
    
    floors[floor_n].room.resize(floor_art_source[floor_n].size());

    for(int i = 0; i < floor_art_source[floor_n].size(); i++) {
        floors[floor_n].room[i].art = floor_art_source[floor_n][i];
        floors[floor_n].room[i].collisions = floor_collisions_source[floor_n][i];
        floors[floor_n].room[i].colors = floor_colors_source[floor_n][i];
        floors[floor_n].room[i].events = floor_events_source[floor_n][i];
        floors[floor_n].room[i].lights = floor_lights_source[floor_n][i];
    }

    return;
}