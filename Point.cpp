#include <iostream>
#include <vector>
#include "Point.hpp"

using namespace std;
using namespace ariel;

Point::~Point() {}

bool Point::operator==(const Point &p) const
{
    static const double EPSILON = 1e-6;
        return std::abs(this->getX() - p.getX()) < EPSILON && std::abs(this->getY() - p.getY()) < EPSILON;
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

