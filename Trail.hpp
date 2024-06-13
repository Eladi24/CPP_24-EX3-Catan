#ifndef _TRAIL_HPP_
#define _TRAIL_HPP_
#include <memory>
#include "Vertex.hpp"
/*
    The Trail class represents a trail (edge) in the game of Catan.
    A trail is a path between two vertices on the board.
    A trail can be owned by a player and can have a road built on it.
    A trail can be built between two vertices.
*/

namespace ariel
{
    
    class Trail
    {
        private:
            const Player* _owner;
            bool _hasRoad;
            Vertex _start;
            Vertex _end;
        
        public:
            Trail(const Player* owner, Vertex start, Vertex end);
            Trail(Vertex start, Vertex end): _owner(nullptr), _start(start), _end(end), _hasRoad(false) {}
            Trail(std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end): _owner(nullptr), _start(*start), _end(*end), _hasRoad(false) {}
            ~Trail();
            const Player* getOwner() const { return this->_owner; }
            bool hasRoad() const { return this->_hasRoad; }
            Vertex getStart() const { return this->_start; };
            Vertex getEnd() const { return this->_end; };
            void setRoad(const Player* owner);
           
    };
}






#endif