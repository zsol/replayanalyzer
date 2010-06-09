#ifndef SC2REPLAY_MESSAGEEVENTS_H
#define SC2REPLAY_MESSAGEEVENTS_H

#include "types.h"

#include <string>
#include <vector>

namespace sc2replay
{

struct Blink
{
public:
  Blink( uint64_t t=0, uint8_t p=0, uint32_t px=0, uint32_t py=0 )
    : timestamp(t), player(p), x(px), y(py)
  {
  }
  
public:
  bool operator==( const Blink& other )
  {
    return timestamp == other.timestamp &&
           player    == other.player    &&
           x         == other.x         &&
           y         == other.y;
  }
  
public:
  uint64_t timestamp;
  uint8_t  player;
  uint32_t x;
  uint32_t y;
};

enum MessageType
{
  ALL      = 0x00,
  ALLIANCE = 0x02
};

struct Message
{
public:
  Message( uint64_t ti=0, uint8_t p=0, MessageType ty=ALL, const std::string& te="" )
    : timestamp(ti), player(p), type(ty), text(te)
  {
  }
  
public:
  bool operator==( const Message& other )
  {
    return timestamp == other.timestamp &&
           player    == other.player    &&
           type      == other.type      &&
           text      == other.text;
  }
  
public:
  uint64_t    timestamp;
  uint8_t     player;
  MessageType type;
  std::string text;
};
  
class MessageEvents
{
public:
  typedef std::vector<Message> Messages;
  typedef std::vector<Blink>   Blinks;
  
public:
  MessageEvents();
  ~MessageEvents();
  
public:
  void load( const uint8_t* data, unsigned long size ); 
  
public:
  const Messages& getMessages() const;
  const Blinks&   getBlinks  () const;
  off_t    getBufferSize() const;
  uint8_t* getBuffer    () const;
  
public:
  void exportDump( const std::string& filename ) const;
  
private:
  uint8_t* buffer_;
  off_t    bufferSize_;
  Messages messages_;
  Blinks   blinks_;
};

} // namespace sc2replay

#endif // SC2REPLAY_MESSAGEEVENTS_H
// Local Variables:
// mode:c++
// c-file-style:stroustrup
// end:

