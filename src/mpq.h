#ifndef SC2REPLAY_MPQ_H
#define SC2REPLAY_MPQ_H

#include "types.h"

#include <string>
#include <iosfwd>
#include <fstream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/code_converter.hpp>
#include <boost/iostreams/device/array.hpp>

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
  MPQFile* getFile( const std::string& filename ) const;
  
private:
  MPQArchiveImpl* impl_;
};

class MPQFile
{
public:
  MPQFile( const std::string& filename,
           const uint8_t*     buffer,
           off_t              size );
  ~MPQFile();
  
  typedef boost::iostreams::stream<boost::iostreams::array_source> array_stream;

public:
  void load( const std::string& filename );
  
public:
  off_t              getFileSize   () const;
  const std::string& getFileName   () const;
  const uint8_t*     getFileContent() const;
  
  /// \todo wrap this in a smart pointer
  array_stream* getFileStream(); 
  
private:
  off_t             size_;
  const uint8_t*    buffer_;
  const std::string filename_;
  array_stream stream_;
  
private:
  MPQFile( const MPQFile& ); // Not copyable
};

} // namespace sc2replay

#endif // SC2REPLAY_MPQ_H
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

