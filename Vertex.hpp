#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_
#include "Point.hpp"
#include "Types.hpp"
#include "Hexagon.hpp"
#include "Structure.hpp"
#include "Player.hpp"


using namespace std;

namespace ariel
{
    class Structure;
    class Hexagon;
    
    class Vertex: public Point
    {
        private:
            vector<Vertex> _neighbors;
            Structure* _structure;
            bool _isOccupied;
            int _id;
            set<shared_ptr<Hexagon>> _hexagons;
            set<shared_ptr<Trail>> _trails;
            
        public:
            static constexpr double squareRoot3Div2 = 0.86602540378;
            static constexpr double half = 0.5;
            Vertex(double x, double y, int id): Point(x, y), _id(id), _isOccupied(false), _structure(nullptr) {}
            Vertex(double x, double y, int id, Structure* structure): Point(x, y), _id(id), _isOccupied(true), _structure(structure) {}
            ~Vertex();
            void addNeighbor(Vertex v);
            void buildSettlement(Player* p);
            void buildCity(Player* p);
            void yieldResources(ResourceType resource);
            bool isOccupied() const { return this->_isOccupied; }
            Structure* getStructure() const { return this->_structure; }
            int getId() const { return this->_id; }
            
            set<shared_ptr<Hexagon>> getHexagons() const { return this->_hexagons; }
            set<shared_ptr<Trail>> getTrails() const { return this->_trails; }
            void addHexagon(shared_ptr<Hexagon> hex) { this->_hexagons.insert(hex); }
            void addTrail(shared_ptr<Trail> trail) { this->_trails.insert(trail); }
    };
}







#endif