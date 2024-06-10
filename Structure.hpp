#ifndef _STRUCTURE_HPP_
#define _STRUCTURE_HPP_

#include <iostream>
#include <vector>
#include "Vertex.hpp"
using namespace std;

namespace ariel
{
    class Structure
    {
        protected:
            // The owner of the structure
            Player _owner;
            
        public:
            // Constructor
            Structure(Player owner);
            // Destructor
            ~Structure();
            
            // Get the owner of the structure
            Player getOwner();
            // Yield resources
            virtual void yieldResources() = 0;
            

    };

}



#endif