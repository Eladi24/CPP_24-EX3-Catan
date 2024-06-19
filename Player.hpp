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
        bool _isTurn;
        bool _isStatringPhase;
        void initPlayer();
        bool canTrade(TradeRequest tradeRequest);
        
        
        
        
    public:
        Player(const string name): _name(name), _victoryPoints(0), _isTurn(false), _isStatringPhase(true) {
            initPlayer();
        }
        
        ~Player();
        void placeSettelemnt(vector<LandType> places, vector<int> placesNum, Board& board, Cashbox& cashbox);
        void placeRoad(vector<LandType> places, vector<int> placesNum, Board& board, Cashbox& cashbox);
        int rollDice();
        void endTurn();
        bool trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, uint amountToGive, uint amountToGet);
        bool reviewTradeRequest(TradeRequest tradeRequest);
        void buyDevelopmentCard(Cashbox& cashbox);
        void printPoints();
        string getName() const { return this->_name; }
        int getVictoryPoints() const { return this->_victoryPoints; }
        void addVictoryPoints(int points);
        void removeVictoryPoints(int points);
        void addResource(ResourceType resource, Cashbox& cashbox, size_t amount);
        void removeResource(ResourceType resource, Cashbox& cashbox, size_t amount);
        size_t getResourceAmount(ResourceType resource) const;
        void setTurn(bool isTurn) { this->_isTurn = isTurn; }
        bool canPlaceSettlement(shared_ptr<Vertex> v);
        bool canPlaceRoad(shared_ptr<Vertex> v1 , shared_ptr<Vertex> v2);
        bool canPlaceCity(shared_ptr<Vertex> v);
        bool canAffordSettlement();
        bool canAffordRoad();
        bool canAffordCity();
        void deductResourcesForSettlement(Cashbox& cashbox);
        void deductResourcesForRoad(Cashbox& cashbox);
        void setStartingPhase(bool isStartingPhase) { this->_isStatringPhase = isStartingPhase; }
        void addStructure(Structure* structure, shared_ptr<Vertex> v) { this->_structures[v] = structure; }
        void addRoad(Road* road, shared_ptr<Trail> t) { this->_roads[t] = road; }

    };
} // namespace ariel



#endif