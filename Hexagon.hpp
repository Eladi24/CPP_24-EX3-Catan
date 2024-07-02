// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _HEXAGON_HPP_
#define _HEXAGON_HPP_
#include <vector>
#include <memory>
#include <set>
#include <map>
#include "Types.hpp"
#include "Vertex.hpp"
#include "Trail.hpp"

using namespace std;
namespace ariel
{
    
    class Vertex;
    class Trail;

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

    class Hexagon : public enable_shared_from_this<Hexagon>
    {
        private:
            LandType _landType;
            ResourceType _resourceType;
            int _value;
            int id;
            Point _center;
            // A set map of the vertices. The keys are the names of the vertices and the values are the vertices themselves.
            map<VertexLocation, weak_ptr<Vertex>> _verticesMap;
            // A set map of the edges. The keys are the names of the edges and the values are the edges themselves.
            map<TrailLocation, weak_ptr<Trail>> _edgesMap;
            bool _hasRobber;
            static int hexagonCounter;
            static int EdgeCounter;
            

        public:
            
            Hexagon(LandType landType, int value, Point &center, int id);

            Hexagon(): enable_shared_from_this<Hexagon>(), _landType(LandType::None), _resourceType(ResourceType::None), _value(0), id(0), _center(Point(0,0)), _verticesMap(), _edgesMap(), _hasRobber(false) {} 

            ~Hexagon();
            /*
            * @brief
            * This function initializes the resources of the hexagon.
            * It sets the resource type and the value of the hexagon.
            */
            void initResources();

            ResourceType getResourceType() const { return _resourceType;}

            LandType getLandType() const { return _landType;}

            int getValue() const { return _value;}

            void setValue(int value) { _value = value;}
            /*
            * @brief
            * This function initializes the vertices and edges of the hexagon.
            * It sets the vertices and edges of the as a shared pointers so that they can be accessed by other classes and hexagons.
            * @param verticesMap - A map of the total vertices in the game.
            * @param edgesMap - A map of the total edges in the game.
            * @return void
            */
            void initHexagon( map<Point, vector<shared_ptr<Vertex>>>& verticesMap, map<Point, vector<shared_ptr<Trail>>>& edgesMap);
            int getId() const { return id;}

            Point getCenter() const { return _center;}

            const map<VertexLocation, weak_ptr<Vertex>> getVerticesMap() const { return _verticesMap;}

            const map<TrailLocation, weak_ptr<Trail>> getEdgesMap() const { return _edgesMap;}
            
            string getLandTypeString();

            bool operator==(const Hexagon& other) const;

            bool hasRobber() const { return _hasRobber;}

            void setRobber(bool hasRobber) { _hasRobber = hasRobber;}
            
           
            
            
    };

}



#endif