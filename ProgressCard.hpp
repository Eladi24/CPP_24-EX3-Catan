// ID: 205739907
// Email: eladima66@gmail.com

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
            ProgressCard(CardType type, SubCardType subType): DevCard(type), _subType(subType) {}
            virtual ~ProgressCard() = default;
            SubCardType getSubType() { return _subType; }
            virtual devCardAction activate() = 0;
    };

    class YearOfPlenty: public ProgressCard
    {
        public:
            YearOfPlenty(CardType type): ProgressCard(type, SubCardType::YEAR_OF_PLENTY) {this->setAction(devCardAction::GET_2_FREE_RESOURCES);}
            ~YearOfPlenty();
            devCardAction activate() override;
    };

    class RoadBuilding: public ProgressCard
    {
        public:
            RoadBuilding(CardType type): ProgressCard(type, SubCardType::ROAD_BUILDING) {this->setAction(devCardAction::GET_2_FREE_ROADS);}
            ~RoadBuilding();
            devCardAction activate() override;
    };

    class Monopoly: public ProgressCard
    {
        public:
            Monopoly(CardType type): ProgressCard(type, SubCardType::MONOPOLY) {this->setAction(devCardAction::GET_MONOPOLY_RESOURCES);}
            ~Monopoly();
            devCardAction activate() override;
    };
}



#endif