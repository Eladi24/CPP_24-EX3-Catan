#include <iostream>
#include <vector>
#include <array>
#include "Hexagon.hpp"

using namespace std;
using namespace ariel;

// Constructor
Hexagon::Hexagon(LandType landType, int value, Point &center, int id): _landType(landType), _value(value), _center(center), id(id) {
    
    this->initResources();
    this->initHexagon();
}

// Destructor
Hexagon::~Hexagon() {}

// Initialize the resources of the hexagon
void Hexagon::initResources()
{
    switch (this->_landType)
    {
    case Forest:
        this->_resourceType = Wood;
        break;
    case Hills:
        this->_resourceType = Brick;
        break;
    case Mountains:
        this->_resourceType = Ore;
        break;
    case Pasture:
        this->_resourceType = Wool;
        break;
    case Field:
        this->_resourceType = Grain;
        break;
    case Desert:
        this->_resourceType = None;
        break;
    default:
        break;
    }
}

// Get the resource type of the hexagon
ResourceType Hexagon::getResourceType()
{
    return this->_resourceType;
}

// Get the land type of the hexagon
LandType Hexagon::getLandType()
{
    return this->_landType;
}


// Get the value of the hexagon
int Hexagon::getValue()
{
    return this->_value;
}

// Set the value of the hexagon
void Hexagon::setValue(int value)
{
    this->_value = value;
}

// Initialize the vertices of the hexagon
void Hexagon::initHexagon()
{
    double q = this->_center.getX();
    double r = this->_center.getY();
    double s = -q - r;
    if (s != 0)
    {
        throw "Invalid hexagon center";
    }

    // Initialize the vertices of the hexagon
    Vertex top(q, r + 1, 0);
    this->_verticesMap["top"].insert(top);

    Vertex topRight(q + Vertex::squareRoot3Div2, r + Vertex::half, 1);
    this->_verticesMap["topRight"].insert(topRight);

    Vertex bottomRight(q + Vertex::squareRoot3Div2, r - Vertex::half, 2);
    this->_verticesMap["bottomRight"].insert(bottomRight);

    Vertex bottom(q, r - 1, 3);
    this->_verticesMap["bottom"].insert(bottom);

    Vertex bottomLeft(q - Vertex::squareRoot3Div2, r - Vertex::half, 4);
    this->_verticesMap["bottomLeft"].insert(bottomLeft);

    Vertex topLeft(q - Vertex::squareRoot3Div2, r + Vertex::half, 5);
    this->_verticesMap["topLeft"].insert(topLeft);
    
    
    // Add the edges to the hexagon
    Trail topRightEdge(top, topRight);
    this->_edgesMap["topRightEdge"].insert(topRightEdge);

    Trail rightEdge(topRight, bottomRight);
    this->_edgesMap["rightEdge"].insert(rightEdge);

    Trail bottomRightEdge(bottomRight, bottom);
    this->_edgesMap["bottomRightEdge"].insert(bottomRightEdge);

    Trail bottomLeftEdge(bottom, bottomLeft);
    this->_edgesMap["bottomLeftEdge"].insert(bottomLeftEdge);

    Trail leftEdge(bottomLeft, topLeft);
    this->_edgesMap["leftEdge"].insert(leftEdge);

    Trail topLeftEdge(topLeft, top);
    this->_edgesMap["topLeftEdge"].insert(topLeftEdge);
    
}