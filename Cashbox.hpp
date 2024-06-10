#ifndef _CASHBOX_HPP_
#define _CASHBOX_HPP_

#include <map>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Land.hpp"
using namespace std;

namespace ariel
{
    class Cashbox
    {
        private:
            // A deck of development cards
            vector<DevCard> devCards;
            // A deck of resource cards
            vector<ResourceType> woodCards;
            vector<ResourceType> brickCards;
            vector<ResourceType> oreCards;
            vector<ResourceType> woolCards;
            vector<ResourceType> grainCards;
        
        public:
            // Constructor
            Cashbox();
            // Destructor
            ~Cashbox();
            // Draw a development card
            DevCard drawDevCard();
            // Draw a resource card
            ResourceType drawResourceCard();
            // Return a resource card to the deck
            void returnResourceCard(ResourceType card);
            // Return a development card to the deck
            void returnDevCard(DevCard card);
            // Get the number of resource cards in the deck
            int getNumResourceCards();
            // Get the number of development cards in the deck
            int getNumDevCards();
            // Loan a resource card to a player with a 4:1 trade
            void loanResourceCard(Player* p, ResourceType card);
        
            
    };
}



#endif