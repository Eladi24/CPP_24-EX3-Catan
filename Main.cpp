#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "DevCard.hpp"

using namespace std;
using namespace ariel;

int main()
{
    int roll_sum;
    Player *p1 = new Player("Aviv", sf::Color::Red);
    Player *p2 = new Player("Gal", sf::Color::Blue);
    Player *p3 = new Player("Yarden", sf::Color::Magenta);
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.setGamePhase(GamePhase::SETUP);
    catan.ChooseStartingPlayer();
    Board &board = catan.getBoard();
    Cashbox &cashbox = catan.getCashbox();
    vector<LandType> places = {LandType::Pasture, LandType::Hills};
    vector<int> placesNum = {2, 6};
    p1->placeSettelemnt(places, placesNum, board, cashbox);
    p1->placeRoad(places, placesNum, board, cashbox);

    places = {LandType::Field, LandType::Forest};
    placesNum = {9, 8};
    p1->placeSettelemnt(places, placesNum, board, cashbox);
    p1->placeRoad(places, placesNum, board, cashbox);

    places = {LandType::Pasture, LandType::Field};
    placesNum = {11, 4};
    p2->placeSettelemnt(places, placesNum, board, cashbox);
    p2->placeRoad(places, placesNum, board, cashbox);

    places = {LandType::Forest, LandType::Hills};
    placesNum = {8, 5};
    p2->placeSettelemnt(places, placesNum, board, cashbox);
    p2->placeRoad(places, placesNum, board, cashbox);

    places = {LandType::Mountains, LandType::Field};
    placesNum = {3, 6};
    p3->placeSettelemnt(places, placesNum, board, cashbox);
    p3->placeRoad(places, placesNum, board, cashbox);

    places = {LandType::Forest, LandType::Hills};
    placesNum = {9, 10};
    p3->placeSettelemnt(places, placesNum, board, cashbox);
    p3->placeRoad(places, placesNum, board, cashbox);
    board.printBoard();

    // Starting the game
    catan.setGamePhase(GamePhase::PLAY);
    roll_sum = p1->rollDice();
    catan.analyzeDiceRoll(roll_sum, p1);
    // P1 want to continue the road he started
    places = {LandType::Pasture, LandType::Hills};
    placesNum = {2, 6};
    p1->placeRoad(places, placesNum, board, cashbox);
    p1->endTurn();
    catan.turnCycleChange();

    roll_sum = p2->rollDice();
    catan.analyzeDiceRoll(roll_sum, p2);
    // P2 want to continue the road he started
    places = {LandType::Hills, LandType::Mountains};
    placesNum = {5, 3};
    p2->placeRoad(places, placesNum, board, cashbox);
    p2->endTurn();
    catan.turnCycleChange();

    roll_sum = p3->rollDice();
    catan.analyzeDiceRoll(roll_sum, p3);
    // P3 try to built on existing settlement and road
    places = {LandType::Mountains, LandType::Field};
    placesNum = {3, 6};

    try
    {
        p3->placeSettelemnt(places, placesNum, board, cashbox);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    try
    {
        p3->placeRoad(places, placesNum, board, cashbox);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    places = {LandType::Field, LandType::Field};
    placesNum = {6, 4};

    p3->placeRoad(places, placesNum, board, cashbox);
    p3->endTurn();
    catan.turnCycleChange();
    board.printBoard();

    roll_sum = p1->rollDice();
    catan.analyzeDiceRoll(roll_sum, p1);
    
    if (p1->canAffordCity())
    {
        p1->placeCity({LandType::Pasture, LandType::Hills}, {2, 6}, board, cashbox);

    }
    else
    {
        cout << "Player " << p1->getName() << " can't afford a city" << endl;
    }

    return 0;
}