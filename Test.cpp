// ID: 205739907
// Email: eladima66@gmail.com

#include "doctest.h"
#include "Catan.hpp"
#include <sstream>

using namespace ariel;

TEST_CASE("Playing not in turn")
{
    Player p1 = Player("p1");
    Player p2 = Player("p2");
    Player p3 = Player("p3");
    p1.setStartingPhase(false);
    p2.setStartingPhase(false);
    p3.setStartingPhase(false);
    CHECK_THROWS(p1.rollDice());
    CHECK_THROWS(p2.rollDice());
    CHECK_THROWS(p3.rollDice());
    p1.setTurn(true);
    CHECK_NOTHROW(p1.rollDice());
    CHECK_THROWS(p2.rollDice());
    CHECK_THROWS(p3.rollDice());
    p1.setTurn(false);
    p2.setTurn(true);
    CHECK_THROWS(p1.rollDice());
    CHECK_NOTHROW(p2.rollDice());
    CHECK_THROWS(p3.rollDice());
    p2.setTurn(false);
    p3.setTurn(true);
    CHECK_THROWS(p1.rollDice());
    CHECK_THROWS(p2.rollDice());
    CHECK_NOTHROW(p3.rollDice());
}

TEST_CASE("Removing too many resources")
{
    Player p1 = Player("p1");
    Cashbox c = Cashbox();
    p1.setStartingPhase(false);
    p1.setTurn(true);

    CHECK_THROWS(p1.removeResource(ResourceType::Wood, c, 3));
    CHECK_THROWS(p1.removeResource(ResourceType::Brick, c, 3));
    // Adding resources to the player
    p1.addResource(ResourceType::Wood, c, 3);
    p1.addResource(ResourceType::Brick, c, 3);
    CHECK_NOTHROW(p1.removeResource(ResourceType::Wood, c, 3));
    // Free the memory allocated in Cashbox
}

TEST_CASE("Adding too many points")
{
    Player p1 = Player("p1");
    p1.setTurn(true);
    CHECK_THROWS(p1.addVictoryPoints(100));
    CHECK_THROWS(p1.addVictoryPoints(1000));
    CHECK_NOTHROW(p1.addVictoryPoints(1));
    CHECK_THROWS(p1.addVictoryPoints(-2));
}

TEST_CASE("Removing too many points")
{
    Player p1 = Player("p1");
    p1.setTurn(true);
    CHECK_THROWS(p1.removeVictoryPoints(100));
    CHECK_THROWS(p1.removeVictoryPoints(1000));
    CHECK_NOTHROW(p1.addVictoryPoints(1));
    CHECK_NOTHROW(p1.removeVictoryPoints(1));
    CHECK_THROWS(p1.removeVictoryPoints(-2));
}

TEST_CASE("Setteling on invalid vertex")
{
    Player p1 = Player("p1");
    Board b = Board();
    Cashbox c = Cashbox();
    p1.setTurn(true);
    CHECK_THROWS(p1.placeSettelemnt({LandType::Hills, LandType::Hills}, {1, 2}, b, c));
    CHECK_THROWS(p1.placeSettelemnt({LandType::Hills, LandType::Hills}, {1, 1}, b, c));
    // Check not throwing when setteling on valid vertex
    CHECK_NOTHROW(p1.placeSettelemnt({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));

}

TEST_CASE("Placing road on invalid trail")
{
    Player p1 = Player("p1");
    Board b = Board();
    Cashbox c = Cashbox();
    p1.setTurn(true);
    CHECK_THROWS(p1.placeRoad({LandType::Hills, LandType::Hills}, {1, 2}, b, c));
    CHECK_THROWS(p1.placeRoad({LandType::Hills, LandType::Hills}, {1, 1}, b, c));
    // Check not throwing when placing road on valid trail
    CHECK_NOTHROW(p1.placeSettelemnt({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
    CHECK_NOTHROW(p1.placeRoad({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
}

TEST_CASE("Placing city on invalid vertex")
{
    Player p1 = Player("p1");
    Board b = Board();
    Cashbox c = Cashbox();
    p1.setTurn(true);
    CHECK_THROWS(p1.placeSettelemnt({LandType::Hills, LandType::Hills}, {1, 2}, b, c));
    CHECK_THROWS(p1.placeSettelemnt({LandType::Hills, LandType::Hills}, {1, 1}, b, c));
    CHECK_THROWS(p1.placeRoad({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
    // Check not throwing when placing city on valid vertex
    CHECK_NOTHROW(p1.placeSettelemnt({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
    CHECK_THROWS(p1.placeCity({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
    // Adding the required resources for building a city
    p1.addResource(ResourceType::Grain, c, 2);
    p1.addResource(ResourceType::Ore, c, 3);
    CHECK_NOTHROW(p1.placeCity({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
}

TEST_CASE("Drawing from an empty deck")
{
    Cashbox c = Cashbox();
    // Draw all the cards from the deck
    for (int i = 0; i < 25; i++)
    {
        DevCard* card = c.drawDevCard();
        delete card;
    }

    CHECK_THROWS(c.drawDevCard());

    // Draw all the cards from the deck
    for (int i = 0; i < 19; i++)
    {
        c.drawResourceCard(ResourceType::Wood);
        c.drawResourceCard(ResourceType::Brick);
        c.drawResourceCard(ResourceType::Ore);
        c.drawResourceCard(ResourceType::Wool);
        c.drawResourceCard(ResourceType::Grain);
    }

    CHECK_THROWS(c.drawResourceCard(ResourceType::Wood));
    CHECK_THROWS(c.drawResourceCard(ResourceType::Brick));
    CHECK_THROWS(c.drawResourceCard(ResourceType::Ore));
    CHECK_THROWS(c.drawResourceCard(ResourceType::Wool));
    CHECK_THROWS(c.drawResourceCard(ResourceType::Grain));
    
}

TEST_CASE("Building a road without a settlement")
{
    Player p1 = Player("p1");
    Board b = Board();
    Cashbox c = Cashbox();
    p1.setTurn(true);
    CHECK_THROWS(p1.placeRoad({LandType::Hills, LandType::Hills}, {1, 2}, b, c));
    CHECK_THROWS(p1.placeRoad({LandType::Hills, LandType::Hills}, {1, 1}, b, c));
    CHECK_THROWS(p1.placeRoad({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
    CHECK_NOTHROW(p1.placeSettelemnt({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
    CHECK_NOTHROW(p1.placeRoad({LandType::Pasture, LandType::Forest}, {2, 9}, b, c));
}

TEST_CASE("Trying to cause memory leak")
{
    Player p1 = Player("p1");
    Board b = Board();
    Cashbox c = Cashbox();
    p1.setTurn(true);
    
}




