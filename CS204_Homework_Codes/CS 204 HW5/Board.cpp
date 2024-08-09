//Alp Demir Ekinci 31935
#include "Board.h"
Board::Board(int dimension, int N) //constructor implementation.
{
    size = dimension;
    Nvalue = N;
    gboard = new char *[size];
    for (int i = 0; i < size; i++)
    {
        gboard[i] = new char[size];
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            gboard[i][j] = '-';
        }
    }
}
Board::~Board() //deconstructor implementation.
{
    for (int i = 0; i < size; ++i)
    {
        delete[] gboard[i];
    }
    delete[] gboard;
}
void Board::print_board() //prints the entire gameboard by going through each element one by one.
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << gboard[i][j];
            
        }
        cout << endl;
    }
    cout << endl;
}
bool Board::put_piece(char piece, int colloc) //inserts a piece into the gameboard while checking if there is a suitable spot.
{
    if (colloc < 0 || colloc >= size) //if the location is out of the gameboard
    {
        return false;
    }
    for (int i = size - 1; i >= 0; i--) //looks for an empty space from bottom-up.
    {
        if (gboard[i][colloc] == '-')
        {
            gboard[i][colloc] = piece;
            return true;
        }
    }
    return false;
}
void Board::turn_board_clockwise()
{
    char** tempboard = new char*[size]; //creates a copy gameboard with the same dimension as the main gameboard
    for (int i = 0; i < size; i++)
    {
        tempboard[i] = new char[size];
    }
    for (int i = 0; i < size; i++) //takes the pieces and turns them 90 degrees before inserting them to the copy gameboard
    {
        for (int j = 0; j < size; j++)
        {
            tempboard[j][size - 1 - i] = gboard[i][j];
        }
    }
    for (int i = 0; i < size; i++) //makes the main gameboard be equal to copy gameboard
    {
        for (int j = 0; j < size; j++)
        {
            gboard[i][j] = tempboard[i][j];
        }
    }
    for (int j = 0; j < size; j++) //implementation of gravity after the 90 degree turn.
    {
        for (int i = size - 1; i >= 0; i--) //checks from bottom up.
        {
            int currentloc = i;
            if (gboard[i][j] != '-')
            {
                while (currentloc < size - 1 && gboard[currentloc + 1][j] == '-')
                {
                    currentloc++;
                }
                if (currentloc != i)
                {
                    gboard[currentloc][j] = gboard[i][j];
                    gboard[i][j] = '-';
                }
            }
        }
    }
    for (int i = 0; i < size; i++) //deletes the copy board.
    {
        delete[] tempboard[i];
    }
    delete[] tempboard;
}
char Board::get_game_status()
{
    int winners = 0; // number of winners.
    char winningchar = '0'; //the winning person
    for (int i = 0; i < size; i++) //checks for horizontal combinations.
    {
        for (int j = 0; j <= size - Nvalue; j++)
        {
            char piece = gboard[i][j];
            if (piece != '-')
            {
                bool win = true;
                for (int k = 1; k < Nvalue; k++)
                {
                    if (gboard[i][j + k] != piece)
                    {
                        win = false;
                    }
                }
                if (win && winningchar != piece)
                {
                    winners += 1;
                    winningchar = piece;
                }
            }
        }
    }
    
    for (int i = 0; i <= size - Nvalue; i++) //checks for vertical combinations.
    {
        for (int j = 0; j < size; j++)
        {
            char piece = gboard[i][j];
            if (piece != '-')
            {
                bool win = true;
                for (int k = 1; k < Nvalue; k++)
                {
                    if (gboard[i + k][j] != piece)
                    {
                        win = false;
                    }
                }
                if (win && winningchar != piece)
                {
                    winners += 1;
                    winningchar = piece;
                }
            }
        }
    }
    
    for (int i = 0; i <= size - Nvalue; i++) //checks for diagonal combinations top left to bottom right.
    {
        for (int j = 0; j <= size - Nvalue; j++)
        {
            char piece = gboard[i][j];
            if (piece != '-')
            {
                bool win = true;
                for (int k = 1; k < Nvalue; k++)
                {
                    if (gboard[i + k][j + k] != piece)
                    {
                        win = false;
                    }
                }
                if (win && winningchar != piece)
                {
                    winners += 1;
                    winningchar = piece;
                }
            }
        }
    }
    
    for (int i = Nvalue - 1; i < size; i++) //checks for diagonal combinations bottom left to top right.
    {
        for (int j = 0; j <= size - Nvalue; j++)
        {
            char piece = gboard[i][j];
            if (piece != '-')
            {
                bool win = true;
                for (int k = 1; k < Nvalue; k++)
                {
                    if (gboard[i - k][j + k] != piece)
                    {
                        win = false;
                    }
                }
                if (win && winningchar != piece)
                {
                    winners += 1;
                    winningchar = piece;
                }
            }
        }
    }
    bool draw = true; // checks for if the board is full and there is no winners.
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (gboard[i][j] == '-')
            {
                draw = false;
            }
        }
    }
    if (winners > 1 || draw == true) // winners > 1 is for the special condition where there are 2 winners after a 90 degree turn.
    {
        return 'D';
    }
    else if (winners == 1)
    {
        return winningchar;
    }
    else
    {
        return '-';
    }
}
/*
 #include "Board.h"
 Board::Board(int dimension, int N)
 {
     row = dimension;
     col = dimension;
     Nvalue = N;
     gboard = new char *[row];
     for (int i = 0; i < row; i++)
     {
         gboard[i] = new char[col];
     }
     for (int i = 0; i < row; i++)
     {
         for (int j = 0; j < col; j++)
         {
             gboard[i][j] = '-';
         }
     }
 }
 Board::~Board()
 {
     for (int i = 0; i < row; ++i)
     {
         delete[] gboard[i];
     }
     delete[] gboard;
 }
 void Board::print_board()
 {
     cout << endl;
     for (int i = 0; i < row; i++)
     {
         for (int j = 0; j < col; j++)
         {
             cout << gboard[i][j];
             
         }
         cout << endl;
     }
     cout << endl;
 }
 bool Board::put_piece(char piece, int colloc)
 {
     if (colloc < 0 || colloc >= col)
     {
         return false;
     }
     for (int i = row - 1; i >= 0; i--)
     {
         if (gboard[i][colloc] == '-')
         {
             gboard[i][colloc] = piece;
             return true;
         }
     }
     return false;
 }
 void Board::turn_board_clockwise()
 {
     char** tempboard = new char*[col];
     for (int i = 0; i < col; i++)
     {
         tempboard[i] = new char[row];
     }
     for (int i = 0; i < row; i++)
     {
         for (int j = 0; j < col; j++)
         {
             tempboard[j][row - 1 - i] = gboard[i][j];
         }
     }
     for (int i = 0; i < col; i++)
     {
         for (int j = 0; j < row; j++)
         {
             gboard[i][j] = tempboard[i][j];
         }
     }
     for (int j = 0; j < col; j++)
     {
         for (int i = row - 1; i >= 0; i--)
         {
             int currentloc = i;
             if (gboard[i][j] != '-')
             {
                 while (currentloc < row - 1 && gboard[currentloc + 1][j] == '-')
                 {
                     currentloc++;
                 }
                 if (currentloc != i)
                 {
                     gboard[currentloc][j] = gboard[i][j];
                     gboard[i][j] = '-';
                 }
             }
         }
     }
     for (int i = 0; i < col; i++)
     {
         delete[] tempboard[i];
     }
     delete[] tempboard;
 }
 char Board::get_game_status()
 {
     int winners = 0;
     char winningchar = '0';
     for (int i = 0; i < row; i++) //checks for horizontal combinations.
     {
         for (int j = 0; j <= col - Nvalue; j++)
         {
             char piece = gboard[i][j];
             if (piece != '-')
             {
                 bool win = true;
                 for (int k = 1; k < Nvalue; k++)
                 {
                     if (gboard[i][j + k] != piece)
                     {
                         win = false;
                     }
                 }
                 if (win && winningchar != piece)
                 {
                     winners += 1;
                     winningchar = piece;
                 }
             }
         }
     }
     
     for (int i = 0; i <= row - Nvalue; i++) //checks for vertical combinations.
     {
         for (int j = 0; j < col; j++)
         {
             char piece = gboard[i][j];
             if (piece != '-')
             {
                 bool win = true;
                 for (int k = 1; k < Nvalue; k++)
                 {
                     if (gboard[i + k][j] != piece)
                     {
                         win = false;
                     }
                 }
                 if (win && winningchar != piece)
                 {
                     winners += 1;
                     winningchar = piece;
                 }
             }
         }
     }
     
     for (int i = 0; i <= row - Nvalue; i++) //diagonal top left to bottom right.
     {
         for (int j = 0; j <= col - Nvalue; j++)
         {
             char piece = gboard[i][j];
             if (piece != '-')
             {
                 bool win = true;
                 for (int k = 1; k < Nvalue; k++)
                 {
                     if (gboard[i + k][j + k] != piece)
                     {
                         win = false;
                     }
                 }
                 if (win && winningchar != piece)
                 {
                     winners += 1;
                     winningchar = piece;
                 }
             }
         }
     }
     
     for (int i = Nvalue - 1; i < row; i++) //diagonal bottom left to top right.
     {
         for (int j = 0; j <= col - Nvalue; j++)
         {
             char piece = gboard[i][j];
             if (piece != '-')
             {
                 bool win = true;
                 for (int k = 1; k < Nvalue; k++)
                 {
                     if (gboard[i - k][j + k] != piece)
                     {
                         win = false;
                     }
                 }
                 if (win && winningchar != piece)
                 {
                     winners += 1;
                     winningchar = piece;
                 }
             }
         }
     }
     bool draw = true; //check for draw from now on.
     for (int i = 0; i < row; i++)
     {
         for (int j = 0; j < col; j++)
         {
             if (gboard[i][j] == '-')
             {
                 draw = false;
             }
         }
     }
     if (winners > 1 || draw == true)
     {
         return 'D';
     }
     else if (winners == 1)
     {
         return winningchar;
     }
     else
     {
         return '-';
     }
 }
 */
