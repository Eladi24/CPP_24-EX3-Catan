#include <iostream>
#include <vector>

#include "Vertex.hpp"

using namespace std;
using namespace ariel;

// Constructor
Vertex::Vertex(int x, int y, int id): Point(x, y), _id(id), _owner(nullptr), _structure(nullptr), _isOccupied(false), _isCity(false) {}

Vertex::Vertex(int x, int y, int id, Player* owner, Structure* structure): Point(x, y), _id(id), _owner(owner), _structure(structure), _isOccupied(true), _isCity(false) {}

// Destructor
Vertex::~Vertex() {}

// Add a neighbor to the vertex
void Vertex::addNeighbor(Vertex v)
{
    this->_neighbors.push_back(v);
}

// Build a settlement on the vertex
void Vertex::buildSettlement(Player* p)
{
    if (this->_isOccupied && this->_owner != p)
    {
        throw "Cannot build a settlement on an occupied vertex";
    }
    this->_owner = p;
    this->_isOccupied = true;
    this->_structure = new Settlement(*p);
}

// Build a city on the vertex

void Vertex::buildCity(Player* p)
{
    if (this->_isOccupied && this->_owner != p)
    {
        throw "This vertex is already occupied by" + this->_owner->getName();
    } 
    else if (!this->_isOccupied)
    {
        throw "Cannot build a city on an unoccupied vertex";
    }

    this->_isCity = true;
    this->_structure = new City(*p);
    
}
