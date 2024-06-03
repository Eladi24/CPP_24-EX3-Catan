#ifndef _TRAIL_HPP_
#define _TRAIL_HPP_

#include "Point.hpp"
#include "Player.hpp"

namespace ariel
{
    class Trail
    {
    private:
        Point _start;
        Point _end;
        bool _isRoad;

    public:
        Trail(Point start, Point end);
        ~Trail();
        void setRoad();
        bool isRoad();
        Point getStart();
        Point getEnd();
    };
}






#endif