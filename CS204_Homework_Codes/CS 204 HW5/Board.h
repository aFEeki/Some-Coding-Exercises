//Alp Demir Ekinci
#ifndef Board_h
#define Board_h

#include <string>
#include <iostream>
#include <ostream>

using namespace std;

class Board
{
private:
    char ** gboard;
    int size;
    int Nvalue;
public:
    Board(int dimension, int N); //construction declaration
    ~Board(); //deconstructor declaration
    void print_board(); //fuction declarations.
    bool put_piece(char piece, int colloc);
    void turn_board_clockwise();
    char get_game_status();
};
#endif /* Board_h */
