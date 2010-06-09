#include "mpq.h"

#include "mpqimpl.h"

namespace sc2replay
{

//
// MPQ Archive
//

    MPQArchive::MPQArchive()
    {
        impl_ = new MPQArchiveImpl;
    }

    MPQArchive::~MPQArchive()
    {
        delete impl_;
    }

    bool MPQArchive::load( const std::string& filename )
    {
        return impl_->load( this, filename );
    }

    MPQFile* MPQArchive::getFile( const std::string& filename ) const
    {
        return impl_->getFile( this, filename );
    }

//
// MPQ File
//

    MPQFile::MPQFile( const MPQArchive& archive, 
                      const std::string& filename, 
                      const uint8_t* buffer, off_t size )
        : archive_( archive ), filename_( filename ), 
          buffer_( buffer ), size_( size ), stream_(buffer_, size_)
    {
    }

    MPQFile::~MPQFile()
    {
        delete buffer_;
    }

    const MPQArchive& MPQFile::getArchive() const
    {
        return archive_;
    }

    off_t MPQFile::getFileSize() const
    {
        return size_;
    }

    const std::string& MPQFile::getFileName() const
    {
        return filename_;
    }

    const uint8_t* MPQFile::getFileContent() const
    {
        return buffer_;
    }

    MPQFile::array_stream* MPQFile::getFileStream()
    {
        return &stream_;
    }

} // namespace sc2replay
// Local Variables:
// mode:c++
// c-file-style:stroustrup
// end:

