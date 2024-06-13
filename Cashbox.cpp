#include <iostream>
#include <algorithm> // Add this line to include the <algorithm> header

#include "Cashbox.hpp"

using namespace std;
using namespace ariel;

// Constructor
Cashbox::Cashbox()
{
    this->init();
}

// Destructor
Cashbox::~Cashbox()
{
    // Nothing to do here
}

// Cashbox initialization
void Cashbox::init()
{
     // Initialize the development cards
    for (int i = 0; i < 14; i++)
    {
        DevCard KNIGHT (CardType::KNIGHT, "Knight", "Move the robber and steal a resource card from another player", 3);
        devCards.push_back(KNIGHT);
    }

    for (int i = 0; i < 5; i++)
    {
        DevCard VICTORY_POINT (CardType::VICTORY_POINT, "Victory Point", "Gain 1 victory point", 1);
        devCards.push_back(VICTORY_POINT);
    }

    for (int i = 0; i < 2; i++)
    {
        DevCard roadBuilding (ROAD_BUILDING, "Road Building", "Build 2 roads", 2);
        devCards.push_back(roadBuilding);
    }

    for (int i = 0; i < 2; i++)
    {
        DevCard yearOfPlenty (YEAR_OF_PLENTY, "Year of Plenty", "Gain 2 resource cards of your choice", 2);
        devCards.push_back(yearOfPlenty);
    }

    for (int i = 0; i < 2; i++)
    {
        DevCard monopoly (MONOPOLY, "Monopoly", "Take all resource cards of a single type from all players", 2);
        devCards.push_back(monopoly);
    }

    DevCard largestArmy (LARGEST_ARMY, "Largest Army", "Gain 2 victory points", 2);
    devCards.push_back(largestArmy);

    DevCard longestRoad (LONGEST_ROAD, "Longest Road", "Gain 2 victory points", 2);
    devCards.push_back(longestRoad);

    // Initialize the resource cards

    for (int i = 0; i < 19; i++)
    {
        ResourceCard wood;
        wood.type = Wood;
        wood.available = true;
        woodCards.push_back(wood);
        ResourceCard brick;
        brick.type = Brick;
        brick.available = true;
        brickCards.push_back(brick);
        ResourceCard ore;
        ore.type = Ore;
        ore.available = true;
        oreCards.push_back(ore);
        ResourceCard wool;
        wool.type = Wool;
        wool.available = true;
        woolCards.push_back(wool);
        ResourceCard grain;
        grain.type = Grain;
        grain.available = true;
        grainCards.push_back(grain);

    }
}

void Cashbox::shuffleDevCards()
{
    // Shuffle the development cards
    random_shuffle(devCards.begin(), devCards.end());
}

void Cashbox::shuffleResourceCards()
{
    // Shuffle the resource cards
    random_shuffle(woodCards.begin(), woodCards.end());
    random_shuffle(brickCards.begin(), brickCards.end());
    random_shuffle(oreCards.begin(), oreCards.end());
    random_shuffle(woolCards.begin(), woolCards.end());
    random_shuffle(grainCards.begin(), grainCards.end());
}

DevCard Cashbox::drawDevCard()
{
    if (devCards.empty())
    {
        throw "No development cards left in the deck";
    }
    // Draw a development card
    DevCard card = devCards.back();
    // Remove the card from the deck
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
                throw "No wood cards left in the deck";
            }
            card = woodCards.back();
            woodCards.pop_back();
            break;
        case ResourceType::Brick:
            if (brickCards.empty())
            {
                throw "No brick cards left in the deck";
            }
            card = brickCards.back();
            brickCards.pop_back();
            break;
        case ResourceType::Ore:
            if (oreCards.empty())
            {
                throw "No ore cards left in the deck";
            }
            card = oreCards.back();
            oreCards.pop_back();
            break;
        case ResourceType::Wool:
            if (woolCards.empty())
            {
                throw "No wool cards left in the deck";
            }
            card = woolCards.back();
            woolCards.pop_back();
            break;
        case ResourceType::Grain:
            if (grainCards.empty())
            {
                throw "No grain cards left in the deck";
            }
            card = grainCards.back();
            grainCards.pop_back();
            break;
        default:
            throw "Invalid resource type";
    }
    return card;
}

void Cashbox::returnDevCard(DevCard card)
{
    // Return a development card to the deck
    devCards.push_back(card);
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
            throw "Invalid resource type";
    }
}

void Cashbox::loanResourceCard(Player* p, ResourceCard cardToGive, ResourceType cardToGet)
{
    if (p->getResourceAmount(cardToGive.type) < 4)
    {
        throw "Player does not have enough resources to loan";
    }

    p->removeResource(cardToGive.type, 4);
    ResourceCard card = drawResourceCard(cardToGet);
    p->addResource(cardToGet, 1);
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
            throw "Invalid resource type";
    }
}





