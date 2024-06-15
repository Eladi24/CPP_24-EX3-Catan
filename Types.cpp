#include "Types.hpp"


namespace ariel
{
    std::ostream& operator<<(std::ostream& os, const LandType& landType)
{
    switch (landType)
    {
        case LandType::Forest:
            os << "Forest";
            break;
        case LandType::Hills:
            os << "Hills";
            break;
        case LandType::Mountains:
            os << "Mountains";
            break;
        case LandType::Pasture:
            os << "Pasture";
            break;
        case LandType::Field:
            os << "Field";
            break;
        case LandType::Desert:
            os << "Desert";
            break;
        case LandType::None:
            os << "None";
            break;
        case LandType::Sea:
            os << "Sea";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const ResourceType& resourceType)
{
    switch (resourceType)
    {
        case ResourceType::Wood:
            os << "Wood";
            break;
        case ResourceType::Brick:
            os << "Brick";
            break;
        case ResourceType::Ore:
            os << "Ore";
            break;
        case ResourceType::Wool:
            os << "Wool";
            break;
        case ResourceType::Grain:
            os << "Grain";
            break;
        case ResourceType::None:
            os << "None";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CardType& cardType)
{
    switch (cardType)
    {
        case CardType::KNIGHT:
            os << "Knight";
            break;
        case CardType::VICTORY_POINT:
            os << "VictoryPoint";
            break;
        case CardType::PROGRESS:
            os << "Progress";
            break;
    }
    return os;
}
}
