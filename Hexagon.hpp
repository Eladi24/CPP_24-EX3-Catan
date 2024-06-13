#ifndef _HEXAGON_HPP_
#define _HEXAGON_HPP_
#include <vector>
#include <memory>
#include <set>
#include <map>
#include "Point.hpp"
#include "Vertex.hpp"
#include "Trail.hpp"


using namespace std;
namespace ariel
{
    enum LandType
    {
        Forest,
        Hills,
        Mountains,
        Pasture,
        Field,
        Desert,
        NONE
    };

    enum ResourceType
    {
        Wood,
        Brick,
        Ore,
        Wool,
        Grain,
        None
    };

    enum VertexLocation
    {
        TOP,
        TOP_RIGHT,
        BOTTOM_RIGHT,
        BOTTOM,
        BOTTOM_LEFT,
        TOP_LEFT
    };

    enum TrailLocation
    {
        TOP_RIGHT_EDGE,
        RIGHT_EDGE,
        BOTTOM_RIGHT_EDGE,
        BOTTOM_LEFT_EDGE,
        LEFT_EDGE,
        TOP_LEFT_EDGE
    };

    class Hexagon
    {
        private:
            LandType _landType;
            ResourceType _resourceType;
            int _value;
            int id;
            Point _center;
            // A set map of the vertices. The keys are the names of the vertices and the values are the vertices themselves.
            map<VertexLocation, shared_ptr<Vertex>> _verticesMap;
            // A set map of the edges. The keys are the names of the edges and the values are the edges themselves.
            map<TrailLocation, shared_ptr<Trail>> _edgesMap;
            

        public:
            Hexagon(LandType landType, int value, Point &center, int id);
            Hexagon(): _landType(LandType::NONE), _value(0), _center(Point(0,0)), id(0) {}
            ~Hexagon();
            void initResources();
            ResourceType getResourceType() const { return _resourceType;}
            LandType getLandType() const { return _landType;}
            int getValue() const { return _value;}
            void setValue(int value) { _value = value;}
            void initHexagon(map<Point, shared_ptr<Vertex>>& verticesMap, map<pair<shared_ptr<Vertex>, shared_ptr<Vertex>>, shared_ptr<Trail>>& edgesMap);
            int getId() const { return id;}
            Point getCenter() const { return _center;}
            map<VertexLocation, shared_ptr<Vertex>> getVerticesMap() const { return _verticesMap;}
            map<TrailLocation, shared_ptr<Trail>> getEdgesMap() const { return _edgesMap;}
            void printHexagon() const;
    };

}



#endif