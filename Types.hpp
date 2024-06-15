#ifndef _TYPES_HPP_
#define _TYPES_HPP_
#include <iostream>
#include <string>

namespace ariel
{
     enum class LandType
    {
        Forest,
        Hills,
        Mountains,
        Pasture,
        Field,
        Desert,
        None,
        Sea
    };
    
    enum class ResourceType
    {
        Wood,
        Brick,
        Ore,
        Wool,
        Grain,
        None
    };

    typedef struct ResourceCard
    {
        ResourceType type;
        bool available;
    } ResourceCard;

    enum class CardType
    {
        KNIGHT,
        PROGRESS,
        VICTORY_POINT
    };

    enum class SubCardType
    {
        ROAD_BUILDING,
        YEAR_OF_PLENTY,
        MONOPOLY,
        LARGEST_ARMY,
        LONGEST_ROAD
    };

    typedef struct TradeRequest
        {
            ResourceType resourceToGive;
            ResourceType resourceToGet;
            int amountToGive;
            int amountToGet;
        } TradeRequest;

std::ostream& operator<<(std::ostream& os, const LandType& landType);
std::ostream& operator<<(std::ostream& os, const ResourceType& resourceType);
std::ostream& operator<<(std::ostream& os, const CardType& cardType);

}





#endif