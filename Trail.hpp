#ifndef _TRAIL_HPP_
#define _TRAIL_HPP_
#include <memory>
#include "Vertex.hpp"
#include "Road.hpp"

/*
    The Trail class represents a trail (edge) in the game of Catan.
    A trail is a path between two vertices on the board.
    A trail can be owned by a player and can have a road built on it.
    A trail can be built between two vertices.
*/

namespace ariel
{
    class Vertex;
    
    class Road;

    class Player;
    
    class Trail
    {
        private:
            const Player* _owner;
            bool _hasRoad;
            shared_ptr<Vertex> _start;
            shared_ptr<Vertex> _end;
            Road* _road;
        
        public:
            Trail(const Player* owner, shared_ptr<Vertex>  start, shared_ptr<Vertex>  end): _owner(owner), _start(start), _end(end), _hasRoad(false), _road(nullptr) {}
            Trail(shared_ptr<Vertex>  start, shared_ptr<Vertex>  end): _owner(nullptr), _start(start), _end(end), _hasRoad(false), _road(nullptr) {}
            
            ~Trail();
            const Player* getOwner() const { return this->_owner; }
            bool hasRoad() const { return this->_hasRoad; }
            const shared_ptr<Vertex>& getStart() const { return this->_start; };
            const shared_ptr<Vertex>& getEnd() const { return this->_end; };
            void setRoad(const Player* owner);
            
            Road* getRoad() const { return this->_road; }
           
    };
}






#endif