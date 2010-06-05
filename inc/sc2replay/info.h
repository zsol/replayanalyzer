#ifndef SC2REPLAY_INFO_H
#define SC2REPLAY_INFO_H

#include "sc2replay/types.h"

#include <string>
#include <vector>

namespace sc2replay
{

struct PlayerDisplay
{
public:
  PlayerDisplay(const std::string& n="", const std::string& r="", const std::string& c="")
    : name(n), race(r), color(c)
  {
  }
  
public:
  bool operator==(const PlayerDisplay& other)
  {
    return name==other.name && race==other.race && color==other.color;
  }
  
public:
  std::string name;
  std::string race;
  std::string color;
};

class Info
{
public:
  enum GameSpeed
  {
    SLOWER = 0x00,
    SLOW   = 0x01,
    NORMAL = 0x02,
    FAST   = 0x03,
    FASTER = 0x04
  };
  
public:
  typedef std::vector<std::string>   PlayerNames;
  typedef std::vector<PlayerDisplay> PlayerDisplays;
  
public:
  Info();
  ~Info();
  
public:
  void load( const uint8_t* data, off_t size );
  
public:
  const PlayerNames&    getPlayerNames           () const;
  const uint8_t         getNumberOfPlayers       () const;
  const uint8_t         getNumberOfSlots         () const;
  const std::string&    getMapFilename           () const;
  const std::string&    getMapName               () const;
  GameSpeed             getSpeed                 () const;
  bool                  getAllianceLocked        () const;
  uint8_t               getNumberOfPlayerDisplays() const;
  const PlayerDisplays& getPlayerDisplays        () const;
  off_t                 getBufferSize            () const;
  uint8_t*              getBuffer                () const;
  
public:
  void exportDump( const std::string& filename ) const;
  
private:
  PlayerNames    playerNames_;
  uint8_t        numberOfSlots_;
  std::string    mapFilename_;
  std::string    mapName_;
  GameSpeed      speed_;
  bool           allianceLocked_;
  uint8_t        numberOfPlayerDisplay_;
  PlayerDisplays playerDisplays_;
  uint8_t*       buffer_;
  off_t          bufferSize_;
};

} // namespace sc2replay

#endif // SC2REPLAY_INFO_H
