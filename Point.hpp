#ifndef _POINT_HPP_
#define _POINT_HPP_

#include "Player.hpp"


namespace ariel
{
    class Point
    {
    private:
        int _x;
        int _y;
        
        
    public:
        Point(int x, int y);
        ~Point();
        int getX();
        int getY();

    };
}

#endif