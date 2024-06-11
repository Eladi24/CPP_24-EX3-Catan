#include <iostream>
#include <vector>

#include "Structure.hpp"

using namespace std;
using namespace ariel;

// Constructor
Structure::Structure(Player owner): _owner(owner) {}

// Destructor
Structure::~Structure() {}

// Get the owner of the structure

Player Structure::getOwner()
{
    return this->_owner;
}
