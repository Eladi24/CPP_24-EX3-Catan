#ifndef _KNIGHTCARD_HPP_
#define _KNIGHTCARD_HPP_

#include "DevCard.hpp"


namespace ariel
{
    class KnightCard: public DevCard
    {
    public:
        KnightCard(): DevCard(CardType::KNIGHT, 3) {}
        ~KnightCard();
        void activate() override;
    };
}





#endif