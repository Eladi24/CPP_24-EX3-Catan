#include <iostream>
#include <vector>
#include <array>
#include "Hexagon.hpp"


using namespace std;
using namespace ariel;

// Constructor
Hexagon::Hexagon(LandType landType, int value, Point &center, int id) : _landType(landType), _value(value), _center(center), id(id)
{

    this->initResources();
}

// Destructor
Hexagon::~Hexagon() {}

// Initialize the resources of the hexagon
void Hexagon::initResources()
{
    switch (this->_landType)
    {
    case LandType::Forest:
        this->_resourceType = ResourceType::Wood;
        break;
    case LandType::Hills:
        this->_resourceType = ResourceType::Brick;
        break;
    case LandType::Mountains:
        this->_resourceType = ResourceType::Ore;
        break;
    case LandType::Pasture:
        this->_resourceType = ResourceType::Wool;
        break;
    case LandType::Field:
        this->_resourceType = ResourceType::Grain;
        break;
    case LandType::Desert:
        this->_resourceType = ResourceType::None;
        break;
    default:
        break;
    }
}

// Initialize the vertices of the hexagon
void Hexagon::initHexagon(map<Point, shared_ptr<Vertex>> &verticesMap, map<pair<shared_ptr<Vertex>, shared_ptr<Vertex>>, shared_ptr<Trail>> &edgesMap)
{
    // Create or reuse vertices
    auto createVertex = [&](double q, double r, int id)
    {
        Point p = Point(q, r);
        if (verticesMap.find(p) == verticesMap.end())
        {
            verticesMap[p] = make_shared<Vertex>(q, r, id);
        }
        return verticesMap[p];
    };
    auto top = createVertex(this->_center.getX(), this->_center.getY() + 1, 0);
    auto topRight = createVertex(this->_center.getX() + Vertex::squareRoot3Div2, this->_center.getY() + Vertex::half, 1);
    auto bottomRight = createVertex(this->_center.getX() + Vertex::squareRoot3Div2, this->_center.getY() - Vertex::half, 2);
    auto bottom = createVertex(this->_center.getX(), this->_center.getY() - 1, 3);
    auto bottomLeft = createVertex(this->_center.getX() - Vertex::squareRoot3Div2, this->_center.getY() - Vertex::half, 4);
    auto topLeft = createVertex(this->_center.getX() - Vertex::squareRoot3Div2, this->_center.getY() + Vertex::half, 5);
    this->_verticesMap[TOP] = top;
    this->_verticesMap[TOP_RIGHT] = topRight;
    this->_verticesMap[BOTTOM_RIGHT] = bottomRight;
    this->_verticesMap[BOTTOM] = bottom;
    this->_verticesMap[BOTTOM_LEFT] = bottomLeft;
    this->_verticesMap[TOP_LEFT] = topLeft;

    top->addHexagon(shared_from_this());
    topRight->addHexagon(shared_from_this());
    bottomRight->addHexagon(shared_from_this());
    bottom->addHexagon(shared_from_this());
    bottomLeft->addHexagon(shared_from_this());
    topLeft->addHexagon(shared_from_this());

    // Create or reuse edges
    auto createEdge = [&](shared_ptr<Vertex> v1, shared_ptr<Vertex> v2)
    {
        pair<shared_ptr<Vertex>, shared_ptr<Vertex>> key = {v1, v2};
        if (edgesMap.find(key) == edgesMap.end())
        {
            edgesMap[key] = make_shared<Trail>(v1, v2);
        }
        return edgesMap[key];
    };

    auto topRightEdge = createEdge(top, topRight);
    auto rightEdge = createEdge(topRight, bottomRight);
    auto bottomRightEdge = createEdge(bottomRight, bottom);
    auto bottomLeftEdge = createEdge(bottom, bottomLeft);
    auto leftEdge = createEdge(bottomLeft, topLeft);
    auto topLeftEdge = createEdge(topLeft, top);

    this->_edgesMap[TOP_RIGHT_EDGE] = topRightEdge;
    this->_edgesMap[RIGHT_EDGE] = rightEdge;
    this->_edgesMap[BOTTOM_RIGHT_EDGE] = bottomRightEdge;
    this->_edgesMap[BOTTOM_LEFT_EDGE] = bottomLeftEdge;
    this->_edgesMap[LEFT_EDGE] = leftEdge;
    this->_edgesMap[TOP_LEFT_EDGE] = topLeftEdge;
    top->addTrail(topRightEdge);
    top->addTrail(topLeftEdge);
    topRight->addTrail(topRightEdge);
    topRight->addTrail(rightEdge);
    bottomRight->addTrail(rightEdge);
    bottomRight->addTrail(bottomRightEdge);
    bottom->addTrail(bottomRightEdge);
    bottom->addTrail(bottomLeftEdge);
    bottomLeft->addTrail(bottomLeftEdge);
    bottomLeft->addTrail(leftEdge);
    topLeft->addTrail(leftEdge);
    topLeft->addTrail(topLeftEdge);
}


// ostream &ariel::operator<<(ostream &os, const Hexagon &hexagon)
// {
//     // Print the edges of the hexagon, land type and value
//     switch (hexagon._landType)
//     {
//     case Forest:
//         os << "Forest ";
//         break;
//     case Hills:
//         os << "Hills ";
//         break;
//     case Mountains:
//         os << "Mountains ";
//         break;
//     case Pasture:
//         os << "Pasture ";
//         break;
//     case Field:
//         os << "Field ";
//         break;
//     case Desert:
//         os << "Desert ";
//         break;
//     default:
//         break;
//     }

//     os << hexagon._value << " ";
//     for (auto const &edge : hexagon._edgesMap)
//     {
//         os << *edge.second;
//     }
// }
