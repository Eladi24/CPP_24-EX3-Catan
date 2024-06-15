#ifndef _POINT_HPP_
#define _POINT_HPP_
#include <iostream>
#include <cmath>
using namespace std;
namespace ariel
{
    class Point
    {
    private:
        double _x;
        double _y;

    public:
        Point(double x, double y): _x(x), _y(y) {}
        Point(): _x(0), _y(0) {}
        Point(const Point &p): _x(p._x), _y(p._y) {}
        ~Point();
        double getX() const { return this->_x; }
        double getY() const { return this->_y; }
        bool operator==(const Point &p) const;
        bool operator<(const Point &p) const;
        double distance(const Point &p) const;
        
        // Hash function for Point
        struct PointHasher
        {   
            size_t operator()(const Point &p) const
            {
                return hash<double>()(p._x) ^ hash<double>()(p._y);
            }
        };
    };
}

#endif