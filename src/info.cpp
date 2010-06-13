#include "info.h"
#include "types.h"
#include "valueparser.h"

#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/home/qi/nonterminal/debug_handler.hpp>

#include <fstream>
#include <iostream>

using namespace boost::spirit::qi;
using namespace boost::phoenix;


namespace sc2replay
{

    
    Info::Info()
    {

        string = 
            byte_[_a = _1/2] > repeat(_a)[char_];
        value = 
            (&byte_[if_(0<(_1 & 0xc0))[_pass=false]] >> byte_[_val = static_cast_<int>(_1)]) |
            little_word[_val = static_cast_<int>(_1) >> 2];


        kv = 
            word >> value;
        player = 
            omit[byte_(0x5) >> byte_(0x12) >> byte_(0x0) >> byte_(0x2)] >>
            string >> omit[byte_(0x2) >> byte_(0x5) >> byte_(0x8)] >> omit[kv] >> 
            omit[repeat(6)[byte_]] >> omit[kv] >> omit[byte_(0x6) >> byte_(0x2)] >>
            string >> omit[byte_(0x4) >> byte_(0x2)] >>
            string >> omit[byte_(0x6) >> byte_(0x5) >> byte_(0x8)] >>
            repeat(9)[kv];

        player.name("player");
        kv.name("KeyValue");
        value.name("value");
        string.name("string");

        on_error<fail>(string,
                       std::cout << val("Error! Expecting ")
                       << _4 << val(" here: \"") << _3 << 
                       val("\" from: ") << _1 << std::endl
            );
        debug(string);
    }

    Info::~Info()
    {
    }

    void
    Info::load(const uint8_t* begin, const uint8_t* end)
    {
        // parse(begin, end,
        //       omit[repeat(7)[byte_]] >> *player,
        //       players_);
        std::string asd;
        parse(begin, end,
              omit[repeat(0xa9)[byte_]] >> string,
              asd);
        std::cout << asd << std::endl;
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

