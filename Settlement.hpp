#ifndef _SETTLEMENT_HPP_
#define _SETTLEMENT_HPP_

#include "Point.hpp"
#include "Player.hpp"
#include "Structure.hpp"

namespace ariel 
{
    class Settlement: public Structure 
    {
        private:
            bool _isCity;
            
        public:
            Settlement(Player owner);
            Settlement(Player owner, bool isCity);
            ~Settlement();
            
            void yieldResources();
            

    };
}



#endif