#ifndef _CASHBOX_HPP_
#define _CASHBOX_HPP_

#include <map>
#include <string>
#include <vector>
#include <memory>
#include "DevCard.hpp"
#include "Player.hpp"



using namespace std;

namespace ariel
{
    class Player;
    class DevCard;

    class Cashbox
    {
        private:
            // A deck of development cards
            vector<DevCard*> devCards;
            // A deck of resource cards
            vector<ResourceCard> woodCards;
            vector<ResourceCard> brickCards;
            vector<ResourceCard> oreCards;
            vector<ResourceCard> woolCards;
            vector<ResourceCard> grainCards;

            Player* _largestArmyHolder;
            Player* _longestRoadHolder;
            
        
        public:
            // Constructor
            // Cashbox(): devCards(25), woodCards(19), brickCards(19), oreCards(19), woolCards(19), grainCards(19) {}
            Cashbox();
            // Destructor
            ~Cashbox();

            // Cashbox initialization
            void init();
            // Draw a development card
            DevCard* drawDevCard();
            // Draw a resource card
            ResourceCard drawResourceCard(ResourceType type);
            // Return a resource card to the deck
            void returnResourceCard(ResourceCard card);
            // Return a development card to the deck
            void returnDevCard(DevCard* card);
            // Get the number of resource cards in the deck
            int getNumResourceCards(ResourceType type);
            // Get the number of development cards in the deck
            int getNumDevCards() { return devCards.size();}
            // Loan a resource card to a player with a 4:1 trade
            void loanResourceCard(Player* p, ResourceCard cardToGive, ResourceType cardToGet);
            // Shuffle the development cards
            void shuffleDevCards();
            // Shuffle the resource cardss
            void shuffleResourceCards();

            bool canAffordDevCard(Player& p);

            CardType peekDeck();
            void printDeck();

            void setLargestArmyHolder(Player* p);
            void setLongestRoadHolder(Player* p);
             
        
            
    };
}



#endif