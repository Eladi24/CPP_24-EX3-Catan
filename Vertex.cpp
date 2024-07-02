// ID: 205739907
// Email: eladima66@gmail.com

#include <iostream>
#include <vector>
#include "Vertex.hpp"
#include "Settlement.hpp"
#include "City.hpp"

using namespace ariel;


// Destructor
Vertex::~Vertex() {
    delete this->_structure;
    this->_hexagons.clear();
}

// Build a settlement on the vertex
void Vertex::buildSettlement(Player* p)
{
    if (this->_isOccupied && this->_structure->getOwner() != p) 
    {
        
        throw invalid_argument("This vertex is already occupied by"); 
    }
    
    this->_isOccupied = true;
    this->_structure = new Settlement(p);
}

// Build a city on the vertex

void Vertex::buildCity(Player* p)
{
    if (this->_isOccupied && this->_structure->getOwner() != p)
    {
        throw invalid_argument("This vertex is already occupied by");
    } 
    else if (!this->_isOccupied)
    {
        throw invalid_argument("Cannot build a city on an unoccupied vertex");
    }

    
    // delete the settlement and build a city
    delete this->_structure;
    this->_structure = new City(p);
    
}

// Yield resources from the vertex
void Vertex::yieldResources(ResourceType resource, Cashbox &cashbox)
{
    if (this->_isOccupied)
    {   
        
        this->_structure->yieldResources(resource, cashbox);
    }
    else
    {
        throw invalid_argument("Cannot yield resources from an unoccupied vertex");
    }
}

bool Vertex::operator==(const Point& other) const {
        static const double EPSILON = 1e-6;
        return std::abs(this->getX() - other.getX()) < EPSILON && std::abs(this->getY() - other.getY()) < EPSILON;
    }


shared_ptr<Trail> Vertex::getTrail(shared_ptr<Vertex> v) const
{
    for (auto &trail : this->_trails)
    {
        if (!trail.expired())
        {
            shared_ptr<Trail> t = trail.lock();
            if (t->getStart().lock() == v || t->getEnd().lock() == v)
            {
                return t;
            }
        }
        else {
            throw invalid_argument("One of the trails of this vertex is expired");
        
        }
    }
    cout << "No trail found between the vertices" << endl;
    return nullptr;
}

void Vertex::draw(sf::RenderWindow& window, double x, double y)
{
    if (this->_isOccupied)
    {
        // Define the size of the point. Adjust the radius as needed.
        float radius = 7.0f; // Example size that is neither too small nor too large

        // Create a circle shape to represent the point
        sf::CircleShape point(radius);

        // Set the fill color to the owner's color
        point.setFillColor(this->_structure->getOwner()->getColor());

        // Set the position of the point. Assuming you have a way to get the vertex's position.
        // For example, if each structure knows its vertex position:
        point.setPosition(x - radius, y - radius);

        // Draw the point on the window
        window.draw(point);
    }
}







