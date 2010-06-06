#include "info.h"
#include "types.h"

#include <fstream>

namespace {

    sc2replay::uint8_t
    read(std::istream& s)
    {
        sc2replay::uint8_t ret = s.peek();
        s.seekg(1, std::ios::cur);
        return ret;
    }

    sc2replay::uint16_t
    read2(std::istream& s)
    {
        sc2replay::uint16_t ret;
        ret = read(s) << 8;
        ret += read(s);
        return ret;
    }

    std::string
    readStr(std::istream& s)
    {
        sc2replay::uint8_t l;
        int len = ((int)read(s))/2;
        char* buf = new char[len+1];
        s.read(buf, len);
        buf[len] = 0;

        return buf;
    }

    typedef std::pair<sc2replay::uint16_t, int> KV;

    KV
    readKV(std::istream& s)
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
}


namespace sc2replay
{

    Info::Info()
    {
  
    }

    Info::~Info()
    {
    }

    void Info::load( std::istream& s )
    {

        s.seekg(0x3f);
        
        while(readPlayer(s));

        s.seekg(2, std::ios::cur);

        mapName_ = readStr(s);
          
        s.seekg(2, std::ios::cur); // 04 02

        //std::cout << readStr(s) << std::endl; //what's this?

        s.seekg(5, std::ios::cur); // 06 05 02 00 02

        mapFilename_ = readStr(s);
    }

    bool
    Info::readPlayer(std::istream& s)
    {
        // player header is 05 12 00 02
        // check for that
        uint8_t hdr[] = { 0x5, 0x12, 0x0, 0x2 };
        for (int idx = 0; idx < sizeof(hdr)/sizeof(uint8_t); ++idx)
        {
            if (read(s) != hdr[idx])
            {
                s.seekg(-1 - idx, std::ios::cur); //reset file to state before call
                return false;
            }
        }

        std::string shortName = readStr(s);

        s.seekg(3, std::ios::cur); // 02 05 08

        readKV(s); // key = 00 09

        s.seekg(6, std::ios::cur); // unknown2

        readKV(s); // key = 04 09

        s.seekg(2, std::ios::cur); // 06 02

        std::string fullName = readStr(s); // fullName

        s.seekg(2, std::ios::cur); // 04 02

        std::string race = readStr(s); // race

        s.seekg(3, std::ios::cur); // 06 05 08

        for (int i=0; i < 9; ++i)
            readKV(s);

        if (shortName.size() && race.size())
            players_.push_back(Player(shortName, race, fullName));

        return true;

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

