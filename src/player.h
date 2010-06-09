#ifndef SC2REPLAY_PLAYER_H
#define SC2REPLAY_PLAYER_H

#include <string>

namespace sc2replay
{
    class Player
    {
    public:
        Player(const std::string& sn, const std::string& r, const std::string& fn)
            : shortName_(sn), fullName_(fn), race_(r)
        {}

        const std::string& getShortName() const { return shortName_; }
        const std::string& getFullName() const { return fullName_; }
        const std::string& getRace() const { return race_; }

        bool operator==(const Player& o) const { return shortName_ == o.shortName_; }

    private:
        std::string shortName_;
        std::string fullName_;
        std::string race_;
    };
}

#endif
// Local Variables:
// mode:c++
// c-file-style:stroustrup
// end:

