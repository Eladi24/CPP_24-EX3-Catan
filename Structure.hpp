// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _STRUCTURE_HPP_
#define _STRUCTURE_HPP_

#include <iostream>
#include <vector>
#include "Types.hpp"
#include "Player.hpp"
#include "Cashbox.hpp"

using namespace std;

namespace ariel
{
    class Player;
    class Cashbox;

    class Structure
    {
        protected:
            // The owner of the structure
            Player* _owner;
            
        public:
            // Constructor
            Structure(Player* owner): _owner(owner) {}
            // Destructor
            virtual ~Structure() = default;
            
            // Get the owner of the structure
            Player* getOwner() { return this->_owner;}
            // Yield resources
            virtual void yieldResources(ResourceType resource, Cashbox &cashbox) = 0;
            

    };

}



#endif
