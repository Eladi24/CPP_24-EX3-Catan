#include <iostream>
#include <vector>
#include "Trail.hpp"


using namespace std;
using namespace ariel;

// Constructor
Trail::Trail(const Player* owner, Vertex start, Vertex end): _owner(owner), _start(start), _end(end), _hasRoad(true) {}

Trail::Trail(Vertex start, Vertex end): _owner(nullptr), _start(start), _end(end), _hasRoad(false) {}

// Destructor
Trail::~Trail() {}

// Getters
Player Trail::getOwner()
{
    return *this->_owner;
}

bool Trail::hasRoad()
{
    return this->_hasRoad;
}

Vertex Trail::getStart()
{
    return this->_start;
}

Vertex Trail::getEnd()
{
    return this->_end;
}

// Setters
void Trail::setRoad(const Player* owner)
{
    if (!this->_hasRoad)
    {
        this->_hasRoad = true;
        this->_owner = owner;
    }
    else
    {
        throw "This trail already has a road";
    }
}


