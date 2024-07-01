/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
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
    Player* p1 = new Player("Amit", sf::Color::Red);
    Player* p2 = new Player("Yossi", sf::Color::Blue);
    Player* p3 = new Player("Dana", sf::Color::Magenta);

    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.setGamePhase(GamePhase::SETUP);
    catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    Board& board = catan.getBoard(); // get the board of the game.
    Cashbox& cashbox = catan.getCashbox(); // get the cashbox of the game.
    cashbox.printDeck(); // print the deck of the cashbox.
    vector<LandType> places = {LandType::Forest, LandType::Hills};
    vector<int> placesNum = {11, 6};
    p1->placeSettelemnt(places, placesNum, board, cashbox);
    p1->placeRoad(places, placesNum, board, cashbox); // p1 chooses Forest, hills with numbers 11, 6.
    board.printBoard(); // print the board of the game.
    
    places = {LandType::Field, LandType::Desert};
    placesNum = {4, 0};
    p1->placeSettelemnt(places, placesNum, board, cashbox);
    p1->placeRoad(places, placesNum, board, cashbox); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.

    
    places = {LandType::Mountains, LandType::Pasture};
    placesNum = {8, 5};
    p2->placeSettelemnt(places, placesNum, board, cashbox);
    p2->placeRoad(places, placesNum, board, cashbox); // p2 chooses Mountains, Pasture Land with numbers 8, 5.
    try
    {
        p3->placeSettelemnt(places, placesNum, board, cashbox); // p3 tries to place a settlement in the same location as p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    
    places = {LandType::Forest, LandType::Pasture};
    placesNum = {9, 2};
    p2->placeSettelemnt(places, placesNum, board, cashbox);
    p2->placeRoad(places, placesNum, board, cashbox); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.

    
    places = {LandType::Mountains, LandType::Pasture};
    placesNum = {10, 2};
    p3->placeSettelemnt(places, placesNum, board, cashbox);
    p3->placeRoad(places, placesNum, board, cashbox); // p3 chooses Mountains, Pasture Land with numbers 10, 2.
    
    places = {LandType::Field, LandType::Pasture};
    placesNum = {4, 5};
    p3->placeSettelemnt(places, placesNum, board, cashbox);
    p3->placeRoad(places, placesNum, board, cashbox); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.
    catan.setGamePhase(GamePhase::PLAY); // Starting the game phase.

    // p1 has wood,bricks, and wheat, p2 has wood, ore, and wool, p3 has ore, wool, wheat.
    roll_sum =  p1->rollDice();
    catan.analyzeDiceRoll(roll_sum, p1);                                    // Lets say it's print 4. Then, p2 gets ore from the mountations.
    p1->placeRoad({LandType::Forest, LandType::Hills}, {11, 6}, board, cashbox); // p1 continues to build a road.
    p1->endTurn();                                     // p1 ends his turn.
    catan.turnCycleChange(); // p2's turn.

    roll_sum = p2->rollDice(); // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    catan.analyzeDiceRoll(roll_sum, p2);
    p2->endTurn();  // p2 ends his turn.
    catan.turnCycleChange(); // p3's turn.

    roll_sum = p3->rollDice(); // Lets say it's print 3. Then, p3 gets wheat from the Agricultural Land and Ore from the Mountains, p1 gets wheat from the Agricultural Land.
    catan.analyzeDiceRoll(roll_sum, p3);
    p3->endTurn();  // p3 ends his turn.
    catan.turnCycleChange(); // p1's turn.

    try
    {
        p2->rollDice(); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    roll_sum = p1->rollDice(); // Lets say it's print 6. Then, p1 gets bricks from the hills.
    catan.analyzeDiceRoll(roll_sum, p1);
    board.printBoard(); // print the board of the game.

    try {
            p1->trade(*p2, ResourceType::Wood, ResourceType::Brick, 1, 1); // p1 trades 1 wood for 1 brick with p2.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    
    p1->endTurn();                        // p1 ends his turn.
    catan.turnCycleChange(); // p2's turn.
    roll_sum = p2->rollDice();           // Lets say it's print 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    catan.analyzeDiceRoll(roll_sum, p2);

    try {
            p2->buyDevelopmentCard(cashbox); // p2 buys a development card. Lets say it is a bonus points card.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    try {
        p2->activateDevCard(board, cashbox, {p1, p2, p3}); // p2 activates the bonus points card.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    
    p2->endTurn();            // p2 ends his turn.
    catan.turnCycleChange(); // p3's turn.
    p1->printPoints(); // p1 has 2 points because it has two settelments.
    p2->printPoints(); // p2 has 3 points because it has two settelments and a bonus points card.
    p3->printPoints(); // p3 has 2 points because it has two settelments.

    catan.printWinner(); // Should print None because no player reached 10 points.
}