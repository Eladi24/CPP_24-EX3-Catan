#ifndef _DEVCARD_HPP_
#define _DEVCARD_HPP_

#include <string>
using namespace std;

namespace ariel
{
    enum CardType
    {
        KNIGHT,
        PROGRESS,
        VICTORY_POINT
    };

    enum SubCardType
    {
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
        string description;
        int value;
        bool used;
        
    public:
        DevCard(CardType type, string description, int value): type(type), description(description), value(value), used(false) {}
        virtual ~DevCard() = default;
        virtual void activate() =0;
        bool isUsed() { return used; }
        void setUsed(bool used) { this->used = used; }
        CardType getCardType() { return type ;}
    };
} // namespace ariel

#endif