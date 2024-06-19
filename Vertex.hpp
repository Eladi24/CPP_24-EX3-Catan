#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_
#include "Point.hpp"
#include "Types.hpp"
#include "Hexagon.hpp"
#include "Structure.hpp"
#include "Player.hpp"
#include "Cashbox.hpp"


using namespace std;

namespace ariel
{
    class Structure;
    class Hexagon;
    
    class Vertex: public Point
    {
        private:
            Structure* _structure;
            bool _isOccupied;
            int _id;
            vector<weak_ptr<Hexagon>> _hexagons;
            vector<weak_ptr<Trail>> _trails;
            
        public:
            static constexpr double squareRoot3Div2 = 0.86602540378;
            static constexpr double half = 0.5;
            Vertex(double x, double y, int id): Point(x, y), _structure(nullptr), _isOccupied(false), _id(id), _hexagons(), _trails() {} 
            Vertex(double x, double y, int id, Structure* structure): Point(x, y), _structure(structure), _isOccupied(true), _id(id), _hexagons(), _trails() {}
            ~Vertex();
            
            void buildSettlement(Player* p);
            void buildCity(Player* p);
            void yieldResources(ResourceType resource, Cashbox &cashbox);
            bool isOccupied() const { return this->_isOccupied; }
            Structure* getStructure() const { return this->_structure; }
            int getId() const { return this->_id; }
            
            vector<weak_ptr<Hexagon>> getHexagons() const { return this->_hexagons; }
            vector<weak_ptr<Trail>> getTrails() const { return this->_trails; }
            void addHexagon(shared_ptr<Hexagon> hex) { this->_hexagons.push_back(hex); }
            void addTrail(shared_ptr<Trail> trail) { this->_trails.push_back(trail); }
            bool operator==(const Point& p) const;
            shared_ptr<Trail> getTrail(shared_ptr<Vertex> v) const;
            
            
    };
}







#endif