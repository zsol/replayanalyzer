#ifndef SC2REPLAY_INFO_H
#define SC2REPLAY_INFO_H

#include "types.h"
#include "player.h"

#include <string>
#include <vector>

namespace sc2replay
{

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
  typedef std::vector<Player>   Players;
  
public:
  Info();
  ~Info();
  
public:
  void load( std::istream& );
  
public:
  const Players& getPlayers() const;
  const uint8_t getNumberOfPlayers() const;
  const std::string& getMapFilename() const;
  const std::string& getMapName() const;
  
public:
  void exportDump( const std::string& filename ) const;
  
 private:
  bool readPlayer(std::istream& s);
private:
  Players players_;
  std::string mapFilename_;
  std::string mapName_;
};

} // namespace sc2replay

#endif // SC2REPLAY_INFO_H
