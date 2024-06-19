#include <iostream>
#include <vector>
#include "Cashbox.hpp"
#include "Player.hpp"

using namespace std;
using namespace ariel;


Player::~Player()
{
    
}

void Player::initPlayer()
{
    for (auto &[resource, cards] : this->_resourceCards)
    {
        this->_resourceCards[resource] = vector<ResourceCard>();
    }

    for (auto &[cardType, devCards] : this->_devCards)
    {
        this->_devCards[cardType] = vector<DevCard*>();
    }

}

int Player::rollDice()
{
    
    if (this->_isTurn || this->_isStatringPhase)
    {
        return this->_die1.roll() + this->_die2.roll();
    }

    else
    {
        throw invalid_argument("Not player's turn");
    }
}

void Player::endTurn()
{
    this->_isTurn = false;
}

bool Player::trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, uint amountToGive, uint amountToGet)
{
    TradeRequest request = {resourceToGive, resourceToGet, amountToGive, amountToGet};
    if (pToTrade.reviewTradeRequest(request) == true)
    {
        for (size_t i = 0; i < amountToGive; i++)
        {
            ResourceCard card = this->_resourceCards[resourceToGive].back();
            this->_resourceCards[resourceToGive].pop_back();
            pToTrade._resourceCards[resourceToGive].push_back(card);
        }

        for (size_t i = 0; i < amountToGet; i++)
        {
            ResourceCard card = pToTrade._resourceCards[resourceToGet].back();
            pToTrade._resourceCards[resourceToGet].pop_back();
            this->_resourceCards[resourceToGet].push_back(card);
        
        }
    }
    return false;
}

bool Player::reviewTradeRequest(TradeRequest tradeRequest)
{
    // Check if the player has the resources to give
    if (tradeRequest.amountToGet > _resourceCards[tradeRequest.resourceToGet].size())
    {
        return false;
    }
    
    // The trade strategy is to accept the trade if the player has more than 2 of the resource to give
    if (tradeRequest.amountToGet - _resourceCards[tradeRequest.resourceToGet].size() <= 2)
    {
        return false;
    }
    
    return true;
}

bool Player::canTrade(TradeRequest tradeRequest)
{
    if (tradeRequest.amountToGive > _resourceCards[tradeRequest.resourceToGive].size())
    {
        return false;
    }
    
    return true;
}

void Player::addResource(ResourceType resource, Cashbox &cashbox, size_t amount)
{
    // If the ResourceCards in index resource is empty, create a new vector
    if (this->_resourceCards.find(resource) == this->_resourceCards.end())
    {
        this->_resourceCards[resource] = vector<ResourceCard>();
    }

    for (size_t i = 0; i < amount; i++)
    {
        ResourceCard card = cashbox.drawResourceCard(resource);
        this->_resourceCards[resource].push_back(card);
    }
}

void Player::removeResource(ResourceType resource, Cashbox &cashbox, size_t amount)
{
    if (this->_resourceCards[resource].size() == 0 || this->_resourceCards[resource].size() < amount)
    {
        throw invalid_argument("Player does not have enough resources to remove");
    }

    for (size_t i = 0; i < amount; i++)
    {
        ResourceCard card = this->_resourceCards[resource].back();
        this->_resourceCards[resource].pop_back();
        cashbox.returnResourceCard(card);
    }
    
}

void Player::printPoints()
{
    cout << "Player " << this->_name << " has " << this->_victoryPoints << " points." << endl;
}

void Player::buyDevelopmentCard(Cashbox &cashbox)
{
    if (cashbox.canAffordDevCard(*this))
    {
        CardType cardType = cashbox.peekDeck();

        DevCard* card = cashbox.drawDevCard();
        card->setOwner(this);
        this->_devCards[cardType].push_back(card);
    }
}

void Player::addVictoryPoints(int points)
{
    // The maximum number of victory points can be gained in a single turn is 13
    if (points > 13)
    {
        throw invalid_argument("Player cannot gain more than 13 points in a single turn");
    }

    if (points < 0)
    {
        throw invalid_argument("Wrong method to remove points");
    }

    this->_victoryPoints += points;
    cout << "Player " << this->_name << " has gained " << points << " points." << endl;
}

void Player::removeVictoryPoints(int points)
{
    if (points > this->_victoryPoints)
    {
        throw invalid_argument("Player cannot lose more points than they have");
    }

    if (points < 0)
    {
        throw invalid_argument("Wrong method to add points");
    }

    this->_victoryPoints -= points;
    cout << "Player " << this->_name << " has lost " << points << " points." << endl;
}

void Player::placeSettelemnt(vector<LandType> places, vector<int> placesNum, Board &board, Cashbox &cashbox)
{
    if (places.size() != 2 || placesNum.size() != 2)
    {
        throw invalid_argument("Invalid number of arguments");
    }

    if (!this->canAffordSettlement() && !this->_isStatringPhase)
    {
        throw invalid_argument("Player cannot afford to build a settlement");
    }

    shared_ptr<Vertex> vertex = board.getVertex(places, placesNum);
    if (vertex == nullptr)
    {
        throw invalid_argument("Invalid vertex");
    }

    if (this->_structures.find(vertex) != this->_structures.end())
    {
        throw invalid_argument("Vertex already has a structure");
    }
    cout << "Available vertex was found at (" << vertex->getX() << ", " << vertex->getY() << ")" << endl;
    vertex->buildSettlement(this);
    this->_structures[vertex] = vertex->getStructure();
    // Add victory points
    this->addVictoryPoints(1);
    // Deduct resources
    this->deductResourcesForSettlement(cashbox);
    cout << "Player " << this->_name << " has placed a settlement on a shared vertex at " << places[0] << " with number " << placesNum[0] << " and " << places[1] << " with number " << placesNum[1] << endl;
}

void Player::placeRoad(vector<LandType> places, vector<int> placesNum, Board &board, Cashbox &cashbox)
{
    if (places.size() != 2 || placesNum.size() != 2)
    {
        throw std::invalid_argument("Must specify exactly two places and their numbers.");
    }

    // Get the two vertices where the road is supposed to be placed
    shared_ptr<Vertex> v1 = board.getVertex(places, placesNum);

    if (v1 == nullptr)
    {
        throw std::invalid_argument("Cannot build a road");
    }
    cout << "v1: at (" << v1->getX() << ", " << v1->getY() << ")" << endl;

    if (!v1)
    {

        throw std::invalid_argument("Invalid vertex locations.");
        exit(EXIT_FAILURE);
    }

    // Now we need to find a second set of places and placesNum to form the other end of the road
    // Assume the player provides the two sets correctly for the road, let's fetch the second vertex

    // Find potential vertices that are neighbors of v1
    auto neighbors = board.getNeighborVertices(v1);

    shared_ptr<Vertex> v2 = nullptr;
    for (auto &neighbor : neighbors)
    {
        
        if (board.vertexMatches(neighbor, places, placesNum))
        {
            v2 = neighbor;
            cout << "A matching neighbor was found" << endl;
            break;
        }
    }

    if (!v2)
    {
        throw std::invalid_argument("Invalid road placement: second vertex not found.");
    }

    // Check if the player can place the road here (i.e., the player has a settlement or road connected to these vertices)
    if (!this->canPlaceRoad(v1, v2))
    {
        throw std::invalid_argument("Invalid road placement: player does not have a settlement or road connected to these vertices.");
    }

    // Check if there is already a road in this place
    if (board.hasRoad(v1, v2))
    {
        auto road = v1->getTrail(v2)->getRoad();
        if (road->getOwner() == this)
        {
            // Check for available trails to build a road continuation

            if (v1->isOccupied())
            {
                neighbors = board.getNeighborVertices(v2);
                for (auto &neighbor : neighbors)
                {

                    // If the trail between v2 and neighbor is not occupied or neighbor is occupied by the player
                    if (!board.hasRoad(v2, neighbor) || neighbor->getStructure()->getOwner() == this)
                    {
                        v1 = neighbor;
                        break;
                    }
                }
            }
            else if (v2->isOccupied())
            {
                neighbors = board.getNeighborVertices(v1);
                for (auto &neighbor : neighbors)
                {
                    // If the trail between v1 and neighbor is not occupied or neighbor is occupied by the player
                    if (!board.hasRoad(v1, neighbor) || neighbor->getStructure()->getOwner() == this)
                    {
                        v2 = neighbor;
                        break;
                    }
                }
            }
            else
            {
                throw std::invalid_argument("Invalid road placement: road already exists between these vertices.");
            }
        }
    }

    shared_ptr<Trail> trail = board.getTrail(v1, v2);
    // Place the road
    trail->setRoad(this);

    // Update the player's structures
    this->_roads[trail] = trail->getRoad();

    // Deduct resources for building a road (assuming the player has enough resources)
    this->deductResourcesForRoad(cashbox);
    cout << "Player " << this->_name << " has placed a road on a shared trail between vertices at " << places[0] << " with number " << placesNum[0] << " and " << places[1] << " with number " << placesNum[1] << endl;
}

bool Player::canPlaceRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2)
{
    // Check if the player has a settlement or road connected to these vertices
    if (this->_structures.find(v1) != this->_structures.end() || this->_structures.find(v2) != this->_structures.end())
    {
        return true;
    }

    // Check if the player has a road connected to these vertices
    for (auto &[trail, road] : this->_roads)
    {
        if (trail->getStart().lock() == v1 || trail->getEnd().lock() == v1 || trail->getStart().lock() == v2 
        || trail->getEnd().lock() == v2)
        {
            return true;
        }
    }

    return false;
}

bool Player::canPlaceCity(shared_ptr<Vertex> v)
{
    // Check if the player has a settlement on this vertex
    if (this->_structures.find(v) != this->_structures.end())
    {
        return true;
    }

    return false;
}

bool Player::canAffordSettlement()
{
    return this->_resourceCards[ResourceType::Brick].size() >= 1 && this->_resourceCards[ResourceType::Wood].size() >= 1 
    && this->_resourceCards[ResourceType::Wool].size() >= 1 && this->_resourceCards[ResourceType::Grain].size() >= 1;
}

bool Player::canAffordRoad()
{
    return this->_resourceCards[ResourceType::Brick].size() >= 1 && this->_resourceCards[ResourceType::Wood].size() >= 1;
}

void Player::deductResourcesForSettlement(Cashbox &cashbox)
{
    if (!this->_isStatringPhase)
    {
        this->removeResource(ResourceType::Brick, cashbox, 1);
        this->removeResource(ResourceType::Wood, cashbox, 1);
        this->removeResource(ResourceType::Wool, cashbox, 1);
        this->removeResource(ResourceType::Grain, cashbox, 1);
    }
}

void Player::deductResourcesForRoad(Cashbox &cashbox)
{
    if (!this->_isStatringPhase)
    {

        this->removeResource(ResourceType::Brick, cashbox, 1);
        this->removeResource(ResourceType::Wood, cashbox, 1);
    }
}

size_t Player::getResourceAmount(ResourceType resource) const
{
    if(this->_resourceCards.find(resource) == this->_resourceCards.end())
    {
        return 0;
    }

    return this->_resourceCards.at(resource).size();
}