#include <vector>
#include <utility>
#include <string>
using namespace std;

vector<int>floor_starting_rooms = {1, 0, 0, 0, 0, 0, 0};

// line and column of room in floor_layout_source
vector<pair<int,int>> starting_room_layout_index = {{0, 1}, {0, 0}};

vector<pair<int, int>>floor_starting_coords = {{4, 6}, {0, 0}};

vector<vector<string>> floor_layout_source = {

    {
        "012",
        "345",
        "678",
    },

    {

    },

};