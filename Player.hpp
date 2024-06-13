#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Die.hpp"
#include "Vertex.hpp"
#include "Trail.hpp"
#include "Hexagon.hpp"
#include "Road.hpp"
#include "DevCard.hpp"

namespace ariel
{
    class Board;
    typedef struct TradeRequest
        {
            ResourceType resourceToGive;
            ResourceType resourceToGet;
            int amountToGive;
            int amountToGet;
        } TradeRequest;
   
    class Player
    {
    private:
        const string _name;
        map<ResourceType, uint> _resources;
        map<Vertex*, Structure*> _structures;
        
        map <Trail, Road> _roads;
        int _victoryPoints;
        map<DevCard*, uint> _devCards;
        Die _die1;
        Die _die2;
        bool _isTurn;
        
        
        
    public:
        Player(const string name): _name(name), _victoryPoints(0), _isTurn(false) {}
        ~Player();
        void placeSettelemnt(vector<string> places, vector<int> placesNum, Board board);
        void placeRoad(vector<string> places, vector<int> placesNum, Board board);
        void rollDice();
        void endTurn();
        bool trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, int amountToGive, int amountToGet);
        bool reviewTradeRequest(TradeRequest tradeRequest);
        void buyDevelopmentCard();
        void printPoints();
        string getName() const { return this->_name; }
        void addResource(ResourceType resource, int amount);
        void removeResource(ResourceType resource, int amount);
        uint getResourceAmount(ResourceType resource) const { return this->_resources.at(resource); }

    };
} // namespace ariel



#endif