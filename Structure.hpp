#ifndef _STRUCTURE_HPP_
#define _STRUCTURE_HPP_

#include <iostream>
#include <vector>
#include "Types.hpp"
#include "Cashbox.hpp"
#include "Player.hpp"

using namespace std;

namespace ariel
{
    class Player;

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
            virtual void yieldResources(ResourceType resource) = 0;
            

    };

}



#endif
