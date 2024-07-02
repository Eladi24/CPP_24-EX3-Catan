// ID: 205739907
// Email: eladima66@gmail.com

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
        // A map of center points to vertices vectors
        map<Point, vector<shared_ptr<Vertex>>> _verticesMap;
        // A map of center points to edges vectors
        map<Point, vector<shared_ptr<Trail>>> _edgesMap;

        // A map of center points to hexagons
        map<Point, shared_ptr<Hexagon>> _hexagonsMap;

        void printBoard(sf::RenderWindow& window);

        

    public:
        Board(); // constructor
        ~Board(); // destructor

        /*
        * @brief
        * This function initializes the hexagons on the board.
        * It creates 19 hexagons with the appropriate land type, resource type, and value.
        * It uses shared pointers so the matching vertices and edges are shared between the hexagons.
        */
        void initHexagons();
        /*
        * @brief
        * Get a hexagon from the board by its center point.
        * @param q The q coordinate of the hexagon.
        * @param r The r coordinate of the hexagon.
        * @return A shared pointer to the hexagon.
        */
        shared_ptr<Hexagon> getHexagon(int q, int r) const { return this->_hexagonsMap.at(Point(q, r)); }
        
        /*
        * @brief
        * Get a vertex from the board by its center point.
        * @param places A vector of land types that the vertex should be on.
        * @param placesNum A vector of the number of vertices that should be on each land type.
        * @return A shared pointer to the vertex.
        */
        shared_ptr<Vertex> getVertex(vector<LandType>& places, vector<int>& placesNum) const;

        /*
        * @brief
        * Gets the hexagons map.
        */
        map<Point, shared_ptr<Hexagon>> getHexagonsMap() const { return this->_hexagonsMap; }
        
        /*
        * @brief
        * This function checks if a vertex matches the given land types and number of vertices.
        * @param v The vertex to check.
        * @param places A vector of land types that the vertex should be on.
        * @param placesNum A vector of the number of vertices that should be on each land type.
        * @return True if the vertex matches the given land types and number of vertices, false otherwise.
        */
        bool vertexMatches(shared_ptr<Vertex> v, vector<LandType>& places, vector<int>& placesNum) const;

        /*
        * @brief
        * This gets the neighbor vertices of a given vertex.
        * @param v The vertex to get the neighbors of.
        * @return A vector of shared pointers to the neighbor vertices.
        */
        vector<shared_ptr<Vertex>> getNeighborVertices(shared_ptr<Vertex> v) const;
        /*
        * @brief
        * This function checks if a road exists between two vertices.
        * @param v1 The first vertex.
        * @param v2 The second vertex.
        * @return True if a road exists between the two vertices, false otherwise.
        */
        bool hasRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const;

        shared_ptr<Trail> getTrail(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const;
        /*
        * @brief
        * This function gets the hexagon that the robber is on.
        * @return A shared pointer to the hexagon that the robber is on.
        */
        shared_ptr<Hexagon> getRobberHexagon() const;

        /*
        * @brief
        * This function draws the board on the screen using SFML.
        */
        void printBoard();
        
        /*
        * @brief
        * This function checks if a vertex is within the distance rule according to the Catan game rules.
        * @param v The vertex to check.
        * @return True if the vertex is within the distance rule, false otherwise.
        */
        bool distanceRule(shared_ptr<Vertex> v);
        
    };
} // namespace ariel


#endif