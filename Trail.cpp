// ID: 205739907
// Email: eladima66@gmail.com

#include <iostream>
#include <vector>
#include "Road.hpp"
#include "Trail.hpp"



using namespace std;
using namespace ariel;

// Destructor
Trail::~Trail() {
    if (this->_hasRoad)
    {
        delete this->_road;
    }
}

// Setters
void Trail::setRoad(const Player* owner)
{
    if (!this->_hasRoad)
    {
        this->_hasRoad = true;
        // Cast away the constness of the owner
        this->_road = new Road(const_cast<Player*>(owner));
    }
    else
    {
        throw invalid_argument("This trail already has a road");
    }
}

double Trail::getLength() const
{
   if (!this->_start.expired() && !this->_end.expired())
   {
       shared_ptr<Vertex> start = this->_start.lock();
       shared_ptr<Vertex> end = this->_end.lock();
       return start->distance(*end);
   }
   else
   {
       throw invalid_argument("One of the vertices of this trail is expired");
   }
}


void Trail::draw(sf::RenderWindow& window, double startX, double startY, double endX, double endY)
{
    if (this->_hasRoad)
    {
        sf::Color color = this->_road->getOwner()->getColor();

        // Calculate the length of the line
        double length = std::hypot(endX - startX, endY - startY);

        // Create a rectangle to represent the line
        sf::RectangleShape line(sf::Vector2f(length, 5.0f)); // 5.0f is the thickness of the line
        line.setFillColor(color);

        // Calculate the angle (in degrees) to rotate the line
        double angle = std::atan2(endY - startY, endX - startX) * 180 / M_PI;

        // Set the origin to the center of the rectangle for proper rotation
        line.setOrigin(0, 2.5f); // Half of the thickness as the origin

        // Rotate and position the line
        line.setRotation(angle);
        line.setPosition(sf::Vector2f(startX, startY));

        // Draw the line
        window.draw(line);
    }
}


