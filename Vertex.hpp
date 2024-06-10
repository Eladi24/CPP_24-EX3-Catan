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
            Player* _owner;
            Structure* _structure;
            bool _isOccupied;
            bool _isCity;
            int _id;
            
        public:
            Vertex(int x, int y, int id);
            Vertex(int x, int y, int id, Player* owner, Structure* structure);
            ~Vertex();
            void addNeighbor(Vertex v);
            void buildSettlement(Player* p);
            void buildCity(Player* p);
            void yieldResources();
            bool isOccupied();
            bool isCity();
            Player getOwner();
    };
}







#endif