#include <iostream>
#include <vector>

#include "Vertex.hpp"
#include "City.hpp"

using namespace std;
using namespace ariel;

// Constructor
Vertex::Vertex(double x, double y, int id): Point(x, y), _id(id), _owner(nullptr), _structure(nullptr), _isOccupied(false), _isCity(false) {}

Vertex::Vertex(double x, double y, int id, const Player* owner, Structure* structure): Point(x, y), _id(id), _owner(owner), _structure(structure), _isOccupied(true), _isCity(false) {}

// Destructor
Vertex::~Vertex() {}

// Add a neighbor to the vertex
void Vertex::addNeighbor(Vertex v)
{
    this->_neighbors.push_back(v);
}

// Build a settlement on the vertex
void Vertex::buildSettlement(const Player* p)
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

void Vertex::buildCity(const Player* p)
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
    // delete the settlement and build a city
    delete this->_structure;
    this->_structure = new City(*p);
}

// Yield resources from the vertex
void Vertex::yieldResources()
{
    
}

// Check if the vertex is occupied
bool Vertex::isOccupied()
{
    return this->_isOccupied;
}

// Check if the vertex is a city

bool Vertex::isCity()
{
    return this->_isCity;
}

// Get the owner of the vertex
Player Vertex::getOwner()
{
    return *this->_owner;
}

// Get the id of the vertex
int Vertex::getId()
{
    return this->_id;
}


