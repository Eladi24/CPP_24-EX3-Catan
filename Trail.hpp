#ifndef _TRAIL_HPP_
#define _TRAIL_HPP_

#include "Point.hpp"
#include "Player.hpp"

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
            Trail(Vertex start, Vertex end);
            ~Trail();
            Player getOwner();
            bool hasRoad();
            Vertex getStart();
            Vertex getEnd();
            void setRoad(const Player* owner);

    };
}






#endif