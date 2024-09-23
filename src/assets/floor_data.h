#include <vector>
#include <string>
using namespace std;

class room_data {
    public:
    vector<wstring> art;
    vector<wstring> collisions;
    vector<wstring> colors;
    vector<wstring> events;
    vector<string> lights;
    vector<string> pickups;
};

class floor_data {
    public:
    vector<room_data>room;
    vector<string> layout;
};