#include "replay.h"

#include "mpq.h"

#include <iostream>
#include <fstream>

namespace sc2replay
{

Replay::Replay( const std::string& filename )
  : imageBuffer_(  0    ),
    isValid_    ( false )
{
  load( filename );
}

Replay::~Replay()
{
  delete [] imageBuffer_;
}

void Replay::load( const std::string& filename )
{
  filename_ = filename;
  
  MPQArchive archive;
  
  // Sanity check
  isValid_ = true;
  if ( !archive.load( filename ) )
  {
    std::cerr << "Error loading MPQ file " << filename << "." << std::endl;
    isValid_ = false;
    return;
  }

  MPQFile* infoFile    = archive.getFile( "replay.info"           );
  const MPQFile* gameFile    = archive.getFile( "replay.game.events"    );
  const MPQFile* syncFile    = archive.getFile( "replay.sync.events"    );
  const MPQFile* messageFile = archive.getFile( "replay.message.events" );
  const MPQFile* saveFile    = archive.getFile( "save.jpg"              );
  
  info_.load         ( *infoFile->getFileStream());
  gameEvents_.load   ( gameFile->getFileContent(),    gameFile->getFileSize()    );
  syncEvents_.load   ( syncFile->getFileContent(),    syncFile->getFileSize()    );
  messageEvents_.load( messageFile->getFileContent(), messageFile->getFileSize() );
  imageSize_   = saveFile->getFileSize();
  imageBuffer_ = new uint8_t[imageSize_];
  std::copy( saveFile->getFileContent(), saveFile->getFileContent()+imageSize_, imageBuffer_ );
  
  delete infoFile;
  delete gameFile;
  delete syncFile;
  delete messageFile;
  delete saveFile;
}

const Info& Replay::getInfo() const
{
  return info_;
}

const GameEvents& Replay::getGameEvents() const
{
  return gameEvents_;
}

const MessageEvents& Replay::getMessageEvents() const
{
  return messageEvents_;
}

const SyncEvents& Replay::getSyncEvents() const
{
  return syncEvents_;
}

const std::string& Replay::getFilename() const
{
  return filename_;
}

const uint8_t* Replay::getImageBuffer() const
{
  return imageBuffer_;
}

off_t Replay::getImageSize() const
{
  return imageSize_;
}

bool Replay::isValid() const
{
  return isValid_;
}

void Replay::exportImage( const std::string& filename ) const
{
  if ( imageBuffer_==0 )
    return;
  
  std::ofstream file( filename.c_str(), std::ios::binary );
  file.write( (char*)imageBuffer_, imageSize_ );
  file.close();
}

}
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

