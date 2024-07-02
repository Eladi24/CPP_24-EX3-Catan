// ID: 205739907
// Email: eladima66@gmail.com

#include "City.hpp"

using namespace std;
using namespace ariel;

City::~City() {}

void City::yieldResources(ResourceType resource, Cashbox &cashbox)
{
    _owner->addResource(resource, cashbox, _productionRate);
    cout << "City produced for player " << _owner->getName() << " " << _productionRate << " " << resource << endl;
}