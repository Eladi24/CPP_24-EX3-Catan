#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <map>
#include "Die.hpp"
#include "Settlement.hpp"
#include "Road.hpp"

namespace ariel
{
    class Player
    {
    private:
        const string name;
        map<ResourceType, int> resources;
        vector<Settlement> settlements;
        vector<Road> roads;
        int points;
        vector<DevCard> devCards;
        Die _die1;
        Die _die2;
        
    public:
        Player(const string name);
        ~Player();
        void placeSettelemnt(vector<string> places, vector<int> placesNum, Board board);
        void placeRoad(vector<string> places, vector<int> placesNum, Board board);
        void rollDice();
        void endTurn();
        void trade(Player pToTrade, string resourceToGive, string resourceToGet, int amountToGive, int amountToGet);
        void buyDevelopmentCard();
        void printPoints();
        string getName();
    };
} // namespace ariel



#endif