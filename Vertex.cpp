#include <iostream>
#include <vector>

#include "Vertex.hpp"
#include "Settlement.hpp"
#include "City.hpp"
#include "Player.hpp"


using namespace std;
using namespace ariel;


// Destructor
Vertex::~Vertex() {
    delete this->_structure;
}

// Add a neighbor to the vertex
void Vertex::addNeighbor(Vertex v)
{
    this->_neighbors.push_back(v);
}

// Build a settlement on the vertex
void Vertex::buildSettlement(Player* p)
{
    if (this->_isOccupied && this->_structure->getOwner() != p) 
    {
        throw "Cannot build a settlement on an occupied vertex";
    }
    
    this->_isOccupied = true;
    this->_structure = new Settlement(p);
}

// Build a city on the vertex

void Vertex::buildCity(Player* p)
{
    if (this->_isOccupied && this->_structure->getOwner() != p)
    {
        throw "This vertex is already occupied by";
    } 
    else if (!this->_isOccupied)
    {
        throw "Cannot build a city on an unoccupied vertex";
    }

    
    // delete the settlement and build a city
    delete this->_structure;
    this->_structure = new City(p);
}

// Yield resources from the vertex
void Vertex::yieldResources(ResourceType resource)
{
    if (this->_isOccupied)
    {
        this->_structure->yieldResources(resource);
    }
    else
    {
        throw "Cannot yield resources from an unoccupied vertex";
    }
}

// Overload the << operator
ostream& ariel::operator<<(ostream& os, const Vertex& vertex)
{
    os << "V" << vertex._id;
    return os;
}




