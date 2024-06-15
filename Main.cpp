#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

using namespace std;
using namespace ariel;

int main()
{
    Board board = Board();
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Catan Board");
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        board.printBoard(window);
        window.display();
        //window.close();
    }
    
    return 0;
}