#include <iostream>
#include <vector>
#include "Player.hpp"


using namespace std;
using namespace ariel;

Player::~Player() {}

void Player::rollDice() {
    int sum = _die1.roll() + _die2.roll();
}

bool Player::trade(Player pToTrade, ResourceType resourceToGive, ResourceType resourceToGet, int amountToGive, int amountToGet) {
    TradeRequest request = {resourceToGive, resourceToGet, amountToGive, amountToGet};
    if (pToTrade.reviewTradeRequest(request) == true)
    {
        this->_resources[resourceToGive] -= amountToGive;
        this->_resources[resourceToGet] += amountToGet;
        pToTrade._resources[resourceToGive] += amountToGive;
        pToTrade._resources[resourceToGet] -= amountToGet;
        return true;
    }
    return false;
}

bool Player::reviewTradeRequest(TradeRequest tradeRequest) {
    if (tradeRequest.amountToGive > _resources[tradeRequest.resourceToGive]) {
        return false;
    }
    if (tradeRequest.amountToGet > _resources[tradeRequest.resourceToGet]) {
        return false;
    }
    
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




