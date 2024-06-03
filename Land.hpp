#ifndef _LAND_HPP_
#define _LAND_HPP_

namespace ariel
{
    enum ResourceType
    {
        Forest,
        Hills,
        Mountains,
        Pasture,
        Field,
        Desert
    };

    class Land
    {
        private:
            ResourceType _type;
            int _value;
            bool _hasRobber;
        public:
            Land(ResourceType type, int value);
            Land(ResourceType type, int value, bool hasRobber);
            ~Land();
            ResourceType getType();
            int getValue();
            bool hasRobber();
            void setRobber(bool hasRobber);
    };

} // namespace ariel








#endif