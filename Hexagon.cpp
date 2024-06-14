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

    this->_edgesMap[TOP_RIGHT_EDGE] = createEdge(top, topRight);
    this->_edgesMap[RIGHT_EDGE] = createEdge(topRight, bottomRight);
    this->_edgesMap[BOTTOM_RIGHT_EDGE] = createEdge(bottomRight, bottom);
    this->_edgesMap[BOTTOM_LEFT_EDGE] = createEdge(bottom, bottomLeft);
    this->_edgesMap[LEFT_EDGE] = createEdge(bottomLeft, topLeft);
    this->_edgesMap[TOP_LEFT_EDGE] = createEdge(topLeft, top);
}


ostream &ariel::operator<<(ostream &os, const Hexagon &hexagon)
{
    // Print the edges of the hexagon, land type and value
    switch (hexagon._landType)
    {
    case Forest:
        os << "Forest ";
        break;
    case Hills:
        os << "Hills ";
        break;
    case Mountains:
        os << "Mountains ";
        break;
    case Pasture:
        os << "Pasture ";
        break;
    case Field:
        os << "Field ";
        break;
    case Desert:
        os << "Desert ";
        break;
    default:
        break;
    }

    os << hexagon._value << " ";
    for (auto const &edge : hexagon._edgesMap)
    {
        os << *edge.second;
    }
}
