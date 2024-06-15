#include <iostream>
#include <vector>
#include "Cashbox.hpp"
#include "Player.hpp"



using namespace std;
using namespace ariel;

Player::~Player() {
    
}

int Player::rollDice()
{
    if (this->_isTurn || this->_isStatringPhase)
    {
        return this->_die1.roll() + this->_die2.roll();
    }
    else
    {
        throw new invalid_argument("Not player's turn");
    }
}

void Player::endTurn()
{
    this->_isTurn = false;
}

bool Player::trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, int amountToGive, int amountToGet) {
    TradeRequest request = {resourceToGive, resourceToGet, amountToGive, amountToGet};
    if (pToTrade.reviewTradeRequest(request) == true)
    {
        this->_resources[resourceToGive] -= amountToGive;
        this->_resources[resourceToGet] += amountToGet;
        pToTrade._resources[resourceToGive] += amountToGive;
        pToTrade._resources[resourceToGet] -= amountToGet;
        return true;
    }
    return false;
}

bool Player::reviewTradeRequest(TradeRequest tradeRequest) {
    if (tradeRequest.amountToGive > _resources[tradeRequest.resourceToGive]) {
        return false;
    }
    if (tradeRequest.amountToGet > _resources[tradeRequest.resourceToGet]) {
        return false;
    }
    
    return true;
}

void Player::addResource(ResourceType resource, int amount)
{
    this->_resources[resource] += amount;
}

void Player::removeResource(ResourceType resource, int amount)
{
    if (this->_resources[resource] == 0 || this->_resources[resource] < amount)
    {
        throw new invalid_argument("Player does not have enough resources to remove");
    }
    this->_resources[resource] -= amount;
}


void Player::printPoints()
{
    cout << "Player " << this->_name << " has " << this->_victoryPoints << " points." << endl;
}

void Player::buyDevelopmentCard(Cashbox& cashbox)
{
    if (cashbox.canAffordDevCard(*this))
    {
        CardType cardType = cashbox.peekDeck();

        shared_ptr<DevCard> card = cashbox.drawDevCard();
        card->setOwner(this);
        if (this->_devCards.find(card) == this->_devCards.end())
        {
            this->_devCards[card] = 1;
            card->activate();
        }

    }
}

void Player::addVictoryPoints(int points)
{
    // The maximum number of victory points can be gained in a single turn is 13
    if (points > 13)
    {
        throw new invalid_argument("Player cannot gain more than 13 points in a single turn");
    }

    if (points < 0)
    {
        throw new invalid_argument("Wrong method to remove points");
    }

    this->_victoryPoints += points;
    cout << "Player " << this->_name << " has gained " << points << " points." << endl;
}


void Player::removeVictoryPoints(int points)
{
    if (points > this->_victoryPoints)
    {
        throw new invalid_argument("Player cannot lose more points than they have");
    }

    if (points < 0)
    {
        throw new invalid_argument("Wrong method to add points");
    }

    this->_victoryPoints -= points;
    cout << "Player " << this->_name << " has lost " << points << " points." << endl;
}

void Player::placeSettelemnt(vector<LandType> places, vector<int> placesNum, Board& board)
{
    if (places.size() != 2 || placesNum.size() != 2)
    {
        throw new invalid_argument("Invalid number of arguments");
    }

    if (!this->canAffordSettlement() && !this->_isStatringPhase)
    {
        throw new invalid_argument("Player cannot afford to build a settlement");
    }

    shared_ptr<Vertex> vertex = board.getVertex(places, placesNum);
    if (vertex == nullptr)
    {
        throw new invalid_argument("Invalid vertex");
    }

    if (this->_structures.find(vertex) != this->_structures.end())
    {
        throw new invalid_argument("Vertex already has a structure");
    }

    vertex->buildSettlement(this);
    this->_structures[vertex] = vertex->getStructure();
    // Add victory points
    this->addVictoryPoints(1);
    // Deduct resources
    this->deductResourcesForSettlement();
    cout << "Player " << this->_name << " has placed a settlement on a shared vertex at " << places[0] << " with number " << placesNum[0] << 
    " and "<<places[1] << " with number " << placesNum[1] << endl;
}


void Player::placeRoad(vector<LandType> places, vector<int> placesNum, Board& board) {
        if (places.size() != 2 || placesNum.size() != 2) {
            throw std::invalid_argument("Must specify exactly two places and their numbers.");
        }

        // Get the two vertices where the road is supposed to be placed
        shared_ptr<Vertex> v1 = board.getVertex(places, placesNum);

        if (!v1) {
            throw std::invalid_argument("Invalid vertex locations.");
        }

        // Now we need to find a second set of places and placesNum to form the other end of the road
        // Assume the player provides the two sets correctly for the road, let's fetch the second vertex

        // Find potential vertices that are neighbors of v1
        auto neighbors = board.getNeighborVertices(v1);

        shared_ptr<Vertex> v2 = nullptr;
        for (auto& neighbor : neighbors) {
            if (board.vertexMatches(neighbor, places, placesNum)) {
                v2 = neighbor;
                break;
            }
        }

        if (!v2) {
            throw std::invalid_argument("Invalid road placement: second vertex not found.");
        }

        // Check if the player can place the road here (i.e., the player has a settlement or road connected to these vertices)
        if (!this->canPlaceRoad(v1, v2)) {
            throw std::invalid_argument("Invalid road placement: player does not have a settlement or road connected to these vertices.");
        }

        // Check if there is already a road in this place
        if (board.hasRoad(v1, v2)) {
            throw std::invalid_argument("Invalid road placement: a road already exists between these vertices.");
        }
        shared_ptr<Trail> trail = board.getTrail(v1, v2);
        // Place the road
        trail->setRoad(this);

        // Update the player's structures
        this->_roads[trail] = trail->getRoad();

        // Deduct resources for building a road (assuming the player has enough resources)
        this->deductResourcesForRoad();
    }

bool Player::canPlaceRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) {
    // Check if the player has a settlement or road connected to these vertices
    if (this->_structures.find(v1) != this->_structures.end() || this->_structures.find(v2) != this->_structures.end()) {
        return true;
    }

    // Check if the player has a road connected to these vertices
    for (auto& [trail, road] : this->_roads) {
        if (trail->getStart() == v1 || trail->getEnd() == v1 || trail->getStart() == v2 || trail->getEnd() == v2) {
            return true;
        }
    }

    return false;
}

bool Player::canPlaceCity(shared_ptr<Vertex> v) {
    // Check if the player has a settlement on this vertex
    if (this->_structures.find(v) != this->_structures.end()) {
        return true;
    }

    return false;
}

bool Player::canAffordSettlement() {
    return this->_resources[ResourceType::Brick] >= 1 && this->_resources[ResourceType::Wood] >= 1 
    && this->_resources[ResourceType::Wool] >= 1 && this->_resources[ResourceType::Grain] >= 1;
}

bool Player::canAffordRoad() {
    return this->_resources[ResourceType::Brick] >= 1 && this->_resources[ResourceType::Wood] >= 1;
}


void Player::deductResourcesForSettlement() {
    if (!this->_isStatringPhase) {
        this->removeResource(ResourceType::Brick, 1);
        this->removeResource(ResourceType::Wood, 1);
        this->removeResource(ResourceType::Wool, 1);
        this->removeResource(ResourceType::Grain, 1);
    }
}

void Player::deductResourcesForRoad() {
    if(this->_isStatringPhase) {

        this->removeResource(ResourceType::Brick, 1);
        this->removeResource(ResourceType::Wood, 1);
    }
}

