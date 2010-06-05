#include "sc2replay/info.h"

#include <fstream>

namespace sc2replay
{

    Info::Info()
        : buffer_    ( 0 ),
          bufferSize_( 0 )
    {
  
    }

    Info::~Info()
    {
        delete [] buffer_;
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

          mapSname_ = readStr(s);
    }

    const Info::PlayerNames& Info::getPlayerNames() const
    {
        return playerNames_;
    }

    const uint8_t Info::getNumberOfPlayers() const
    {
        return playerNames_.size();
    }

    const uint8_t Info::getNumberOfSlots() const
    {
        return numberOfSlots_;
    }

    const std::string& Info::getMapFilename() const
    {
        return mapFilename_;
    }

    const std::string& Info::getMapName() const
    {
        return mapName_;
    }

    Info::GameSpeed Info::getSpeed() const
    {
        return speed_;
    }

    bool Info::getAllianceLocked() const
    {
        return allianceLocked_;
    }

    uint8_t Info::getNumberOfPlayerDisplays() const
    {
        return numberOfPlayerDisplay_;
    }

    const Info::PlayerDisplays& Info::getPlayerDisplays() const
    {
        return playerDisplays_;
    }

    off_t Info::getBufferSize() const
    {
        return bufferSize_;
    }

    uint8_t* Info::getBuffer() const
    {
        return buffer_;
    }

    void Info::exportDump( const std::string& filename ) const
    {
        std::ofstream file( filename.c_str(), std::ios::binary );
        file.write( (const char*)buffer_, bufferSize_ );
        file.close();
    }

}
