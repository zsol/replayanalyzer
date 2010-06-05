#ifndef SC2REPLAY_REPLAY_H
#define SC2REPLAY_REPLAY_H

#include "sc2replay/types.h"
#include "sc2replay/gameevents.h"
#include "sc2replay/info.h"
#include "sc2replay/messageevents.h"
#include "sc2replay/syncevents.h"

#include <string>

namespace sc2replay
{

class Replay
{
public:
  explicit Replay( const std::string& filename );
  ~Replay();
  
public:
  // Load a starcraft 2 replay file
  void load( const std::string& filename );
  
public:
  bool isValid() const;
  
public:
  // Getters
  const Info&          getInfo         () const;
  const GameEvents&    getGameEvents   () const;
  const MessageEvents& getMessageEvents() const;
  const SyncEvents&    getSyncEvents   () const;
  const std::string&   getFilename     () const;
  const uint8_t*       getImageBuffer  () const;
  off_t                getImageSize    () const;
  
public:
  void exportImage( const std::string& filename ) const;
  
private:
  bool          isValid_;
  Info          info_;
  GameEvents    gameEvents_;
  MessageEvents messageEvents_;
  SyncEvents    syncEvents_;
  std::string   filename_;
  uint8_t*      imageBuffer_;
  off_t         imageSize_;
};

} // namespace sc2replay

#endif // SC2REPLAY_REPLAY_H
