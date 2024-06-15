#ifndef _CATAN_HPP_
#define _CATAN_HPP_

#include "Types.hpp"
#include "Player.hpp"
namespace ariel
{
    class Catan
    {
    private:
        Player _p1;
        Player _p2;
        Player _p3;
        Board _board;
        Cashbox _cashbox;
        Die _die1;
        Die _die2;
        int _turnCounter; 
        int _currentPlayerIndex;
        int roundCounter;
        
        Player& checkWinner();


        enum GamePhase
        {
            SETUP,
            PLAY,
            END
        }_gamePhase;    
        
    public:
        Catan(Player p1, Player p2, Player p3): _p1(p1), _p2(p2), _p3(p3), _board(), _cashbox(), _turnCounter(0), _currentPlayerIndex(0), roundCounter(0), _gamePhase(SETUP) {}
        ~Catan();
        
        void ChooseStartingPlayer();
        Board& getBoard() { return _board; }
        Cashbox& getCashbox() { return _cashbox; }
        void printWinner();
        void changeTurn();
        void yieldResources(int diceRoll);
        
        


    };
} // namespace ariel


#endif