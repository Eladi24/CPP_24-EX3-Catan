#include "VictoryPointCard.hpp"


using namespace std;
using namespace ariel;

VictoryPointCard::~VictoryPointCard() {}

void VictoryPointCard::activate()
{
    _owner->addVictoryPoints(1);
}