#include <iostream>
#include <vector>
#include "Settlement.hpp"
#include "Point.hpp"

using namespace std;
using namespace ariel;

// Constructor, the settlement class inherits from the structure class
Settlement::Settlement(Player owner): Structure(owner), _isCity(false) {}

// Destructor
Settlement::~Settlement() {}

void Settlement::yieldResources()
{
    
}

