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
        VICTORY_POINT,
        ROAD_BUILDING,
        MONOPOLY,
        YEAR_OF_PLENTY,
        LARGEST_ARMY,
        LONGEST_ROAD
    };

    enum class SubCardType
    {
        ROAD_BUILDING,
        YEAR_OF_PLENTY,
        MONOPOLY,
        LARGEST_ARMY,
        LONGEST_ROAD
    };

    enum class devCardAction
    {
        GET_VICTORY_POINT,
        GET_2_FREE_ROADS,
        GET_2_FREE_RESOURCES,
        GET_MONOPOLY_RESOURCES,
        ACT_AS_ROBBER
    };



    typedef struct TradeRequest
        {
            ResourceType resourceToGive;
            ResourceType resourceToGet;
            uint amountToGive;
            uint amountToGet;
        } TradeRequest;

std::ostream& operator<<(std::ostream& os, const LandType& landType);
std::ostream& operator<<(std::ostream& os, const ResourceType& resourceType);
std::ostream& operator<<(std::ostream& os, const CardType& cardType);

}





#endif