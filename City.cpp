
#include "City.hpp"

using namespace std;
using namespace ariel;

City::~City() {}

void City::yieldResources(ResourceType resource)
{
    _owner->addResource(resource, _productionRate);
    cout << "City produced for player " << _owner->getName() << " " << _productionRate << " " << resource << endl;
}