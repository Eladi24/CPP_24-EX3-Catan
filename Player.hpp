#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <map>
#include "Die.hpp"
#include "Settlement.hpp"
#include "Road.hpp"
#include "DevCard.hpp"
#include "Land.hpp"
#include "Board.hpp"
#include "Vertex.hpp"
#include "Structure.hpp"

namespace ariel
{
    typedef struct TradeRequest
        {
            const Player requester;
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
        map<Vertex, Structure> _structures;
        vector<Settlement> _settlements;
        vector<Road> _roads;
        int _victoryPoints;
        vector<DevCard> _devCards;
        Die _die1;
        Die _die2;
        bool _isTurn;
        
        
        
    public:
        Player(const string name);
        ~Player();
        void placeSettelemnt(vector<string> places, vector<int> placesNum, Board board);
        void placeRoad(vector<string> places, vector<int> placesNum, Board board);
        void rollDice();
        void endTurn();
        bool trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, int amountToGive, int amountToGet);
        bool reviewTradeRequest(TradeRequest tradeRequest);
        void buyDevelopmentCard();
        void printPoints();
        string getName();
        void addResource(ResourceType resource, int amount);
        void removeResource(ResourceType resource, int amount);

    };
} // namespace ariel



#endif