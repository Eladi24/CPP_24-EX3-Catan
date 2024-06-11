#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include <vector>
#include <string>
#include "Player.hpp"
#include "Structure.hpp"
using namespace std;

namespace ariel
{
    class Vertex: public Point
    {
        private:
            vector<Vertex> _neighbors;
            const Player* _owner;
            Structure* _structure;
            bool _isOccupied;
            bool _isCity;
            int _id;
            
        public:
            const static double squareRoot3Div2 = 0.86602540378;
            const static double half = 0.5;
            Vertex(double x, double y, int id);
            Vertex(double x, double y, int id, const Player* owner, Structure* structure);
            ~Vertex();
            void addNeighbor(Vertex v);
            void buildSettlement(const Player* p);
            void buildCity(const Player* p);
            void yieldResources();
            bool isOccupied();
            bool isCity();
            Player getOwner();
            int getId();
    };
}







#endif