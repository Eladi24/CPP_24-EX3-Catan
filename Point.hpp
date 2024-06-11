#ifndef _POINT_HPP_
#define _POINT_HPP_

#include "Player.hpp"

namespace ariel
{
    class Point
    {
    private:
        double _x;
        double _y;

    public:
        Point(double x, double y);
        Point(const Point &p); // Copy constructor
        ~Point();
        int getX();
        int getY();
        bool operator==(const Point &p) const;
        
        // Hash function for Point
        struct PointHasher
        {   
            size_t operator()(const Point &p) const
            {
                return hash<int>()(p._x) ^ hash<int>()(p._y);
            }
        };
    };
}

#endif