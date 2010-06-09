#include "syncevents.h"

#include <fstream>

namespace sc2replay
{

SyncEvents::SyncEvents()
  : buffer_    ( 0 ),
    bufferSize_( 0 )
{
}

SyncEvents::~SyncEvents()
{
  delete [] buffer_;
}

void SyncEvents::load( const uint8_t* buffer, unsigned long size )
{
  buffer_ = new uint8_t[size];
  std::copy( buffer, buffer+size, buffer_ );
  bufferSize_ = size;
}

off_t SyncEvents::getBufferSize() const
{
  return bufferSize_;
}

uint8_t* SyncEvents::getBuffer() const
{
  return buffer_;
}

void SyncEvents::exportDump( const std::string& filename ) const
{
  std::ofstream file( filename.c_str(), std::ios::binary );
  file.write( (const char*)buffer_, bufferSize_ );
  file.close();
}

}
// Local Variables:
// mode:c++
// c-file-style:stroustrup
// end:

