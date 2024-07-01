#include "KnightCard.hpp"

using namespace ariel;

KnightCard::~KnightCard() {}

devCardAction KnightCard::activate()
{
    if (!this->_canUse || this->_used)
    {
        throw invalid_argument("The card cannot be used");
    }
    // The player can move the robber
    cout << "Player " << _owner->getName() << " has activated a Knight card and can move the robber" << endl;
    this->setUsed(true);
    return devCardAction::ACT_AS_ROBBER;
}