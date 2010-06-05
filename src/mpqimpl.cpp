#include "mpqimpl.h"

#include <string>
#include <fstream>

namespace sc2replay
{

MPQArchiveImpl::MPQArchiveImpl()
{
  static bool initialized = false;
  if ( !initialized )
  {
    // Comment this line if using a newer version of libmpq that removed libmpq__init & libmpq__shutdown
    libmpq__init();
    initialized = true;
  }
}

MPQArchiveImpl::~MPQArchiveImpl()
{
  if ( archive_!=0 ) // sanity check, libmpq will crash if archive is null
    libmpq__archive_close( archive_ );
}

bool MPQArchiveImpl::load( const MPQArchive* self, const std::string& filename )
{
  filename_ = filename;
  
  int32_t good = libmpq__archive_open( &archive_, filename.c_str(), -1 );
  
  // Sanity check
  if ( good < 0 )
    return false;

  return true;
}

const std::string& MPQArchiveImpl::getFilename() const
{
  return filename_;
}

const MPQFile* MPQArchiveImpl::getFile( const MPQArchive* self, const std::string& filename ) const
{
  uint32_t number = 0;
  ::off_t    size   = 0;
  uint8_t* buffer = 0;
  
  libmpq__file_number( archive_, filename.c_str(), &number );
  libmpq__file_unpacked_size( archive_, number, &size );
  
  buffer = new uint8_t[size];
  
  libmpq__file_read( archive_, number, buffer, size, NULL );
  
  return new MPQFile( *self, filename, buffer, size );
}

} // namespace sc2replay
