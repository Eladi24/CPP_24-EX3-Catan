#include <iostream>


#include "Board.hpp"

using namespace std;
using namespace ariel;

// Constructor
Board::Board()
{
    this->initHexagons();
}

// Destructor
Board::~Board() {}

// Initialize the hexagons of the board
const Hexagon& Board::getHexagon(int q, int r) const
{
    return this->_hexagons.at({q, r});
}

// Place a settlement on the board

void Board::placeSettlement(const Player& owner, const Point& point)
{
    this->_vertices[point].buildCity(&owner);
}

// Place a city on the board
void Board::placeCity(const Player& owner, const Point& point)
{
    this->_vertices[point].buildCity(&owner);
}

void Board::placeRoad(const Player& owner, const Point& start, const Point& end)
{
    this->_edges[{start, end}].setRoad(&owner);
}

// Initialize the hexagons of the board
void Board::initHexagons()
{
    for (int q = -2; q <= 2; q++)
    {
        for (int r = -2; r <= 2; r++)
        {
            if (q + r >= -2 && q + r <= 2)
            {
                Point center = Point(q, r);
                Hexagon hex = Hexagon(Forest, 3, center, 0);
                this->_hexagons[center] = hex;
            }
        }
    }
}

// Print the board

void Board::printBoard()
{
    for (int q = -2; q <= 2; q++)
    {
        for (int r = -2; r <= 2; r++)
        {
            if (q + r >= -2 && q + r <= 2)
            {
                cout << "Hexagon at (" << q << ", " << r << "): " << this->_hexagons[{q, r}].getLandType() << endl;
            }
        }
    }
}
