#ifndef _ROAD_HPP_
#define _ROAD_HPP_
#include "Types.hpp"

namespace ariel
{
    class Road
    {
        class Player;

        private:
            Player* _owner;
            
        public:
            Road(Player* owner): _owner(owner) {}
            ~Road() {}
            Player* getOwner() const { return this->_owner; }
            
    };
}








#endif