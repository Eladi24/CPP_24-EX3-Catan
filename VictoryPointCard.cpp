#include "VictoryPointCard.hpp"


using namespace std;
using namespace ariel;

VictoryPointCard::~VictoryPointCard() {}

devCardAction VictoryPointCard::activate()
{
    // The player can move the robber
    cout << "Player " << _owner->getName() << " has activated a Victory Point card and has gained a victory point" << endl;
    this->setUsed(true);
    return this->_action;
}