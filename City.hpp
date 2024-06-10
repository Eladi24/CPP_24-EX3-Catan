#ifndef _CITY_HPP_
#define _CITY_HPP_

#include "Structure.hpp"

using namespace std;

namespace ariel
{
    class City: public Structure
    {
        public:
            City(Player owner);
            ~City();
            void yieldResources();
    };
}






#endif