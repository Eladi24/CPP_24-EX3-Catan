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



