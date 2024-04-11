#include <vector>
#include <string>
#include "globals.h"
#include "floor_data.h"

struct pickup {
    
    wchar_t icon;
    char color;
    char ID;
    int type;

}
lighter_fuel = {L'[', 'W', '1', 0},
note[10] = {
    {L'n', 'W', '2', 0},
    {L'n', 'W', '2', 1},
    {L'n', 'W', '2', 2},
    {L'n', 'W', '2', 3},
    {L'n', 'W', '2', 4},
    {L'n', 'W', '2', 5},
    {L'n', 'W', '2', 6},
    {L'n', 'W', '2', 7},
    {L'n', 'W', '2', 8},
    {L'n', 'W', '2', },
},
bandaid = {L'b', 'W', '3', 0},
medkit = {L'+', 'W', '4', 0};

void spawn_pickup(pickup p, int x, int y, int room_n) {
    auto& r = floors[current_floor].room[room_n];

    r.art[y][x] = p.icon;
    r.colors[y][x] = p.color;
    r.events[y][x] = p.ID;

}