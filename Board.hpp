#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <unordered_map>
#include <utility>
#include <memory>
#include "Point.hpp"
#include "Vertex.hpp"
#include "Trail.hpp"
#include "Hexagon.hpp"



using namespace std;

namespace ariel
{
    class Board
    {
    private:
        // A 2D array of hexagons in size 5x5 as a vector of vectors
        vector<vector<Hexagon>> _hexagonGrid;
        // A map of points to vertices
        map<Point, shared_ptr<Vertex>> _verticesMap;
        // A map of points to edges
        map<pair<shared_ptr<Vertex>, shared_ptr<Vertex>>, shared_ptr<Trail>> _edgesMap;

        // A map of points to hexagons
        map<Point, Hexagon> _hexagonsMap;

    public:
        Board(); // constructor
        ~Board(); // destructor
        void initHexagons();

        const Hexagon& getHexagon(int q, int r) const { return this->_hexagonGrid[q][r]; }
        
        void printBoard();
    };
} // namespace ariel


#endif