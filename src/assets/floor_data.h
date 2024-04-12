#include <vector>
#include <string>
using namespace std;

struct room_data {
    vector<wstring> art;
    vector<wstring> collisions;
    vector<wstring> colors;
    vector<wstring> events;
    vector<wstring> entities;
    vector<string> lights;
    vector<string> pickups;
};

struct floor_data {
    vector<room_data>room;
    vector<string> layout;
}floors[7];