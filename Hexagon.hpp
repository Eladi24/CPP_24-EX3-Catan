#ifndef _HEXAGON_HPP_
#define _HEXAGON_HPP_
#include <set>
#include "Point.hpp"

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
        Desert
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
        TopLeft,
        TopRight,
        Right,
        BottomRight,
        BottomLeft,
        Left
    };

    enum TrailLocation
    {
        Top,
        TopRight,
        BottomRight,
        Bottom,
        BottomLeft,
        TopLeft
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
            map<string, set<Vertex>> _verticesMap;
            // A set map of the edges. The keys are the names of the edges and the values are the edges themselves.
            map<string, set<Trail>> _edgesMap;

            

        public:
            Hexagon(LandType landType, int value, Point &center, int id);
            ~Hexagon();
            void initResources();
            ResourceType getResourceType();
            LandType getLandType();
            int getValue();
            void setValue(int value);
            void initHexagon();
            int getId();
            Point getCenter();
            map<string, set<Vertex>> getVerticesMap();
            map<string, set<Trail>> getEdgesMap();   
    };

}



#endif