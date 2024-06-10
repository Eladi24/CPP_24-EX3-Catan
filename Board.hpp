#ifndef _BOARD_HPP_
#define _BOARD_HPP_


#include <vector>

namespace ariel
{
    class Board
    {
    private:
        std::vector<std::vector<char>> tiles; // 2D vector to represent the board tiles
        int rows; // number of rows in the board
        int columns; // number of columns in the board

    public:
        Board(); // constructor
        ~Board(); // destructor

        void setTile(int row, int column, char value); // method to set the value of a specific tile
        char getTile(int row, int column); // method to get the value of a specific tile

        void displayBoard(); // method to display the board
        void performAction(); // method to perform actions on the board
    };
} // namespace ariel


#endif