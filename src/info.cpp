#include "info.h"
#include "types.h"

#include <boost/spirit/include/phoenix.hpp>

#include <fstream>


using namespace boost::spirit::qi;

namespace sc2replay
{

    const Info::string_rule_type Info::string = 
        byte_[_a = _1] >> repeat(_a/2)[char_[_val += _1]];
    const Info::value_rule_type Info::value = 
        (&byte_[if_(0==(_1 & 0x80))[_pass=false]] >> big_word[_val = _1 & 0x7fff]) | byte_;
    const Info::kv_rule_type Info::kv = 
        big_word >> Info::value;
    const Info::player_rule_type Info::player = 
        omit[byte_(0x5) >> byte_(0x12) >> byte_(0x0) >> byte_(0x2)] >>
        string >> omit[byte_(0x2) >> byte_(0x5) >> byte_(0x8)] >> omit[kv] >> 
        omit[repeat(6)[byte_]] >> omit[kv] >> omit[byte_(0x6) >> byte_(0x2)] >>
        string >> omit[byte_(0x4) >> byte_(0x2)] >> 
        string >> omit[byte_(0x6) >> byte_(0x5) >> byte_(0x8)] >>
        omit[repeat(9)[kv]];

    Info::Info()
    {
  
    }

    Info::~Info()
    {
    }

    void
    Info::load(const uint8_t* begin, const uint8_t* end)
    {
        parse(begin, end,
              omit[repeat(0x3f)[byte_]] >> *player,
              players_);
    }

    const Info::Players& Info::getPlayers() const
    {
        return players_;
    }

    const uint8_t Info::getNumberOfPlayers() const
    {
        return players_.size();
    }

    const std::string& Info::getMapFilename() const
    {
        return mapFilename_;
    }

    const std::string& Info::getMapName() const
    {
        return mapName_;
    }

    void Info::exportDump( const std::string& filename ) const
    {
        std::ofstream file( filename.c_str(), std::ios::binary );
        //TODO file.write( (const char*)buffer_, bufferSize_ );
        file.close();
    }
}

// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

