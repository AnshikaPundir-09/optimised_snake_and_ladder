#include "board.h"

int Snaketail(int position) 
{
    switch (position) 
    {
        case 99: return 78;
        case 95: return 75;
        case 92: return 88;
        case 89: return 68;
        case 74: return 53;
        case 62: return 19;
        case 49: return 11;
        case 46: return 25;
        case 16: return 6;
        default: return position;
    }
}
int ladderClimb(int position)
{
    switch (position) 
    {
        case 2: return 38;
        case 7: return 14;
        case 8: return 31;
        case 15: return 26;
        case 21: return 42;
        case 28: return 84;
        case 36: return 44;
        case 51: return 67;
        case 71: return 91;
        case 78: return 98;
        case 87: return 94;
        default: return position;
    }
}

