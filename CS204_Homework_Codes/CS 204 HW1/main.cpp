
// Written by Alp Demir Ekinci 31935
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
void printmatrix(const vector<vector<char>>& matrix) //Prints the matrix by iterating through every char.
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}
bool upcheck(const vector<vector<char>>& matrix,int row) //Checks if the coordinate above is there or not.
{
    if (row > -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool downcheck(const vector<vector<char>>& matrix, int row, int colsize) //Checks if the coordinate under is there or not.
{
    if (row < colsize)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool leftcheck(const vector<vector<char>>& matrix, int column) //Checks if the left coordinate is there or not.
{
    if (column > -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool rightcheck(const vector<vector<char>>& matrix, int column, int rowsize) //Checks if the right coordinate is there or not.
{
    if (column < rowsize)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void totalmovementcheck(const vector<vector<char>>& matrix, int rowsize, int colsize, bool& iteration, int& numofdash) //Checks for total movement available to be done in the matrix.
{
    int totalnumber = 0;
    numofdash = 0;
    for (int i = 0; i < rowsize; ++i)
    {
        for (int j = 0; j < colsize; ++j)
        {
            char current = matrix[i][j];
            // Count dashes
            if (current == '-')
            {
                ++numofdash;
            }
            // Check movements for each direction
            if (current == 'u' && upcheck(matrix, i))
            {
                if (i == 0 || matrix[i - 1][j] == '-')
                {
                    ++totalnumber;
                }
            }
            else if (current == 'd' && downcheck(matrix, i, rowsize))
            {
                if (i == rowsize - 1 || matrix[i + 1][j] == '-')
                {
                    ++totalnumber;
                }
            }
            else if (current == 'l' && leftcheck(matrix, j))
            {
                if (j == 0 || matrix[i][j - 1] == '-')
                {
                    ++totalnumber;
                }
            }
            else if (current == 'r' && rightcheck(matrix, j, colsize))
            {
                if (j == colsize - 1 || matrix[i][j + 1] == '-')
                {
                        ++totalnumber;
                }
            }
        }
    }
    // Updates iteration. Iteration is used in the game itself / to keep the game going.
    iteration = (totalnumber > 0) && (numofdash != rowsize * colsize);
}

int main()
{
    string filename;
    cout << "Please enter the file name:" << endl;
    cin >> filename;
    ifstream inputfile(filename);
    while (!inputfile.is_open()) //classic file check.
    {
        inputfile.clear();
        cout << "Could not open the file. Please enter a valid file name:" <<endl;
        cin >> filename;
        inputfile.open(filename);
    }
    vector<vector<char>> matrix;
    vector<char> temprow;
    string line;
    int rowlength;
    bool firstrow = true;
    int firstrowlength = 0;
    while (getline(inputfile, line)) //goes through every line in the matrix while doing the subsequent input checks.
    {
        temprow.clear();
        for (char letter : line)
        {
            if (letter != 'u' && letter != 'd' && letter != 'l' && letter != 'r' && letter != '-') //checks if the letter in the line is valid.
            {
                cout << "Erroneous file content. Program terminates.";
                return 1;
                // end the code.
            }
            temprow.push_back(letter);
        }
        matrix.push_back(temprow);
        rowlength = temprow.size();
        if (firstrow == true)
        {
            firstrowlength = temprow.size();
            firstrow = false;
        }
        else if (temprow.size() != firstrowlength)
        {
            cout << "Erroneous file content. Program terminates.";
            return 1;
        }
    }
    int rowsize = matrix.size();
    int colsize = matrix[0].size();
    cout << "The matrix file contains:" << endl;
    printmatrix(matrix);
    string coordinates;
    bool iteration = true;
    int numofdash = 0;
    totalmovementcheck(matrix, rowsize, colsize, iteration, numofdash);
    while (iteration) //this is the main movement function where all the magic happens.
    {
        numofdash = 0;
        cout << "Please enter the row and column of the tile that you want to move:" << endl; //row and column input.
        int row;
        int column;
        cin >> row >> column;
        while ((row < rowsize && column < colsize && row >= 0 && column >= 0) == false) // to check if the coordinate is in the matrix.
        {
            cout << "Invalid row or column index." << endl;
            cout << "Please enter the row and column of the tile that you want to move:" << endl;
            cin >> row >> column;
        }
        char matrixletter = matrix[row][column];
        if (matrixletter == 'u' && upcheck(matrix, row) == true) //if the letter is u checks if there is a viable movement and does it if there is.
        {
            int temprow = row - 1;
            bool turntime = true; //turntime for if there is another letter in the next space.
            while (temprow > -1 && turntime == true) //if the next space is in the matrix and there isn't another letter.
            {
                if (matrix[temprow][column] == '-')
                {
                    --temprow;
                }
                else
                {
                    turntime = false;
                }
            }
            if (temprow == - 1) //for the special cases where the the letter is in the edges of the matrix.
            {
                matrix[row][column] = '-';
                matrix[temprow + 1][column] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
            else if (turntime == false) //procs when encountered with another letter.
            {
                matrix[row][column] = '-'; //turns the starting location into dash.
                matrix[temprow + 1][column] = 'u'; //turns the current location into the letter.
                if (temprow + 1 == row) //procs if the letter couldn't move at all.
                {
                    matrix[row][column] = 'u';
                    cout <<"No tiles have been moved." << endl;
                }
                else
                {
                    cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
                }
            }
            else //for the rest of the cases.
            {
                matrix[temprow][column] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
        }
        else if (matrixletter == 'd' && downcheck(matrix, row, rowsize)) //Same logic with u. Just different variables.
        {
            int temprow = row + 1;
            bool turntime = true;
            while (temprow < rowsize && turntime == true)
            {
                if (matrix[temprow][column] == '-')
                {
                    ++temprow;
                }
                else
                {
                    turntime = false;
                }
            }
            if (temprow == rowsize)
            {
                matrix[row][column] = '-';
                matrix[temprow - 1][column] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
            else if(turntime == false)
            {
                matrix[row][column] = '-';
                matrix[temprow - 1][column] = 'd';
                if (temprow - 1 == row)
                {
                    matrix[row][column] = 'd';
                    cout << "No tiles have been moved." << endl;
                }
                else
                {
                    cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
                }
            }
            else
            {
                matrix[temprow][column] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
        }
        else if (matrixletter == 'l' && leftcheck(matrix, column)) //same logic.
        {
            int tempcol = column - 1;
            bool turntime = true;
            while (tempcol > -1 && turntime == true)
            {
                if (matrix[row][tempcol] == '-')
                {
                    --tempcol;
                }
                else
                {
                    turntime = false;
                }
            }
            if (tempcol == - 1)
            {
                matrix[row][column] = '-';
                matrix[row][tempcol + 1] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
            else if (turntime == false)
            {
                matrix[row][column] = '-';
                matrix[row][tempcol + 1] = 'l';
                if (tempcol + 1 == column)
                {
                    matrix[row][column] = 'l';
                    cout << "No tiles have been moved." << endl;
                }
                else
                {
                    cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
                }
            }
            else
            {
                matrix[row][tempcol] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
        }
        else if (matrixletter == 'r' && rightcheck(matrix, column, colsize)) //same as before.
        {
            int tempcol = column + 1;
            bool turntime = true;
            while (tempcol < colsize && turntime == true)
            {
                if (matrix[row][tempcol] == '-')
                {
                    ++tempcol;
                }
                else
                {
                    turntime = false;
                }
            }
            if (tempcol == colsize)
            {
                matrix[row][column] = '-';
                matrix[row][tempcol - 1] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
            else if (turntime == false)
            {
                matrix[row][column] = '-';
                matrix[row][tempcol - 1] = 'r';
                if (tempcol - 1 == column)
                {
                    matrix[row][column] = 'r';
                    cout << "No tiles have been moved." << endl;
                }
                else
                {
                    cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
                }
            }
            else
            {
                matrix[row][tempcol] = '-';
                cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
            }
        }
        else if (matrixletter == '-')
        {
            cout << "No tiles have been moved." << endl;
        }
        printmatrix(matrix);
        totalmovementcheck(matrix, rowsize, colsize, iteration, numofdash); //checks total movement and ends it if need be.
    }
    if (numofdash == rowsize * colsize) //for the special case where the entire matrix is made out of -.
    {
        cout << "The matrix is empty.";
    }
    else // ends after the code gets out of the while loop.
    {
        cout << "No more moves are possible.";
    }
    return 0;
}
