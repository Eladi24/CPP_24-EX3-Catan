// ID: 205739907
// Email: eladima66@gmail.com

#ifndef _DIE_HPP_
#define _DIE_HPP_
#include <cstdlib>
#include <ctime>

namespace ariel
{
    class Die
    {
    public:
        Die() { 
            srand(static_cast<unsigned int>(time(nullptr)));
        }
        int roll() {
            return 1 + rand() % 6;}
    };
} // namespace ariel




#endif