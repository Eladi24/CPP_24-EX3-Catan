
#include "ProgressCard.hpp"

using namespace ariel;

YearOfPlenty::~YearOfPlenty()
{
}

devCardAction YearOfPlenty::activate()
{
    if (!this->_canUse || this->_used)
    {
        throw invalid_argument("The card cannot be used");
    }

    cout << "Player " << _owner->getName() << " has activated a Year of Plenty card" << endl;
    return this->_action;
}


RoadBuilding::~RoadBuilding()
{
}

devCardAction RoadBuilding::activate()
{
    if (!this->_canUse || this->_used)
    {
        throw invalid_argument("The card cannot be used");
    }

    cout << "Player " << _owner->getName() << " has activated a Road Building card" << endl;
    return this->_action;
}

Monopoly::~Monopoly()
{
}

devCardAction Monopoly::activate()
{
    if (!this->_canUse || this->_used)
    {
        throw invalid_argument("The card cannot be used");
    }
    
    cout << "Player " << _owner->getName() << " has activated a Monopoly card" << endl;
    return this->_action;
}


// ProgressCard::~ProgressCard()
// {
// }

// void ProgressCard::activate()
// {
//     // The player gets to activate the progress card
//     cout << "Player " << _owner->getName() << " has activated a progress card" << endl;
//     this->setUsed(true);
// }