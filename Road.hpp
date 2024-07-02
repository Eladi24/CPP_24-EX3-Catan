// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _ROAD_HPP_
#define _ROAD_HPP_

#include "Types.hpp"


namespace ariel
{
    class Player;

    class Road
    {
        
        private:
            Player* _owner;
            
        public:
            Road(Player* owner): _owner(owner) {}
            ~Road() {}
            Player* getOwner() const { return this->_owner; }
            void setOwner(Player* owner) { this->_owner = owner; }
            
    };
}








#endif