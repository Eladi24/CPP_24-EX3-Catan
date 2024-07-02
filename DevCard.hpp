// ID: 205739907
// Email: eladima66@gmail.com

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

    protected:
        bool _used;
        bool _canUse;
        Player* _owner;
        devCardAction _action;
    public:
        DevCard(CardType type): _type(type), _used(false), _canUse(false), _owner(nullptr) {}

        virtual ~DevCard() = default;

        virtual devCardAction activate() = 0;


        bool isUsed() { return _used; }

        void setUsed(bool used) { this->_used = used; }

        bool canUse() { return _canUse; }

        void setCanUse(bool canUse) { this->_canUse = canUse; }

        CardType getCardType() { return _type ;}

        Player* getOwner() { return _owner; }

        void setOwner(Player* owner) { this->_owner = owner; }
        
        void setAction(devCardAction action) { this->_action = action; }
        
    };
} // namespace ariel

#endif