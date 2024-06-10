#ifndef _LAND_HPP_
#define _LAND_HPP_

using namespace std;
namespace ariel
{
    enum LandType
    {
        Forest,
        Hills,
        Mountains,
        Pasture,
        Field,
        Desert
    };

    enum ResourceType
    {
        Wood,
        Brick,
        Ore,
        Wool,
        Grain
    };

    class Land
    {
        private:
            LandType _landType;
            ResourceType _resourceType;
            int _value;
            int id;
            array<Vertex, 6> _vertices;
            array<Trail, 6> _edges;

            
        public:
            Land(LandType landType, int value, int id);

            ~Land();
            ResourceType getType();
            int getValue();
            void setValue(int value);
            
    };

} // namespace ariel








#endif