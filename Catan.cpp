#include "Catan.hpp"

using namespace std;
using namespace ariel;

Catan::~Catan()
{
}

void Catan::ChooseStartingPlayer()
{
    int p1Roll = 0;
    int p2Roll = 0;
    int p3Roll = 0;
    while (p1Roll == p2Roll && p1Roll == p3Roll && p2Roll == p3Roll)
    {
        p1Roll = _p1.rollDice();
        p2Roll = _p2.rollDice();
        p3Roll = _p3.rollDice();
    }

    // _p1.setStartingPhase(false);
    // _p2.setStartingPhase(false);
    // _p3.setStartingPhase(false);

    if (p1Roll > p2Roll && p1Roll > p3Roll)
    {
        _currentPlayerIndex = 0;

        _p1.setTurn(true);
        cout << "The starting player is: " << _p1.getName() << endl;
    }

    else if (p2Roll > p1Roll && p2Roll > p3Roll)
    {
        _currentPlayerIndex = 1;
        _p2.setTurn(true);
        cout << "The starting player is: " << _p2.getName() << endl;
    }

    else
    {
        _currentPlayerIndex = 2;
        _p3.setTurn(true);
        cout << "The starting player is: " << _p3.getName() << endl;
    }
}

Player &Catan::checkWinner()
{
    if (_p1.getVictoryPoints() >= 10 && _p2.getVictoryPoints() < 10 && _p3.getVictoryPoints() < 10)
    {
        _gamePhase = END;
        return _p1;
    }
    else if (_p2.getVictoryPoints() >= 10 && _p1.getVictoryPoints() < 10 && _p3.getVictoryPoints() < 10)
    {
        _gamePhase = END;
        return _p2;
    }
    else if (_p3.getVictoryPoints() >= 10 && _p1.getVictoryPoints() < 10 && _p2.getVictoryPoints() < 10)
    {
        _gamePhase = END;
        return _p3;
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

    for (const auto &[key, hex] : _board.getHexagonsMap())
    {
        if (hex->getValue() == diceRoll)
        {
            for (const auto &[vertexKey, vertex] : hex->getVerticesMap())
            {
                if (vertex->getStructure() != nullptr)
                {
                    vertex->yieldResources(hex->getResourceType(), _cashbox);
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
        _p1.setStartingPhase(false);
        _p2.setStartingPhase(false);
        _p3.setStartingPhase(false);
        break;
    case END:
        cout << "Game phase is: END" << endl;
        break;
    }
}
