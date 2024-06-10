#ifndef _TRAIL_HPP_
#define _TRAIL_HPP_

#include "Point.hpp"
#include "Player.hpp"

namespace ariel
{
    class Trail
    {
        private:
            Player* _owner;
            bool _hasRoad;
            Vertex _start;
            Vertex _end;
        
        public:
            Trail(Player* owner, Vertex start, Vertex end);
            Trail(Vertex start, Vertex end);
            ~Trail();
            Player getOwner();
            bool hasRoad();
            Vertex getStart();
            Vertex getEnd();
            void setRoad(Player* owner);

    };
}






#endif