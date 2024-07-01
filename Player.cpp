#include <iostream>
#include <vector>
#include "Cashbox.hpp"
#include "ProgressCard.hpp"
#include "Player.hpp"

using namespace std;
using namespace ariel;

Player::~Player()
{
    for (auto &[cardType, devCards] : this->_devCards)
    {
        for (auto &card : devCards)
        {   cout << "Deleting card" << endl;
            delete card;
        }
    }
}

void Player::initPlayer()
{
    // Create vector of resource cards for each resource type
    for (auto &[resource, cards] : this->_resourceCards)
    {
        this->_resourceCards[resource] = vector<ResourceCard>();
    }

    // Create vector of development cards for each card type
    for (auto &[cardType, devCards] : this->_devCards)
    {
        this->_devCards[cardType] = vector<DevCard *>();
    }
}

int Player::rollDice()
{
    // Player can only roll the dice if it is their turn or the starting phase
    if (this->_isTurn || this->_isStatringPhase)
    {   int roll = this->_die1.roll() + this->_die2.roll();
        cout << "Player " << this->_name << " has rolled a " << roll << endl;
        return roll;
    }

    else
    {
        throw invalid_argument("Not player's turn");
    }
}

void Player::endTurn()
{
    cout << "Player " << this->_name << " has ended their turn." << endl;
}

bool Player::trade(Player& pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, uint amountToGive, uint amountToGet)
{
    TradeRequest request = {resourceToGive, resourceToGet, amountToGive, amountToGet};

    // Check if the player has the required amount of resources to trade
    if (!this->canTrade(request))
    {
        cout << "Player " << this->_name << " does not have enough resources to trade" << endl;
        return false;
    }

    // If the other player accepts the trade, trade the resources
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
        cout << "Player " << this->_name << " has traded with player " << pToTrade.getName() << "The resources traded are: " << amountToGive << " " << resourceToGive << " for " << amountToGet << " " << resourceToGet << endl;
        return true;
    }
    cout << "Player " << pToTrade.getName() << " has rejected the trade request with player " << this->_name << endl;
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
        // Draw a resource card from the cashbox and add it to the player's resource cards
        try
        {
            ResourceCard card = cashbox.drawResourceCard(resource);
            this->_resourceCards[resource].push_back(card);
        }
        catch (const invalid_argument &e)
        {
            cout << resource << endl;
            cout << e.what() << endl;
        }
    }
}

void Player::removeResource(ResourceType resource, Cashbox &cashbox, size_t amount)
{
    // Check if the player has enough resources to remove
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

void Player::setTurn(bool isTurn)
{
    this->_isTurn = isTurn;
    if (isTurn)
    {
        for (auto &[cardType, devCards] : this->_devCards)
        {
            for (auto &card : devCards)
            {
                if (!card->isUsed() && !card->canUse())
                {
                    card->setCanUse(true);
                }
            }
        }
        cout << "Player " << this->_name << " has started their turn." << endl;
    }
}

void Player::printPoints()
{
    cout << "Player " << this->_name << " has " << this->_victoryPoints << " points." << endl;
}

void Player::buyDevelopmentCard(Cashbox &cashbox)
{
    // Check if the player can afford a development card
    if (this->canAffordDevCard())
    {
        // Gets the card type from the top of the deck, it's the key to the map
        CardType cardType = cashbox.peekDeck();

        DevCard *card = cashbox.drawDevCard();
        card->setOwner(this);
        this->_devCards[cardType].push_back(move(card));
        cout << "Player " << this->_name << " has bought a " << cardType << " card." << endl;
    }
    else
    {
        cout << "Player " << this->_name << " cannot afford a development card." << endl;
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

    shared_ptr<Vertex> vertex = board.getVertex(places, placesNum);
    if (vertex == nullptr)
    {
        throw invalid_argument("Invalid vertex");
    }

    // Check if the player can place a settlement here
    if (!this->canPlaceSettlement(vertex, board))
    {
        throw invalid_argument("Player cannot place a settlement here");
    }

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

            break;
        }
    }

    if (!v2)
    {
        throw std::invalid_argument("Invalid road placement: second vertex not found.");
        exit(EXIT_FAILURE);
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
    if (!_isStatringPhase)
    {
        if (!this->canAffordRoad())
        {   cout << "Player " << this->_name << " cannot afford a road." << endl;
            return false;
        }
    }

    if (!v1 || !v2)
    {
        return false;
    }

    // Check if the player has a settlement connected to these vertices
    if ((v1->isOccupied() && v1->getStructure()->getOwner() == this) ||
        (v2->isOccupied() && v2->getStructure()->getOwner() == this))
    {
        return true;
    }

    // Check if the player has a road connected to these vertices
    for (auto &[trail, road] : this->_roads)
    {
        if ((trail->getStart().lock() == v1 || trail->getEnd().lock() == v1 ||
             trail->getStart().lock() == v2 || trail->getEnd().lock() == v2) &&
            road->getOwner() == this)
        {
            return true;
        }
    }

    return false;
}

bool Player::canPlaceSettlement(shared_ptr<Vertex> v, Board &board)
{
    if (this->_structures.find(v) != this->_structures.end())
    {
        throw invalid_argument("Vertex already has a structure");
    }

    if (!_isStatringPhase)
    {
        if (this->canAffordSettlement())
        // Check if at least one road connected to the vertex has a road owned by the player
        {
            for (auto &[trail, road] : this->_roads)
            {
                auto start = trail->getStart().lock();
                auto end = trail->getEnd().lock();
                if ((start == v || end == v) && board.distanceRule(v))
                {
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

bool Player::canPlaceCity(shared_ptr<Vertex> v)
{
    if (this->canAffordCity())
    {
        if (this->_structures.find(v) != this->_structures.end())
        {
            return true;
        }
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
    if (this->_resourceCards.find(resource) == this->_resourceCards.end())
    {
        return 0;
    }

    return this->_resourceCards.at(resource).size();
}

int Player::getTotalResources()
{
    int total = 0;
    for (auto &[resource, cards] : this->_resourceCards)
    {
        total += cards.size();
    }

    return total;
}

bool Player::canAffordCity()
{
    return this->_resourceCards[ResourceType::Ore].size() >= 3 && this->_resourceCards[ResourceType::Grain].size() >= 2;
}

bool Player::canAffordDevCard()
{
    return this->_resourceCards[ResourceType::Wool].size() >= 1 && this->_resourceCards[ResourceType::Ore].size() >= 1 
    && this->_resourceCards[ResourceType::Grain].size() >= 1;
}

void Player::moveRobber(Board &board)
{
    // Check the board for the hexagon with the robber
    shared_ptr<Hexagon> hex = board.getRobberHexagon();
    if (hex == nullptr)
    {
        throw invalid_argument("Robber hexagon not found");
    }

    // Move the robber to a new hexagon with the strategy of moving to the hexagon with 2 players that are not the current player
    shared_ptr<Hexagon> newHex = nullptr;

    for (const auto &[key, hexagon] : board.getHexagonsMap())
    {
        if (!hexagon->hasRobber())
        {
            int count = 0;
            for (const auto &[vertexKey, vertex] : hexagon->getVerticesMap())
            {
                if ((vertex.lock())->getStructure() != nullptr)
                {
                    if ((vertex.lock())->getStructure()->getOwner() != this)
                    {
                        count++;
                    }
                }
            }

            if (count == 2)
            {
                newHex = hexagon;

                break;
            }
        }
    }
    if (newHex == nullptr)
    {
        throw invalid_argument("No hexagon found to move the robber to");
    }

    // Move the robber to the new hexagon
    hex->setRobber(false);
    newHex->setRobber(true);
    cout << "Robber has been moved to hexagon " << newHex->getLandType() << " on ("
         << newHex->getCenter().getX() << ", " << newHex->getCenter().getY() << ")" << endl;
}

void Player::stealResource(Player *robber, ResourceType resource)
{
    // Check if the player has the resource to steal
    if (this->_resourceCards[resource].size() == 0)
    {
        throw invalid_argument("Player does not have the resource to steal");
    }

    // Steal the resource
    ResourceCard card = this->_resourceCards[resource].back();
    this->_resourceCards[resource].pop_back();
    robber->_resourceCards[resource].push_back(card);
    cout << "Player " << this->_name << " has stolen a " << resource << " card from player " << robber->getName() << endl;
}

void Player::activateDevCard(Board &board, Cashbox &cashbox, vector<Player *> players)
{
    // Check if the player has a dev card to activate
    if (this->_devCards.size() == 0)
    {
        throw invalid_argument("Player does not have a dev card to activate");
    }

    // Randomly select a dev card to activate
    int index = rand() % this->_devCards.size();
    auto it = this->_devCards.begin();
    advance(it, index);
    DevCard *card = it->second.back();
    devCardAction action = card->activate();

    switch (action)
    {
    case devCardAction::GET_2_FREE_RESOURCES:
    {
        // Get 2 free resources
        vector<ResourceType> resources = {ResourceType::Brick, ResourceType::Wood, ResourceType::Wool, ResourceType::Grain, ResourceType::Ore};
        for (int i = 0; i < 2; i++)
        {
            int index = rand() % resources.size();
            this->addResource(resources[index], cashbox, 1);
        }
        break;
    }

    case devCardAction::GET_MONOPOLY_RESOURCES:
    {
        // Get all resources of a single type from all players
        vector<ResourceType> resources = {ResourceType::Brick, ResourceType::Wood, ResourceType::Wool, ResourceType::Grain, ResourceType::Ore};
        int index = rand() % resources.size();
        ResourceType resource = resources[index];
        for (auto &player : players)
        {
            if (player != this)
            {
                size_t amount = player->getResourceAmount(resource);
                for (size_t i = 0; i < amount; i++)
                {
                    ResourceCard card = player->_resourceCards[resource].back();
                    player->_resourceCards[resource].pop_back();
                    this->_resourceCards[resource].push_back(card);
                }
            }
        }
        break;
    }

    case devCardAction::ACT_AS_ROBBER:
    {
        // Move the robber
        this->moveRobber(board);
        break;
    }

    case devCardAction::GET_VICTORY_POINT:
    {
        // Get a victory point
        this->addVictoryPoints(1);
        break;
    }

    case devCardAction::GET_2_FREE_ROADS:
    {
        // Set the isStartingPhase to true so the player can build 2 free roads
        this->setStartingPhase(true);
        // Select random owend vertices/roads to build the roads
        vector<shared_ptr<Vertex>> vertices;
        for (auto &[vertex, structure] : this->_structures)
        {
            vertices.push_back(vertex);
        }

        for (int i = 0; i < 2; i++)
        {
            int index = rand() % vertices.size();
            shared_ptr<Vertex> v1 = vertices[index];
            vertices.erase(vertices.begin() + index);

            vector<shared_ptr<Vertex>> neighbors = board.getNeighborVertices(v1);
            index = rand() % neighbors.size();
            shared_ptr<Vertex> v2 = neighbors[index];

            // Place the road
            shared_ptr<Trail> trail = board.getTrail(v1, v2);
            trail->setRoad(this);
            this->_roads[trail] = trail->getRoad();
        }
        // Set the isStartingPhase to false
        this->setStartingPhase(false);
        break;
    }

    default:
    {
        throw invalid_argument("Invalid dev card action");
    }
    }
}

void Player::placeCity(vector<LandType> places, vector<int> placesNum, Board &board, Cashbox &cashbox)
{

    if (places.size() != 2 || placesNum.size() != 2)
    {
        throw invalid_argument("Invalid number of arguments");
    }

    shared_ptr<Vertex> vertex = board.getVertex(places, placesNum);
    if (vertex == nullptr)
    {
        throw invalid_argument("Invalid vertex");
    }

    if (!this->canPlaceCity(vertex))
    {
        throw invalid_argument("Player cannot place a city here");
    }

    // Build a city
    vertex->buildCity(this);
    this->_structures[vertex] = vertex->getStructure();
    // Add victory points
    this->addVictoryPoints(1);
    // Deduct resources
    this->removeResource(ResourceType::Ore, cashbox, 3);
    this->removeResource(ResourceType::Grain, cashbox, 2);
    cout << "Player " << this->_name << " has placed a city on a shared vertex at " << places[0] << " with number " << placesNum[0] << " and " << places[1] << " with number " << placesNum[1] << endl;
}

void Player::setLargestArmyHolder()
{
    this->_isLargestArmyHolder = true;
    // Add 2 victory points
    this->addVictoryPoints(2);

    cout << "Player " << this->_name << " has the largest army." << endl;
}

void Player::setLongestRoadHolder()
{
    this->_isLongestRoadHolder = true;
    // Add 2 victory points
    this->addVictoryPoints(2);

    cout << "Player " << this->_name << " has the longest road." << endl;
}

void Player::takeLargestArmyCard()
{
    this->_isLargestArmyHolder = false;
    // Remove 2 victory points
    this->removeVictoryPoints(2);

    cout << "Player " << this->_name << " has lost the largest army." << endl;
}

void Player::takeLongestRoadCard()
{
    this->_isLongestRoadHolder = false;
    // Remove 2 victory points
    this->removeVictoryPoints(2);

    cout << "Player " << this->_name << " has lost the longest road." << endl;
}

map<shared_ptr<Vertex>, vector<shared_ptr<Vertex>>> Player::getRoadNetwork() const
{
    map<shared_ptr<Vertex>, vector<shared_ptr<Vertex>>> roadNetwork;

    for (const auto &roadPair : _roads)
    {
        auto trail = roadPair.first;
        auto start = trail->getStart().lock();
        auto end = trail->getEnd().lock();

        if (start && end)
        {
            roadNetwork[start].push_back(end);
            roadNetwork[end].push_back(start);
        }
    }

    return roadNetwork;
}

size_t Player::dfs(shared_ptr<Vertex> vertex, shared_ptr<Vertex> parent, map<shared_ptr<Vertex>, vector<shared_ptr<Vertex>>> &roadNetwork, map<shared_ptr<Vertex>, bool> &visited)
{
    visited[vertex] = true;
    size_t maxLength = 0;

    for (const auto &neighbor : roadNetwork[vertex])
    {
        if (neighbor != parent && !visited[neighbor])
        {
            maxLength = max(maxLength, dfs(neighbor, vertex, roadNetwork, visited) + 1);
        }
    }

    visited[vertex] = false;
    return maxLength;
}


size_t Player::countSequenceRoads()
{
    auto roadNetwork = getRoadNetwork();
    map<shared_ptr<Vertex>, bool> visited;
    size_t longestRoad = 0;

    for (const auto &roadPair : roadNetwork)
    {
        auto vertex = roadPair.first;
        longestRoad = max(longestRoad, dfs(vertex, nullptr, roadNetwork, visited));
    }

    return longestRoad;
}

size_t Player::countKnightCards()
{
    if (this->_devCards.find(CardType::KNIGHT) == this->_devCards.end())
    {
        return 0;
    }
    else {
        return this->_devCards[CardType::KNIGHT].size();
    }
}
