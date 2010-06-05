#ifndef SC2REPLAY_UTIL_H
#define SC2REPLAY_UTIL_H

#include <string>
#include <sstream>

#include "sc2replay/types.h"

namespace sc2replay
{

//
// DECLARATIONS
//

std::string timestampToString( timestamp_t timestamp );

//
// IMPLEMENTATIONS
//

std::string timestampToString( timestamp_t timestamp )
{
  uint8_t seconds = (timestamp/64) % 60;
  uint8_t minutes = seconds / 60;
  
  std::ostringstream oss;
  oss << (int)minutes << ":" << (int)seconds;
  
  return oss.str();
}

} // namespace sc2replay

#endif // SC2REPLAY_UTIL_H
