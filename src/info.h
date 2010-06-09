#ifndef SC2REPLAY_INFO_H
#define SC2REPLAY_INFO_H

#include "types.h"
#include "player.h"
#include "util.h"

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
        template <typename T>
        void load( std::basic_istream<T>& );
  
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
    };

} // namespace sc2replay

namespace sc2replay
{

    template <typename T>
    void Info::load( std::basic_istream<T>& s )
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

    template <typename T>
    bool
    Info::readPlayer(std::basic_istream<T>& s)
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
    

} // namespace sc2replay

#endif // SC2REPLAY_INFO_H
// Local Variables:
// mode:c++
// c-file-style:stroustrup
// end:

