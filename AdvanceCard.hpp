#ifndef _ADVANCECARD_HPP_
#define _ADVANCECARD_HPP_

#include <iostream>
#include <vector>
#include "DevCard.hpp"
namespace ariel
{
    class AdvanceCard: public DevCard
    {
    private:
        std::string type;
        std::string name;
        std::string description;
        int value;

    public:
        AdvanceCard(std::string type, std::string name, std::string description, int value);
        ~AdvanceCard();
    };
} // namespace ariel


#endif