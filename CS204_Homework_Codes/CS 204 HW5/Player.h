//Alp Demir Ekinci
#ifndef Player_h
#define Player_h
#include <string>
#include <iostream>
#include <ostream>
#include "Board.h"

using namespace std;

class Player
{
private:
    Board& gboard;
    char gpiece;
public:
    Player(Board& gboard, char gpiece) : gboard(gboard), gpiece(gpiece){} //takes reference and initializes the variables.
    bool put(int column); //function declarations.
    void turn_board();
    bool is_winner();
    char get_symbol();
};
#endif /* Player_h */
