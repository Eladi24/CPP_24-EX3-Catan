#include <iostream>
#include <vector>
#include "Settlement.hpp"


using namespace std;
using namespace ariel;

// Destructor
Settlement::~Settlement() {}

void Settlement::yieldResources(ResourceType resource)
{
    _owner->addResource(resource, 1);
    cout << "Settlement produced for player " << _owner->getName() << " 1 " << resource << endl;
}


