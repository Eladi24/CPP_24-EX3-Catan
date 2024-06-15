#include <iostream>
#include <vector>
#include <array>
#include "Hexagon.hpp"
#include <SFML/Graphics.hpp>


using namespace std;
using namespace ariel;

int Hexagon::hexagonCounter = 0;
// Constructor
Hexagon::Hexagon(LandType landType, int value, Point &center, int id) : enable_shared_from_this<Hexagon>(), _landType(landType), _resourceType(ResourceType::None), _value(value), id(id), _center(center), _verticesMap(), _edgesMap()

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
            hexagonCounter++;
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

// Get the radius of the hexagon
double Hexagon::getRadius()
{
    for (auto &[location, edge] : this->_edgesMap)
    {
        cout << "Length of edge: " << edge->getLength() << endl;
    }
    return 0;
    
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

