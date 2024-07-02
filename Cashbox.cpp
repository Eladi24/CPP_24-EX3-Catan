// ID: 205739907
// Email: eladima66@gmail.com

#include <iostream>
#include <algorithm> 

#include "Cashbox.hpp"
#include "KnightCard.hpp"
#include "ProgressCard.hpp"
#include "VictoryPointCard.hpp"
using namespace std;
using namespace ariel;

// Constructor
Cashbox::Cashbox(): _largestArmyHolder(nullptr), _longestRoadHolder(nullptr)
{
    this->init();
}

// Destructor
Cashbox::~Cashbox()
{
    
    for (auto& card : devCards)
    {
        delete card;
    }
    devCards.clear();
    
}

// Cashbox initialization
void Cashbox::init()
{
     // Initialize the development cards
    for (int i = 0; i < 14; i++)
    {
        
        DevCard* knight = new KnightCard();
        devCards.push_back(move(knight));
    }

    for (int i = 0; i < 5; i++)
    {
        DevCard* victoryPoint = new VictoryPointCard();
        devCards.push_back(move(victoryPoint));
    }

    for (int i = 0; i < 2; i++)
    {
        DevCard* roadBuilding = new RoadBuilding(CardType::PROGRESS);
        devCards.push_back(move(roadBuilding));

        DevCard* yearOfPlenty = new YearOfPlenty(CardType::PROGRESS);
        devCards.push_back(move(yearOfPlenty));

        DevCard* monopoly = new Monopoly(CardType::PROGRESS);
        devCards.push_back(move(monopoly));
    }
    this->shuffleDevCards();

    // Initialize the resource cards

    for (int i = 0; i < 19; i++)
    {
        ResourceCard wood;
        wood.type = ResourceType::Wood;
        wood.available = true;
        woodCards.push_back(wood);
        ResourceCard brick;
        brick.type = ResourceType::Brick;
        brick.available = true;
        brickCards.push_back(brick);
        ResourceCard ore;
        ore.type = ResourceType::Ore;
        ore.available = true;
        oreCards.push_back(ore);
        ResourceCard wool;
        wool.type = ResourceType::Wool;
        wool.available = true;
        woolCards.push_back(wool);
        ResourceCard grain;
        grain.type = ResourceType::Grain;
        grain.available = true;
        grainCards.push_back(grain);

    }
}

void Cashbox::shuffleDevCards()
{
    // Shuffle the development cards
    random_shuffle(devCards.begin(), devCards.end());
}


DevCard* Cashbox::drawDevCard()
{
    if (devCards.empty())
    {
        throw invalid_argument("No development cards left in the deck");
    }
    // Draw a development card
    DevCard* card = move(devCards.back());
    // Remove the card from the deck, needs to be deleted by the caller
    devCards.pop_back();
    
    return card;
}

ResourceCard Cashbox::drawResourceCard(ResourceType type)
{
    // Draw a resource card
    ResourceCard card;
    switch (type)
    {
        case ResourceType::Wood:
            if (woodCards.empty())
            {
                throw invalid_argument("No wood cards left in the deck");
            }
            card = woodCards.back();
            woodCards.pop_back();
            break;
        case ResourceType::Brick:
            if (brickCards.empty())
            {
                throw invalid_argument("No brick cards left in the deck");
            }
            card = brickCards.back();
            brickCards.pop_back();
            break;
        case ResourceType::Ore:
            if (oreCards.empty())
            {
                throw invalid_argument("No ore cards left in the deck");
            }
            card = oreCards.back();
            oreCards.pop_back();
            break;
        case ResourceType::Wool:
            if (woolCards.empty())
            {
                throw invalid_argument("No wool cards left in the deck");
            }
            card = woolCards.back();
            woolCards.pop_back();
            break;
        case ResourceType::Grain:
            if (grainCards.empty())
            {
                throw invalid_argument("No grain cards left in the deck");
            }
            card = grainCards.back();
            grainCards.pop_back();
            break;
        default:
            throw invalid_argument("Invalid resource type");
    }
    return card;
}

void Cashbox::returnDevCard(DevCard* card)
{
    // Return a development card to the deck
    devCards.push_back(move(card));
}

void Cashbox::returnResourceCard(ResourceCard card)
{
    // Return a resource card to the deck
    switch (card.type)
    {
        case ResourceType::Wood:
            woodCards.push_back(card);
            break;
        case ResourceType::Brick:
            brickCards.push_back(card);
            break;
        case ResourceType::Ore:
            oreCards.push_back(card);
            break;
        case ResourceType::Wool:
            woolCards.push_back(card);
            break;
        case ResourceType::Grain:
            grainCards.push_back(card);
            break;
        default:
            throw invalid_argument("Invalid resource type");
    }
}

void Cashbox::loanResourceCard(Player* p, ResourceCard cardToGive, ResourceType cardToGet)
{
    if (p->getResourceAmount(cardToGive.type) < 4)
    {
        throw invalid_argument("Player does not have enough resources to loan");
    }

    p->removeResource(cardToGive.type, *this, 4);
    p->addResource(cardToGet, *this, 1);
}

int Cashbox::getNumResourceCards(ResourceType type)
{
    switch (type)
    {
        case ResourceType::Wood:
            return woodCards.size();
        case ResourceType::Brick:
            return brickCards.size();
        case ResourceType::Ore:
            return oreCards.size();
        case ResourceType::Wool:
            return woolCards.size();
        case ResourceType::Grain:
            return grainCards.size();
        default:
            throw invalid_argument("Invalid resource type");
    }
}




CardType Cashbox::peekDeck()
{
    if (devCards.empty())
    {
        throw invalid_argument("No development cards left in the deck");
    }
    return devCards.back()->getCardType();
}

void Cashbox::printDeck()
{
    for (auto& card : devCards)
    {
        cout << card->getCardType() << endl;
    }
}

void Cashbox::setLargestArmyHolder(Player* p)
{
    if (_largestArmyHolder != nullptr)
    {
        _largestArmyHolder->takeLargestArmyCard();
        p->setLargestArmyHolder();
    }
    else
    {
        p->setLargestArmyHolder();
    }
}

void Cashbox::setLongestRoadHolder(Player* p)
{
    if (_longestRoadHolder != nullptr)
    {
        _longestRoadHolder->takeLongestRoadCard();
        p->setLongestRoadHolder();
    }
    else
    {
        p->setLongestRoadHolder();
    }
}





