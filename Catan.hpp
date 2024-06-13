#ifndef _CATAN_HPP_
#define _CATAN_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <map>



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
        int _turnCounter;
        int _currentPlayerIndex;

        enum GamePhase
        {
            SETUP,
            PLAY,
            END
        }_gamePhase;    
        
    public:
        Catan(Player p1, Player p2, Player p3);
        ~Catan();
        void ChooseStartingPlayer();
        Board getBoard();
        void printWinner();
        void checkWinner();
        void changeTurn();
    };
} // namespace ariel


#endif