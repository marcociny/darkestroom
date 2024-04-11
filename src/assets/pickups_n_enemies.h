#include <vector>
#include <string>

struct pickup {
    
    wchar_t icon;
    char color;
    char ID;
    int type;

}
lighter_fuel_pickup = {L'[', 'W', '1', 0},
note_pickup[10] = {
    {L'n', 'W', '2', 0},
    {L'n', 'W', '2', 1},
    {L'n', 'W', '2', 2},
    {L'n', 'W', '2', 3},
    {L'n', 'W', '2', 4},
    {L'n', 'W', '2', 5},
    {L'n', 'W', '2', 6},
    {L'n', 'W', '2', 7},
    {L'n', 'W', '2', 8},
    {L'n', 'W', '2', 9},
},
bandaid_pickup = {L'b', 'W', '3', 0},
medkit_pickup = {L'+', 'W', '4', 0};