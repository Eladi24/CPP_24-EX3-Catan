#ifndef _DEVCARD_HPP_
#define _DEVCARD_HPP_

#include <iostream>
#include <vector>

namespace ariel
{
    enum CardType
    {
        KNIGHT,
        VICTORY_POINT,
        ROAD_BUILDING,
        YEAR_OF_PLENTY,
        MONOPOLY,
        LARGEST_ARMY,
        LONGEST_ROAD
    };

    class DevCard
    {
    private:
        CardType type;
        string name;
        
    public:
        DevCard(CardType type, string name, string description, int value);
        ~DevCard();
        void activate();
        string getType();
    };
} // namespace ariel

#endif