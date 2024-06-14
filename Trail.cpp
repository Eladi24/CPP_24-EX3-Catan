#include <iostream>
#include <vector>
#include "Trail.hpp"



using namespace std;
using namespace ariel;

// Destructor
Trail::~Trail() {}

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


ostream& ariel::operator<<(ostream& os, const Trail& trail)
{
    os << trail._start << " -> " << trail._end;
    return os;
}


