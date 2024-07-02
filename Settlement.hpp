// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _SETTLEMENT_HPP_
#define _SETTLEMENT_HPP_

#include "Structure.hpp"


namespace ariel 
{
    
    class Settlement: public Structure 
    {
        private:
            bool _isCity;
            
        public:
            Settlement(Player* owner): Structure(owner), _isCity(false) {}
            Settlement(Player* owner, bool isCity): Structure(owner), _isCity(isCity) {}
            ~Settlement();
            
            void yieldResources(ResourceType resource, Cashbox &cashbox) override;
            
            

    };
}



#endif