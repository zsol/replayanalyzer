#include "mpqimpl.h"

#include <string>
#include <fstream>

namespace sc2replay
{

MPQArchiveImpl::MPQArchiveImpl()
{
  static bool initialized = 
#ifdef NEW_LIBMPQ
      true
#else
      false
#endif
      ;

#ifndef NEW_LIBMPQ
  if (not initialized)
  {
      libmpq__init();
      initialized = true;
  }
#endif
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

MPQFile* MPQArchiveImpl::getFile( const MPQArchive* self, const std::string& filename ) const
{
  uint32_t number = 0;
  ::off_t size = 0, actualsize = 0;
  uint8_t* buffer = 0;
  
  libmpq__file_number( archive_, filename.c_str(), &number );
  libmpq__file_unpacked_size( archive_, number, &size );
  
  buffer = new uint8_t[size];
  
  libmpq__file_read( archive_, number, buffer, size, &actualsize );
  
  return new MPQFile( filename, buffer, actualsize );
}

} // namespace sc2replay
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

