#ifndef _CATAN_HPP_
#define _CATAN_HPP_

#include "Types.hpp"
#include "Player.hpp"
namespace ariel
{
    enum GamePhase
        {
            SETUP,
            PLAY,
            END
        };

    class Catan
    {
    private:
        Player*& _p1;
        Player*& _p2;
        Player*& _p3;
        Board _board;
        Cashbox _cashbox;
        Die _die1;
        Die _die2;
        int _turnCounter; 
        int _currentPlayerIndex;
        int roundCounter;
        GamePhase _gamePhase;
        
        Player& checkWinner();
        


            
        
    public:
        Catan(Player*& p1, Player*& p2, Player*& p3): _p1(p1), _p2(p2), _p3(p3), _board(), _cashbox(), _turnCounter(0), _currentPlayerIndex(0), roundCounter(0), _gamePhase(SETUP) {}
        
        ~Catan();
        /*
        * @brief
        * This function is responsible for choosing the starting player
        * The order of the players is determined by the sum of the dice roll
        */
        void ChooseStartingPlayer();

        Board& getBoard() { return _board; }

        Cashbox& getCashbox() { return _cashbox; }

        /*
        * @brief
        * This function is responsible for printing the winner of the game
        * If there is no winner yet, it will print "No winner yet"
        */
        void printWinner();
        void changeTurn();
        /*
        * @brief
        * This function is responsible for yielding resources to the players
        * It iterates over the vertices and yields resources with matching numbers to the dice roll
        */
        void yieldResources(int diceRoll);
        /*
        * @brief
        * This function is responsible for setting the game phase
        * @param gamePhase The game phase to set
        */
        void setGamePhase(GamePhase gamePhase);

        void swapPlayers(Player*& p1, Player*& p2);
        /*
        * @brief
        * This function is responsible for changing the turn of the players
        */
        void turnCycleChange();

        /*
        * @brief
        * This function is responsible for analyzing the dice roll
        * It yields resources to the players and checks if a player has won
        * @param roll_sum The sum of the dice roll
        * @param currentPlayer The current player
        */
        void analyzeDiceRoll(int roll_sum, Player*& currentPlayer); 

        


    };
} // namespace ariel


#endif