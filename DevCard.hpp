#ifndef _DEVCARD_HPP_
#define _DEVCARD_HPP_

#include <string>
#include "Types.hpp"
#include "Player.hpp"
using namespace std;

namespace ariel
{
    class Player;

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