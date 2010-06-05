#ifndef SC2REPLAY_MPQ_H
#define SC2REPLAY_MPQ_H

#include "sc2replay/types.h"

#include <string>

namespace sc2replay
{

class MPQArchive;
class MPQArchiveImpl;

class MPQFile;
class MPQFileImpl;

class MPQArchive
{
public:
  MPQArchive();
  ~MPQArchive();
  
public:
  bool load( const std::string& filename );
  
public:
  const MPQFile* getFile( const std::string& filename ) const;
  
private:
  MPQArchiveImpl* impl_;
};

class MPQFile
{
public:
  MPQFile( const MPQArchive&  archive,
           const std::string& filename,
           const uint8_t*     buffer,
           off_t              size );
  ~MPQFile();
  
public:
  void load( const std::string& filename );
  
public:
  const MPQArchive&  getArchive    () const;
  off_t              getFileSize   () const;
  const std::string& getFileName   () const;
  const uint8_t*     getFileContent() const;
  
private:
  off_t             size_;
  const uint8_t*    buffer_;
  const std::string filename_;
  const MPQArchive& archive_;
  
private:
  MPQFile( const MPQFile& ); // Not copyable
};

} // namespace sc2replay

#endif // SC2REPLAY_MPQ_H
