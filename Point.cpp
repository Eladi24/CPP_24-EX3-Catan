#include <iostream>
#include <vector>
#include "Point.hpp"

using namespace std;
using namespace ariel;

Point::Point(int x, int y): _x(x), _y(y) {}

Point::Point(const Point &p): _x(p._x), _y(p._y) {}

bool Point::operator==(const Point &p) const
{
    return (this->_x == p._x && this->_y == p._y);
}


int Point::getX()
{
    return this->_x;
}

int Point::getY()
{
    return this->_y;
}






