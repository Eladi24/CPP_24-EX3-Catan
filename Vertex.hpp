#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include "Point.hpp"
#include "Structure.hpp"

using namespace std;

namespace ariel
{

    class Vertex: public Point
    {
        private:
            vector<Vertex> _neighbors;
            Structure* _structure;
            bool _isOccupied;
            int _id;
            
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
            friend ostream& operator<<(ostream& os, const Vertex& vertex);
    };
}







#endif