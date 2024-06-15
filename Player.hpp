#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include "Die.hpp"
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
        map<ResourceType, uint> _resources;
        map<shared_ptr<Vertex>, Structure*> _structures;
        
        map <shared_ptr<Trail>, Road*> _roads;
        int _victoryPoints;
        map<shared_ptr<DevCard>, uint> _devCards;
        Die _die1;
        Die _die2;
        bool _isTurn;
        bool _isStatringPhase;
        
        
        
    public:
        Player(const string name): _name(name), _victoryPoints(0), _isTurn(false), _isStatringPhase(true) {}
        ~Player();
        void placeSettelemnt(vector<LandType> places, vector<int> placesNum, Board& board);
        void placeRoad(vector<LandType> places, vector<int> placesNum, Board& board);
        int rollDice();
        void endTurn();
        bool trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, int amountToGive, int amountToGet);
        bool reviewTradeRequest(TradeRequest tradeRequest);
        void buyDevelopmentCard(Cashbox& cashbox);
        void printPoints();
        string getName() const { return this->_name; }
        int getVictoryPoints() const { return this->_victoryPoints; }
        void addVictoryPoints(int points);
        void removeVictoryPoints(int points);
        void addResource(ResourceType resource, int amount);
        void removeResource(ResourceType resource, int amount);
        uint getResourceAmount(ResourceType resource) const { return this->_resources.at(resource); }
        void setTurn(bool isTurn) { this->_isTurn = isTurn; }
        bool canPlaceSettlement(shared_ptr<Vertex> v);
        bool canPlaceRoad(shared_ptr<Vertex> v1 , shared_ptr<Vertex> v2);
        bool canPlaceCity(shared_ptr<Vertex> v);
        bool canAffordSettlement();
        bool canAffordRoad();
        bool canAffordCity();
        void deductResourcesForSettlement();
        void deductResourcesForRoad();
        void setStartingPhase(bool isStartingPhase) { this->_isStatringPhase = isStartingPhase; }

    };
} // namespace ariel



#endif