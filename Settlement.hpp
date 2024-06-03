#ifndef _SETTLEMENT_HPP_
#define _SETTLEMENT_HPP_

#include "Point.hpp"
#include "Player.hpp"
namespace ariel 
{
    class Settlement
    {
        private:
            Point _location;
            Player _owner;
            bool _isCity;
        public:
            Settlement(Point location, Player owner);
            Settlement(Point location, Player owner, bool isCity);
            ~Settlement();
            Point getLocation();
            Player getOwner();
            void setOwner(Player owner);
            void setCity();
            bool isCity();
            void yieldResources();
            

    };
}



#endif