#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <unordered_map>
#include <utility>
#include <vector>
#include <array>
#include "Hexagon.hpp"
#include "Player.hpp"
#include "Point.hpp"

using namespace std;

namespace ariel
{
    class Board
    {
    private:
        // A 2D array of hexagons in size 5x5 as a vector of vectors
        vector<vector<Hexagon>> _hexagons;
        unordered_map<Point, Hexagon, Point::PointHasher> _hexagons;
        unordered_map<Point, Vertex, Point::PointHasher> _vertices;
        unordered_map<pair<Point, Point>, Trail, pair<Point::PointHasher, Point::PointHasher>> _edges;

    public:
        Board(); // constructor
        ~Board(); // destructor
        const Hexagon& getHexagon(int q, int r) const;

        void placeSettlement(const Player& owner, const Point& point);
        void placeCity(const Player& owner, const Point& point);
        void placeRoad(const Player& owner, const Point& start, const Point& end);
        void initHexagons();
        void printBoard();
    };
} // namespace ariel


#endif