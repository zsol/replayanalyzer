#ifndef SC2REPLAY_MPQIMPL_H
#define SC2REPLAY_MPQIMPL_H

#include "sc2replay/types.h"
#include "sc2replay/mpq.h"

#ifdef BUILD_LIBMPQ
#  include <libmpq/mpq.h>
#else // StormLib
#  include <StormLib/StormLib.h>
#endif

namespace sc2replay
{

class MPQArchiveImpl
{
public:
  MPQArchiveImpl();
  ~MPQArchiveImpl();

public:
  bool load( const MPQArchive* self, const std::string& filename );

public:
  const std::string& getFilename() const;
  
public:
  const MPQFile* getFile( const MPQArchive* self, const std::string& filename ) const;
  
private:
  std::string filename_;

#ifdef BUILD_LIBMPQ
  mpq_archive_s* archive_;
#else
  HANDLE         archive_;
#endif
};

} // namespace sc2replay

#endif // SC2REPLAY_MPQIMPL_H
