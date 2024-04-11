#include <vector>
#include <string>
using namespace std;

struct room_data {
    vector<wstring> art;
    vector<wstring> collisions;
    vector<wstring> colors;
    vector<wstring> events;
    vector<wstring> lights;
    vector<wstring> entities;
};

struct floor_data {
    vector<room_data>room;
    vector<string> layout;
}floors[7];