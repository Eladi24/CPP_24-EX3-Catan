#include <random>
#include "Catan.hpp"

using namespace std;
using namespace ariel;

Catan::~Catan()
{
    delete _p1;
    delete _p2;
    delete _p3;

}

void Catan::ChooseStartingPlayer() {
    int p1Roll = 0;
    int p2Roll = 0;
    int p3Roll = 0;
    cout << "Orginal p1:" << _p1->getName() << endl;
    cout << "Orginal p2:" << _p2->getName() << endl;
    cout << "Orginal p3:" << _p3->getName() << endl;
    // Roll the dice until we get unique values
    while (p1Roll == p2Roll || p1Roll == p3Roll || p2Roll == p3Roll) {
        p1Roll = _p1->rollDice();
        p2Roll = _p2->rollDice();
        p3Roll = _p3->rollDice();
    }

    // Determine the order of players based on their rolls
    //Case 1: p1 has the highest roll
    
    if (p1Roll > p2Roll && p1Roll > p3Roll) {

        // The playing order is already correct: p1, p2, p3
        if (p2Roll > p3Roll) {
            _currentPlayerIndex = 0;
        // The playing order is p1, p3, p2    
        } else {
            // swapPlayers(_p2, _p3);
            std::swap(_p2, _p3);
            _currentPlayerIndex = 0;
        }

    //Case 2: p2 has the highest roll
    } else if (p2Roll > p1Roll && p2Roll > p3Roll) {
        // swapPlayers(_p1, _p2);
        std::swap(_p1, _p2);
        // The playing order is already correct: p2, p3, p1
        if (p1Roll < p3Roll) {
            // swapPlayers(_p2, _p3);
            std::swap(_p2, _p3);
        }
        _currentPlayerIndex = 1;

    //Case 3: p3 has the highest roll
    } else {
        // swapPlayers(_p1, _p3);
        std::swap(_p1, _p3);
        // The playing order is: p3, p2, p1
        if (p1Roll > p2Roll) {
            // swapPlayers(_p2, _p3);
            std::swap(_p2, _p3);
        }
        _currentPlayerIndex = 2;
    }

    _p1->setTurn(true);
    cout << "The starting player is: " << _p1->getName() << endl;
    cout << "The second player is: " << _p2->getName() << endl;
    cout << "The third player is: " << _p3->getName() << endl;
}


Player &Catan::checkWinner()
{
    if (_p1->getVictoryPoints() >= 10 && _p2->getVictoryPoints() < 10 && _p3->getVictoryPoints() < 10)
    {
        _gamePhase = END;
        return *_p1;
    }
    else if (_p2->getVictoryPoints() >= 10 && _p1->getVictoryPoints() < 10 && _p3->getVictoryPoints() < 10)
    {
        _gamePhase = END;
        return *_p2;
    }
    else if (_p3->getVictoryPoints() >= 10 && _p1->getVictoryPoints() < 10 && _p2->getVictoryPoints() < 10)
    {
        _gamePhase = END;
        return *_p3;
    }

    else
    {
        _gamePhase = PLAY;
        throw invalid_argument("No winner yet");
    }
}

void Catan::printWinner()
{
    try
    {
        Player &winner = checkWinner();
        cout << "The winner is: " << winner.getName() << endl;
    }
    catch (const invalid_argument &e)
    {
        cout << e.what() << endl;
    }
}

void Catan::changeTurn()
{
    if (_currentPlayerIndex == 2)
    {
        _currentPlayerIndex = 0;
    }
    else
    {
        _currentPlayerIndex++;
    }
}

void Catan::yieldResources(int diceRoll)
{
    // If the dice roll is < 0, the setup phase has ended and each player should yield resources from their structures
    if (diceRoll < 0)
    {
        for (const auto &[key, hex] : _board.getHexagonsMap())
        {
            for (const auto &[vertexKey, vertex] : hex->getVerticesMap())
            {
                if ((vertex.lock())->getStructure() != nullptr && hex->getResourceType() != ResourceType::None)
                {
                    (vertex.lock())->yieldResources(hex->getResourceType(), _cashbox);
                }
            }
        }
        return;
    }

    for (const auto &[key, hex] : _board.getHexagonsMap())
    {
        if (hex->getValue() == diceRoll && !hex->hasRobber())
        {
            for (const auto &[vertexKey, vertex] : hex->getVerticesMap())
            {
                if ((vertex.lock())->getStructure() != nullptr && hex->getResourceType() != ResourceType::None)
                {
                    (vertex.lock())->yieldResources(hex->getResourceType(), _cashbox);
                }
            }
        }
        else if(hex->hasRobber() && hex->getValue() == diceRoll)
        {
            for (const auto &[vertexKey, vertex] : hex->getVerticesMap())
            {
                if ((vertex.lock())->getStructure() != nullptr)
                {
                    cout << "Player: " << (vertex.lock())->getStructure()->getOwner()->getName() << 
                    "Does not get resources because the robber is on the hexagon" << endl;
                }
            }
        }
    }
}

void Catan::setGamePhase(GamePhase gamePhase)
{
    _gamePhase = gamePhase;

    switch (_gamePhase)
    {
    case SETUP:

        cout << "Game phase is: SETUP" << endl;
        break;
    case PLAY:
        cout << "Game phase is: PLAY" << endl;
        this->yieldResources(-1);
        _p1->setStartingPhase(false);
        _p2->setStartingPhase(false);
        _p3->setStartingPhase(false);
        break;
    case END:
        cout << "Game phase is: END" << endl;
        break;
    }
}


void Catan::swapPlayers(Player*& p1, Player*& p2)
{
    Player* temp = p1;
    p1 = p2;
    p2 = temp;
}

void Catan::turnCycleChange()
{
    if(_p1->getIsTurn() == true)
    {
        _p1->setTurn(false);
        _p2->setTurn(true);
    }
    else if(_p2->getIsTurn() == true)
    {
        _p2->setTurn(false);
        _p3->setTurn(true);
    }
    else
    {
        _p3->setTurn(false);
        _p1->setTurn(true);
    }
}

void Catan::analyzeDiceRoll(int roll_sum, Player*& currentPlayer)
{
    // If the dice roll is 7, the robber is activated and the player should move the robber to a new hexagon
    if (roll_sum == 7)
    {
        cout << "Player: " << currentPlayer->getName() << " rolled a 7" << endl;
        try {
            currentPlayer->moveRobber(_board);
        }
        catch (const invalid_argument &e)
        {
            cout << e.what() << endl;
        }
        
        shared_ptr<Hexagon> robberHex = _board.getRobberHexagon();
        vector<Player*> otherPlayers;
        if(currentPlayer != _p1) otherPlayers.push_back(_p1);
        if(currentPlayer != _p2) otherPlayers.push_back(_p2);
        if(currentPlayer != _p3) otherPlayers.push_back(_p3);
        if (otherPlayers.size() == 3 || otherPlayers.empty())
        {
            throw invalid_argument("Invalid number of players to steal from");
        }
        // Randomly select one of the other players
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, otherPlayers.size() - 1);
        int randomIndex = dis(gen);
        Player* playerToStealFrom = otherPlayers[randomIndex];
        try {
            playerToStealFrom->stealResource(currentPlayer, robberHex->getResourceType());
        }
        catch (const invalid_argument &e)
        {
            cout << e.what() << endl;
        }

        
    }
    else
    {
        // Yield resources to the players based on the dice roll
        this->yieldResources(roll_sum);

        // Check if a one of the players has the longest road or largest army
        vector<Player*> players = {_p1, _p2, _p3};
        if(!_cashbox.getLongestRoadHolder())
        {
            
            for (auto &player : players)
            {
                if (player->countSequenceRoads() >= 5)
                {
                    player->setLongestRoadHolder();
                    _cashbox.setLongestRoadHolder(player);
                    cout << "Player: " << player->getName() << " has the longest road" << endl;
                    break;
                }
            }
        } else {
            
            for (auto &player : players)
            {
                if (player->countSequenceRoads() > _cashbox.getLongestRoadHolder()->countSequenceRoads())
                {   
                    cout << "Player: " << _cashbox.getLongestRoadHolder()->getName() << " no longer has the longest road" << endl;
                    _cashbox.getLongestRoadHolder()->takeLongestRoadCard();
                    _cashbox.setLongestRoadHolder(nullptr);
                    _cashbox.setLongestRoadHolder(player);
                    cout << "Player: " << player->getName() << " has the longest road" << endl;
                }
            }
        }

        if(!_cashbox.getLargestArmyHolder())
        {
            for (auto &player : players)
            {
                if (player->countKnightCards() >= 3)
                {
                    player->setLargestArmyHolder();
                    _cashbox.setLargestArmyHolder(player);
                    cout << "Player: " << player->getName() << " has the largest army" << endl;
                    break;
                }
            }
        } else {
            for (auto &player : players)
            {
                if (player->countKnightCards() > _cashbox.getLargestArmyHolder()->countKnightCards())
                {
                    cout << "Player: " << _cashbox.getLargestArmyHolder()->getName() << " no longer has the largest army" << endl;
                    _cashbox.getLargestArmyHolder()->takeLargestArmyCard();
                    _cashbox.setLargestArmyHolder(nullptr);
                    _cashbox.setLargestArmyHolder(player);
                    cout << "Player: " << player->getName() << " has the largest army" << endl;
                }
            }
        }
    }
    // Check if a player has won the game
    try
    {
        checkWinner();
    }
    catch (const invalid_argument &e)
    {
        cout << e.what() << endl;
    }
}