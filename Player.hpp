// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include "Die.hpp"
#include "Types.hpp"
#include "DevCard.hpp"
#include "Structure.hpp"
#include "Vertex.hpp"
#include "Trail.hpp"
#include "Road.hpp"
#include "Cashbox.hpp"
#include "Board.hpp"

namespace ariel
{
    class DevCard;
    class Structure;
    class Board;
    class Cashbox;
    

    class Player
    {
    private:
        const string _name;
        map<ResourceType, vector<ResourceCard>> _resourceCards;
        map<shared_ptr<Vertex>, Structure*> _structures;
        map <shared_ptr<Trail>, Road*> _roads;
        int _victoryPoints;
        map<CardType, vector<DevCard*>> _devCards;
        Die _die1;
        Die _die2;
        sf::Color _color;
        bool _isTurn;
        bool _isStatringPhase;
        bool _isLargestArmyHolder;
        bool _isLongestRoadHolder;
        void initPlayer();
        bool canTrade(TradeRequest tradeRequest);
        /*
        * @brief
        * This function returns the road network of the player.
        * It iterates over the vertices of the player and creates a map of the road network.
        * @return map<shared_ptr<Vertex>, vector<shared_ptr<Vertex>>> The road network of the player.
        */
        map<shared_ptr<Vertex>, vector<shared_ptr<Vertex>>> getRoadNetwork() const;

        /*
        * @brief
        * This function is DFS algorithm that calculates the size of the road network of the player.
        * @param vertex The vertex to start the DFS from.
        * @param parent The parent of the vertex.
        * @param roadNetwork The road network of the player.
        * @param visited A map of the visited vertices.
        * @return size_t The size of the road network.
        */
        size_t dfs(shared_ptr<Vertex> vertex, shared_ptr<Vertex> parent, map<shared_ptr<Vertex>, vector<shared_ptr<Vertex>>> &roadNetwork, map<shared_ptr<Vertex>, bool> &visited);
        
        
        
    public:
        Player(const string name, sf::Color color): _name(name), _victoryPoints(0), _color(color), _isTurn(false), _isStatringPhase(true), _isLargestArmyHolder(false), _isLongestRoadHolder(false) {
            initPlayer();
        }
        
        ~Player();
        /*
        * @brief
        * This function places a settlement on the board.
        * @param places A vector of land types to place the settlement on.
        * @param placesNum A vector of the number of vertices that should be on each land type.
        * @param board The board of the game.
        * @param cashbox The cashbox of the game.
        */
        void placeSettelemnt(vector<LandType> places, vector<int> placesNum, Board& board, Cashbox& cashbox);
        /*
        * @brief
        * This function places a road on the board.
        * @param places A vector of land types to place the road on.
        * @param placesNum A vector of the number of trails that should be on each land type.
        * @param board The board of the game.
        * @param cashbox The cashbox of the game.
        */
        void placeRoad(vector<LandType> places, vector<int> placesNum, Board& board, Cashbox& cashbox);

        /*
        * @brief
        * This function places a city on the board.
        * A city can only be placed on a settlement.
        * @param places A vector of land types to place the city on.
        * @param placesNum A vector of the number of vertices that should be on each land type.
        * @param board The board of the game.
        * @param cashbox The cashbox of the game.
        * @return void
        */
        void placeCity(vector<LandType> places, vector<int> placesNum, Board& board, Cashbox& cashbox);

        int rollDice();

        /*
        * @brief
        * This function ends the turn of the player.
        * It sets the isTurn field to false.
        * @return void
        */
        void endTurn();

        /*
        * @brief
        * This function trades resources with another player.
        * It checks if the trade is possible on the requester's side and creates a trade request.
        * @param pToTrade The player to trade with.
        * @param resourceToGive The resource to give.
        * @param resourceToGet The resource to get.
        * @param amountToGive The amount of the resource to give.
        * @param amountToGet The amount of the resource to get.
        * @return bool True if the other player accepted the trade, false otherwise.
        */
        bool trade(Player& pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, uint amountToGive, uint amountToGet);

        /*
        * @brief
        * This function reviews a trade request.
        * It checks if the trade is possible on the requested's side and accepts or declines the trade.
        * The strategy of the player is to accept the trade if the amount of resources that he has to give is greater than 1
        * @param tradeRequest The trade request to review.
        * @return bool True if the trade was accepted, false otherwise.
        */
        bool reviewTradeRequest(TradeRequest tradeRequest);

        /*
        * @brief
        * This function buys a development card.
        * It checks if the player can afford the development card and deducts the resources from the player's resources.
        * @param cashbox The cashbox of the game.
        * @return void
        */
        void buyDevelopmentCard(Cashbox& cashbox);

        void printPoints();

        string getName() const { return this->_name; }

        int getVictoryPoints() const { return this->_victoryPoints; }

        void addVictoryPoints(int points);

        void removeVictoryPoints(int points);

        void addResource(ResourceType resource, Cashbox& cashbox, size_t amount);

        void removeResource(ResourceType resource, Cashbox& cashbox, size_t amount);

        size_t getResourceAmount(ResourceType resource) const;

        void setTurn(bool isTurn);

        bool canPlaceSettlement(shared_ptr<Vertex> v, Board& board);
        
        bool canPlaceRoad(shared_ptr<Vertex> v1 , shared_ptr<Vertex> v2);

        bool canPlaceCity(shared_ptr<Vertex> v);

        bool canAffordSettlement();

        bool canAffordRoad();

        bool canAffordCity();
        
        bool canAffordDevCard();

        void deductResourcesForSettlement(Cashbox& cashbox);

        void deductResourcesForRoad(Cashbox& cashbox);

        void setStartingPhase(bool isStartingPhase) { this->_isStatringPhase = isStartingPhase; }

        void addStructure(Structure* structure, shared_ptr<Vertex> v) { this->_structures[v] = structure; }

        void addRoad(Road* road, shared_ptr<Trail> t) { this->_roads[t] = road; }

        int getTotalResources();

        bool getIsTurn() const { return this->_isTurn; }


        // Methods for moving the robber
        void moveRobber(Board& board);

        void stealResource(Player* p, ResourceType type);

        void activateDevCard(Board& board, Cashbox& cashbox, vector<Player*> players);

        void setLargestArmyHolder();

        void setLongestRoadHolder();

        bool getIsLargestArmyHolder() const { return this->_isLargestArmyHolder; }

        bool getIsLongestRoadHolder() const { return this->_isLongestRoadHolder; }

        void takeLargestArmyCard();

        void takeLongestRoadCard(); 

        sf::Color getColor() const { return this->_color; }

        size_t countSequenceRoads();

        size_t countKnightCards();

    };
} // namespace ariel



#endif