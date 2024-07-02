// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _VICTORYPOINTCARD_HPP_
#define _VICTORYPOINTCARD_HPP_

#include "DevCard.hpp"


namespace ariel
{
    class VictoryPointCard: public DevCard
    {
    public:
        VictoryPointCard(): DevCard(CardType::VICTORY_POINT) { _action = devCardAction::GET_VICTORY_POINT; }
        ~VictoryPointCard();
        devCardAction activate() override;
    };
}






#endif