#ifndef _DEVCARD_HPP_
#define _DEVCARD_HPP_

#include "Player.hpp"
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
        CardType _type;
        int _value;
        bool _used;
        
    protected:
        Player* _owner;
    public:
        DevCard(CardType type, int value): _type(type), _value(value), _used(false), _owner(nullptr) {}
        virtual ~DevCard() = default;
        virtual void activate() =0;
        bool isUsed() { return _used; }
        void setUsed(bool used) { this->_used = used; }
        CardType getCardType() { return _type ;}
        int getValue() { return _value; }
        Player* getOwner() { return _owner; }
        void setOwner(Player* owner) { this->_owner = owner; }
        
    };
} // namespace ariel

#endif