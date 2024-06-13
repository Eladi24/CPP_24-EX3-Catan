#include <iostream>
#include <vector>
#include "Point.hpp"

using namespace std;
using namespace ariel;

Point::~Point() {}

bool Point::operator==(const Point &p) const
{
    return (this->_x == p._x && this->_y == p._y);
}

double Point::distance(const Point &p) const
{
    return sqrt(pow(this->_x - p._x, 2) + pow(this->_y - p._y, 2));
}

bool Point::operator<(const Point &other) const
{
    if (_x < other._x)
        return true;
    if (_x > other._x)
        return false;
    return _y < other._y;
}

