// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _KNIGHTCARD_HPP_
#define _KNIGHTCARD_HPP_

#include "DevCard.hpp"


namespace ariel
{
    class KnightCard: public DevCard
    {
    public:
        KnightCard(): DevCard(CardType::KNIGHT) { _action = devCardAction::ACT_AS_ROBBER; }
        ~KnightCard();
        devCardAction activate() override;
    };
}





#endif