#include <iostream>
#include <vector>
#include <array>
#include "Hexagon.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace ariel;

int Hexagon::hexagonCounter = 0;
int Hexagon::EdgeCounter = 0;
// Constructor
Hexagon::Hexagon(LandType landType, int value, Point &center, int id) : enable_shared_from_this<Hexagon>(), _landType(landType), _resourceType(ResourceType::None), _value(value), id(id), _center(center), _verticesMap(), _edgesMap()

{
    // this->_center = pixelToPointyHex(center, HEXAGON_RADIUS);
    this->initResources();
}

// Destructor
Hexagon::~Hexagon()
{
    this->_verticesMap.clear();
    this->_edgesMap.clear();
}

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
void Hexagon::initHexagon(map<Point, vector<shared_ptr<Vertex>>> &verticesMap, map<Point, vector<shared_ptr<Trail>>> &edgesMap)
{
    // Create or reuse vertices
    auto createVertex = [&](double q, double r, int id)
    {
        Point p = Point(q, r);
        for (auto &[location, vertices] : verticesMap)
        {
            for (auto &vertex : vertices)
            {
                if (*vertex == p)
                {

                    return vertex;
                }
            }
        }
        hexagonCounter++;
        verticesMap[this->_center].push_back(make_shared<Vertex>(q, r, id));
        
        return verticesMap[this->_center].back();
    };

    auto top = createVertex(this->_center.getX(), this->_center.getY() + 1, 0);
    top->addHexagon(shared_from_this());

    auto topRight = createVertex(this->_center.getX() + Vertex::squareRoot3Div2, this->_center.getY() + Vertex::half, 1);
    topRight->addHexagon(shared_from_this());
    auto bottomRight = createVertex(this->_center.getX() + Vertex::squareRoot3Div2, this->_center.getY() - Vertex::half, 2);
    bottomRight->addHexagon(shared_from_this());
    auto bottom = createVertex(this->_center.getX(), this->_center.getY() - 1, 3);
    bottom->addHexagon(shared_from_this());
    auto bottomLeft = createVertex(this->_center.getX() - Vertex::squareRoot3Div2, this->_center.getY() - Vertex::half, 4);
    bottomLeft->addHexagon(shared_from_this());
    auto topLeft = createVertex(this->_center.getX() - Vertex::squareRoot3Div2, this->_center.getY() + Vertex::half, 5);
    topLeft->addHexagon(shared_from_this());
    // cast shared_ptr<Vertex> to weak_ptr<Vertex>
    this->_verticesMap[TOP] = top;
    this->_verticesMap[TOP_RIGHT] = topRight;
    this->_verticesMap[BOTTOM_RIGHT] = bottomRight;
    this->_verticesMap[BOTTOM] = bottom;
    this->_verticesMap[BOTTOM_LEFT] = bottomLeft;
    this->_verticesMap[TOP_LEFT] = topLeft;
    
    // Create or reuse edges
    auto createEdge = [&](shared_ptr<Vertex> v1, shared_ptr<Vertex> v2)
    {
        for (auto &[key, edges] : edgesMap)
        {
            for (auto &edge : edges)
            {
                if (!edge->getStart().expired() && !edge->getEnd().expired())
                {
                    shared_ptr<Vertex> start = edge->getStart().lock();
                    shared_ptr<Vertex> end = edge->getEnd().lock();
                    if ((*start == *v1 && *end == *v2) || (*start == *v2 && *end == *v1))
                    {

                        return edge;
                    }
                }
            }
        }
        EdgeCounter++;
        edgesMap[this->_center].push_back(make_shared<Trail>(v1, v2));
        return edgesMap[this->_center].back();
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

// Get the land type of the hexagon
string Hexagon::getLandTypeString()
{
    // If the land type is null raise an exception

    switch (this->_landType)
    {
    case LandType::Forest:
        return "Forest";
    case LandType::Hills:
        return "Hills";
    case LandType::Mountains:
        return "Mountains";
    case LandType::Pasture:
        return "Pasture";
    case LandType::Field:
        return "Field";
    case LandType::Desert:
        return "Desert";
    default:
        return "None";
    }
}

Point Hexagon::pointyHextoPixel(Point center, double size)
{
    double x = size * (sqrt(3.0) * center.getX() + sqrt(3.0) / 2 * center.getY());
    double y = size * (3.0 / 2 * center.getY());
    return Point(x, y);
}

Point Hexagon::pixelToPointyHex(Point p, double size)
{
    double q = (sqrt(3.0) / 3 * p.getX() - 1.0 / 3 * p.getY()) / size;
    double r = (2.0 / 3 * p.getY()) / size;
    return Point(q, r);
}

Point Hexagon::pixelToPointyHexFraction(double x, double y)
{
    double q = sqrt(3.0) / 3 * x - 1.0 / 3 * y;
    double r = 2.0 / 3 * y;
    return Point(q, r);
}

bool Hexagon::operator==(const Hexagon &other) const
{
    return this->_center == other._center;
}