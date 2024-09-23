#include <vector>
#include <string>
using namespace std;

// X: can't pass, can't see through; O: can't pass, can see through

vector<vector<vector<wstring>>> floor_collisions_source = {
    // FLOOR 1
    {
        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },

        {
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"X . . . . . . . . . . . . . . . . . . . . . . . . X"},
        {L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"},
        },
    },

    // FLOOR 2
    {
        {
            {
                
            }
        }
    }
        
};