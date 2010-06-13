#ifndef SC2REPLAY_UTIL_H
#define SC2REPLAY_UTIL_H

#include <string>
#include <sstream>
#include <iosfwd>

#include "types.h"

namespace sc2replay
{

//
// DECLARATIONS
//

    typedef std::basic_istream<char> stream;
    typedef std::pair<sc2replay::uint16_t, int> KV;

    std::string timestampToString( timestamp_t timestamp );
    uint8_t read(stream& s);
    uint16_t read2(stream& s);
    std::string readStr(stream& s);
    KV readKV(stream& s);

//
// IMPLEMENTATIONS
//

    std::string timestampToString( timestamp_t timestamp )
    {
        uint8_t seconds = (timestamp/64) % 60;
        uint8_t minutes = seconds / 60;
  
        std::ostringstream oss;
        oss << (int)minutes << ":" << (int)seconds;
  
        return oss.str();
    }

    sc2replay::uint8_t
    read(stream& s)
    {
        sc2replay::uint8_t ret = s.peek();
        s.seekg(1, std::ios::cur);
        return ret;
    }

    sc2replay::uint16_t
    read2(stream& s)
    {
        sc2replay::uint16_t ret;
        ret = read(s) << 8;
        ret += read(s);
        return ret;
    }

    std::string
    readStr(stream& s)
    {
        sc2replay::uint8_t l;
        int len = ((int)read(s))/2;
        char* buf = new char[len+1];
        s.read((buf), len);
        buf[len] = 0;

        return buf;
    }

    KV
    readKV(stream& s)
    {
        sc2replay::uint16_t key = read2(s);
        sc2replay::uint8_t tmp = read(s);
        int val(0);
        val = tmp & 0x7f;
        if ((tmp & 0x80) > 0)
        {
            val <<= 8;
            val += (int)read(s);
        }
        //std::cout << std::hex << key << " => " << val << std::endl;
        return std::make_pair(key, val);
    }

} // namespace sc2replay

#endif // SC2REPLAY_UTIL_H
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

