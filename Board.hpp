#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <iostream>
#include <unordered_map>
#include <utility>
#include <memory>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"
#include "Player.hpp"
#include "Types.hpp"



using namespace std;

namespace ariel
{
    class Player;
    class Hexagon;

    class Board
    {
    private:
        // A 2D array of hexagons in size 5x5 as a vector of vectors
        vector<vector<shared_ptr<Hexagon>>> _hexagonGrid;
        // A map of points to vertices
        map<Point, shared_ptr<Vertex>> _verticesMap;
        // A map of points to edges
        map<pair<shared_ptr<Vertex>, shared_ptr<Vertex>>, shared_ptr<Trail>> _edgesMap;

        // A map of points to hexagons
        map<Point, shared_ptr<Hexagon>> _hexagonsMap;

        

    public:
        Board(); // constructor
        ~Board(); // destructor
        void initHexagons();

        shared_ptr<Hexagon> getHexagon(int q, int r) const { return this->_hexagonGrid[q][r]; }
        
        shared_ptr<Vertex> getVertex(vector<LandType>& places, vector<int>& placesNum) const;
        map<Point, shared_ptr<Hexagon>> getHexagonsMap() const { return this->_hexagonsMap; }
        
        void printBoard(sf::RenderWindow& window);
        bool vertexMatches(shared_ptr<Vertex> v, vector<LandType>& places, vector<int>& placesNum) const;
        vector<shared_ptr<Vertex>> getNeighborVertices(shared_ptr<Vertex> v) const;
        bool hasRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const;
        shared_ptr<Trail> getTrail(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const;
        void placeRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, const Player* owner);
    };
} // namespace ariel


#endif