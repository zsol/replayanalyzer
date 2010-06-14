#ifndef SC2REPLAY_PLAYER_H
#define SC2REPLAY_PLAYER_H

#include <string>
#include <map>
#include <vector>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include "types.h"

#include <ostream>

namespace sc2replay
{
    struct Player
    {
        explicit Player(const std::string& sn = "", const std::string& r = "", 
                        const std::string& fn = "")
            : shortName_(sn), fullName_(fn), race_(r)
        {}

        const std::string& getShortName() const { return shortName_; }
        const std::string& getFullName() const { return fullName_; }
        const std::string& getRace() const { return race_; }

        bool operator==(const Player& o) const { return shortName_ == o.shortName_; }

        bool operator!() const { return isValid(); }
        bool isValid() const { return shortName_.size() && fullName_.size() && race_.size(); }

        std::string shortName_;
        std::string fullName_;
        std::string race_;

        typedef std::vector<std::pair<uint8_t, int> > attributes_type;
        attributes_type attributes_;

        friend std::ostream&
        operator<<(std::ostream& out, const sc2replay::Player& p)
            {
                out << p.shortName_;
                return out;
            }

    };
}


BOOST_FUSION_ADAPT_STRUCT(
    sc2replay::Player,
    (std::string, shortName_)
    (std::string, fullName_)
    (std::string, race_)
    (sc2replay::Player::attributes_type, attributes_))

#endif
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

