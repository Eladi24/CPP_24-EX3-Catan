// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _TRAIL_HPP_
#define _TRAIL_HPP_
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
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
            weak_ptr<Vertex> _start;
            weak_ptr<Vertex> _end;
            Road* _road;
        
        public:
            Trail(const Player* owner, shared_ptr<Vertex>  start, shared_ptr<Vertex>  end): _owner(owner), _hasRoad(true), _start(start), _end(end), _road(nullptr) {}
            Trail(shared_ptr<Vertex>  start, shared_ptr<Vertex>  end): _owner(nullptr), _hasRoad(false), _start(start), _end(end), _road(nullptr) {}
            double getLength() const;
            ~Trail();
            const Player* getOwner() const { return this->_owner; }
            bool hasRoad() const { return this->_hasRoad; }
            const weak_ptr<Vertex>& getStart() const { return this->_start; };
            const weak_ptr<Vertex>& getEnd() const { return this->_end; };
            void setRoad(const Player* owner);
            
            Road* getRoad() const { return this->_road; }

            void draw(sf::RenderWindow& window, double startX, double startY, double endX, double endY);
           
    };
}






#endif