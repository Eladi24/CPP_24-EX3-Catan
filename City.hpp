// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _CITY_HPP_
#define _CITY_HPP_

#include "Structure.hpp"


using namespace std;

namespace ariel
{
    class City: public Structure
    {
        private:

                const int _productionRate = 2;
        public:
            City(Player* owner): Structure(owner) {}
            ~City();
            void yieldResources(ResourceType resource, Cashbox &cashbox) override;
            
    };
}






#endif