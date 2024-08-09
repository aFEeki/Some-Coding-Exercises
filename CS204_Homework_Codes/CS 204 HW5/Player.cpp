//Alp Demir Ekinci
#include "Player.h"
bool Player::put(int column)
{
    return gboard.put_piece(gpiece, column);
}
bool Player::is_winner()
{
    char status = gboard.get_game_status();
    if (status == gpiece)
    {
        return true;
    }
    else
    {
        return false;
    }
}
char Player::get_symbol()
{
    return gpiece;
}
void Player::turn_board()
{
    gboard.turn_board_clockwise();
}
