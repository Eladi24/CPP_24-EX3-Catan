
#include "ProgressCard.hpp"

using namespace ariel;

// YearOfPlenty::~YearOfPlenty()
// {
// }

// void YearOfPlenty::activate(ResourceType resource1, ResourceType resource2, Cashbox& cashbox)
// {
//     // The player gets two resources of his choice
//     _owner->addResource(resource1, cashbox, 1);
//     _owner->addResource(resource2, cashbox, 1);
//     cout << "Player " << _owner->getName() << " has activated a Year of Plenty card and received 1 " << resource1 << " and 1 " << resource2 << endl;
//     this->setUsed(true);
// }


// RoadBuilding::~RoadBuilding()
// {
// }

// void RoadBuilding::activate(vector<LandType> places, vector<int> placesNum, Board& board, Cashbox& cashbox)
// {
//     // The player gets to build two roads
//     this->_owner->setStartingPhase(true);
    
//     // Split the vector into two vectors
//     vector<LandType> places1(places.begin(), places.begin() + 2);
//     vector<int> placesNum1(placesNum.begin(), placesNum.begin() + 2);

//     vector<LandType> places2(places.begin() + 2, places.end());
//     vector<int> placesNum2(placesNum.begin() + 2, placesNum.end());
//     this->_owner->placeRoad(places1, placesNum1, board, cashbox);
//     this->_owner->placeRoad(places2, placesNum2, board, cashbox);
//     this->_owner->setStartingPhase(false);
    
//     cout << "Player " << _owner->getName() << " has activated a Road Building card and built two roads" << endl;
//     this->setUsed(true);
// }

// Monopoly::~Monopoly()
// {
// }

// void Monopoly::activate(ResourceType resourceToGet, vector<Player*> players)
// {
//     // The player gets 1 resource of his choice from all other players
//     for (auto p : players)
//     {
//         if (p != _owner)
//         {
//             p->stealResource(_owner, resourceToGet);
//         }
//     }
// }


ProgressCard::~ProgressCard()
{
}

void ProgressCard::activate()
{
    // The player gets to activate the progress card
    cout << "Player " << _owner->getName() << " has activated a progress card" << endl;
    this->setUsed(true);
}