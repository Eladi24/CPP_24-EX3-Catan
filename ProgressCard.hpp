#ifndef _PROGRESSCARD_HPP_
#define _PROGRESSCARD_HPP_

#include "DevCard.hpp"


namespace ariel
{
    class ProgressCard: public DevCard
    {
        private:
            // The type of the progress card
            SubCardType _subType;

        public:
            ProgressCard(CardType type, int cost, SubCardType subType): DevCard(type, cost), _subType(subType) {}
            ~ProgressCard();
            SubCardType getSubType() { return _subType; }
            void activate() override; 
    };

    class YearOfPlenty: public DevCard
    {
        public:
            YearOfPlenty(CardType type, int cost): DevCard(type, cost) {}
            ~YearOfPlenty();
            void activate(ResourceType resource1, ResourceType resource2, Cashbox& cashbox);
    };

    class RoadBuilding: public DevCard
    {
        public:
            RoadBuilding(CardType type, int cost): DevCard(type, cost) {}
            ~RoadBuilding();
            void activate(vector<LandType> places, vector<int> placesNum, Board& board, Cashbox& cashbox);
    };

    class Monopoly: public DevCard
    {
        public:
            Monopoly(CardType type, int cost): DevCard(type, cost) {}
            ~Monopoly();
            void activate(ResourceType resourceToGet, vector<Player*> players);
    };
}



#endif