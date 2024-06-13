#ifndef _PROGRESSCARD_HPP_
#define _PROGRESSCARD_HPP_

#include "DevCard.hpp"


namespace ariel
{
    class ProgressCard: public DevCard
    {
        private:
            // The type of the progress card
            SubCardType _subType;

    public:
        ProgressCard(CardType type, string name, int cost, SubCardType subType): DevCard(type, name, cost), _subType(subType) {}
        ~ProgressCard();
        void activate() override;
    };
}



#endif