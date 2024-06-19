#include <iostream>
#include <vector>
#include "Road.hpp"
#include "Trail.hpp"



using namespace std;
using namespace ariel;

// Destructor
Trail::~Trail() {
    if (this->_hasRoad)
    {
        delete this->_road;
    }
}

// Setters
void Trail::setRoad(const Player* owner)
{
    if (!this->_hasRoad)
    {
        this->_hasRoad = true;
        // Cast away the constness of the owner
        this->_road = new Road(const_cast<Player*>(owner));
    }
    else
    {
        throw invalid_argument("This trail already has a road");
    }
}

double Trail::getLength() const
{
   if (!this->_start.expired() && !this->_end.expired())
   {
       shared_ptr<Vertex> start = this->_start.lock();
       shared_ptr<Vertex> end = this->_end.lock();
       return start->distance(*end);
   }
   else
   {
       throw invalid_argument("One of the vertices of this trail is expired");
   }
}


