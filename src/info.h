#ifndef SC2REPLAY_INFO_H
#define SC2REPLAY_INFO_H

#include "types.h"
#include "player.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>


#include <iosfwd>
#include <string>
#include <vector>

namespace sc2replay
{

    class Info
    {
    public:
        enum GameSpeed
        {
            SLOWER = 0x00,
            SLOW   = 0x01,
            NORMAL = 0x02,
            FAST   = 0x03,
            FASTER = 0x04
        };
  
    public:
        typedef std::vector<Player>   Players;
  
    public:
        Info();
        ~Info();
  
    public:
        void load(const uint8_t* begin, off_t len) { load(begin, begin+len/sizeof(uint8_t)); }
        void load(const uint8_t* begin, const uint8_t* end);
  
    public:
        const Players& getPlayers() const;
        const uint8_t getNumberOfPlayers() const;
        const std::string& getMapFilename() const;
        const std::string& getMapName() const;
  
    public:
        void exportDump( const std::string& filename ) const;
  
    private:
        template <typename T>
        bool readPlayer(std::basic_istream<T>& s);
    private:
        Players players_;
        std::string mapFilename_;
        std::string mapName_;


        typedef boost::spirit::qi::rule<const uint8_t*, 
                                        boost::spirit::qi::locals<int>, 
                                        std::string() > string_rule_type;

        typedef boost::spirit::qi::rule<const uint8_t*, 
                                        int()> value_rule_type;

        typedef boost::spirit::qi::rule<const uint8_t*, 
                                        std::pair<sc2replay::uint16_t, 
                                                  int>()> kv_rule_type;

        typedef boost::spirit::qi::rule<const uint8_t*, 
                                        sc2replay::Player()> player_rule_type;

        static const string_rule_type string;
        static const value_rule_type value;
        static const kv_rule_type kv;
        static const player_rule_type player;
    };

} // namespace sc2replay

#endif // SC2REPLAY_INFO_H
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

