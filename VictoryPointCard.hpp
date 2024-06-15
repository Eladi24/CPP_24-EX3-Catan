#ifndef _VICTORYPOINTCARD_HPP_
#define _VICTORYPOINTCARD_HPP_

#include "DevCard.hpp"


namespace ariel
{
    class VictoryPointCard: public DevCard
    {
    public:
        VictoryPointCard(): DevCard(CardType::VICTORY_POINT,  1) {}
        ~VictoryPointCard();
        void activate() override;
    };
}






#endif