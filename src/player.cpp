#include "player.h"
#include "util.h"

#include <sstream>
#include <string>

namespace
{
    void
    color(const sc2replay::Player::attributes_type& attributes_,
          int& r, int& g, int& b)
    {
        for (sc2replay::Player::attributes_type::const_iterator it = attributes_.begin();
             it != attributes_.end(); ++it)
        {
            switch(it->first)
            {
            case 0x2:
                r=it->second;
                break;
            case 0x4:
                g=it->second;
                break;
            case 0x6:
                b=it->second;
                break;
            }
        }
    }

    std::string toString( int a_, int b_, int c_ )
    {
        std::ostringstream oss;
        oss << std::hex << a_ << b_ << c_;
        return oss.str();
    }



}

namespace sc2replay
{
    int
    Player::team() const
    {
        for (attributes_type::const_iterator it = attributes_.begin();
             it != attributes_.end(); ++it)
        {
            if (it->first == 0x10)
                return it->second/2;
        }
        return 0;
    }

    int
    Player::color() const
    {
        int r=0, g=0, b=0;

        ::color(attributes_, r,g,b);

        return r << 16 + g << 8 + b;
    }

    std::string
    Player::colorAsString() const
    {
        int r=0, g=0, b=0;
        ::color(attributes_,r,g,b);
        return ::toString(r,g,b);
    }
}
