#include "info.h"
#include "types.h"

#include <fstream>


namespace sc2replay
{

    Info::Info()
    {
  
    }

    Info::~Info()
    {
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
// c-file-style:stroustrup
// end:

