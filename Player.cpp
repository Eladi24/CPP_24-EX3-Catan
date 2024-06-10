#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Settlement.hpp"
#include "Point.hpp"

using namespace std;
using namespace ariel;

Player::Player(const string name): _name(name), _victoryPoints(0), _isTurn(false) {}

Player::~Player() {}

void Player::rollDice() {
    int sum = _die1.roll() + _die2.roll();
}

bool Player::trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, int amountToGive, int amountToGet) {
    TradeRequest request = {*this, resourceToGive, resourceToGet, amountToGive, amountToGet};
    if (pToTrade.reviewTradeRequest(request) == true)
    {
        
    }
}

bool Player::reviewTradeRequest(TradeRequest tradeRequest) {
    if (tradeRequest.amountToGive > _resources[tradeRequest.resourceToGive]) {
        return false;
    }
    if (tradeRequest.amountToGet > _resources[tradeRequest.resourceToGet]) {
        return false;
    }
    // if the player agrees to the trade, the resources are exchanged.
    _resources[tradeRequest.resourceToGive] -= tradeRequest.amountToGive;
    _resources[tradeRequest.resourceToGet] += tradeRequest.amountToGet;
    return true;
}

void Player::addResource(ResourceType resource, int amount)
{
    this->_resources[resource] += amount;
}

void Player::removeResource(ResourceType resource, int amount)
{
    if (this->_resources[resource] == 0 || this->_resources[resource] < amount)
    {
        throw new invalid_argument("Player does not have enough resources to remove");
    }
    this->_resources[resource] -= amount;
}


void Player::printPoints()
{
    cout << "Player " << this->_name << " has " << this->_victoryPoints << " points." << endl;
}

string Player::getName()
{
    return this->_name;
}




