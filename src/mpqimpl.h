#ifndef SC2REPLAY_MPQIMPL_H
#define SC2REPLAY_MPQIMPL_H

#include "types.h"
#include "mpq.h"

#include <libmpq/mpq.h>


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
  MPQFile* getFile( const MPQArchive* self, const std::string& filename ) const;
  
private:
  std::string filename_;

  mpq_archive_s* archive_;
};

} // namespace sc2replay

#endif // SC2REPLAY_MPQIMPL_H
