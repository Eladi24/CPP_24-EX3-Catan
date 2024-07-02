// ID: 205739907
// Email: eladima66@gmail.com

#include <iostream>
#include <vector>
#include "Settlement.hpp"


using namespace std;
using namespace ariel;

// Destructor
Settlement::~Settlement() {}

void Settlement::yieldResources(ResourceType resource, Cashbox &cashbox)
{
    _owner->addResource(resource, cashbox, 1);
    cout << "Settlement produced for player " << _owner->getName() << " 1 " << resource << endl;
}


