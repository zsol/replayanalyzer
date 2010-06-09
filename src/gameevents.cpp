#include "gameevents.h"

#include <fstream>
#include <iostream>

namespace sc2replay
{

GameEvents::GameEvents()
  : buffer_    ( 0 ),
    bufferSize_( 0 )
{
}

GameEvents::~GameEvents()
{
  EventList::const_iterator it = begin();
  for (; it!=end(); ++it )
    delete *it;
  delete [] buffer_;
}

void GameEvents::load( const uint8_t* buffer, unsigned long size )
{
  buffer_ = new uint8_t[size];
  std::copy( buffer, buffer+size, buffer_ );
  bufferSize_ = size;
  
  parse();
}

off_t GameEvents::getBufferSize() const
{
  return bufferSize_;
}

uint8_t* GameEvents::getBuffer() const
{
  return buffer_;
}

void GameEvents::exportDump( const std::string& filename ) const
{
  std::ofstream file( filename.c_str(), std::ios::binary );
  file.write( (const char*)buffer_, bufferSize_ );
  file.close();
}

GameEvents::EventList::const_iterator GameEvents::begin() const
{
  return events_.begin();
}

GameEvents::EventList::const_iterator GameEvents::end() const
{
  return events_.end();
}

size_t GameEvents::size() const
{
  return events_.size();
}

//
// PARSER INTERFACE
//

void GameEvents::parse()
{
  off_t offset = 0;
  
  while ( offset < bufferSize_ )
  {
    GameEvent e;
    parseHeader( offset, e );
    
    switch ( e.code )
    {
      case INITIALIZATION_SPAWN:
      {
        events_.push_back( parseSpawnEvent(offset,e) );
      } break;
      
      case INITIALIZATION_START:
      {
        events_.push_back( parseStartEvent(offset,e) );
      } break;
      
      case ACTION_QUIT:
      {
        events_.push_back( parseQuitEvent(offset,e) );
      } break;
      
      case ACTION_ABILITY:
      {
        std::cerr << "Parsing trap [ACTION_ABILITY] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      case ACTION_SEND_RESOURCE:
      {
        events_.push_back( parseQuitEvent(offset,e) );
      } break;
      
      case ACTION_SELECTION:
      {
        std::cerr << "Parsing trap [ACTION_SELECTION] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      case ACTION_USE_HOTKEY0:
      case ACTION_USE_HOTKEY1:
      case ACTION_USE_HOTKEY2:
      case ACTION_USE_HOTKEY3:
      case ACTION_USE_HOTKEY4:
      case ACTION_USE_HOTKEY5:
      case ACTION_USE_HOTKEY6:
      case ACTION_USE_HOTKEY7:
      case ACTION_USE_HOTKEY8:
      case ACTION_USE_HOTKEY9:
      {
        std::cerr << "Parsing trap [ACTION_USE_HOTKEY] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      case ACTION_UPDATE_HOTKEY0:
      case ACTION_UPDATE_HOTKEY1:
      case ACTION_UPDATE_HOTKEY2:
      case ACTION_UPDATE_HOTKEY3:
      case ACTION_UPDATE_HOTKEY4:
      case ACTION_UPDATE_HOTKEY5:
      case ACTION_UPDATE_HOTKEY6:
      case ACTION_UPDATE_HOTKEY7:
      case ACTION_UPDATE_HOTKEY8:
      case ACTION_UPDATE_HOTKEY9:
      {
        std::cerr << "Parsing trap [ACTION_UPDATE_HOTKEY] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      case REPLAY_MOVE_CAMERA:
      {
        events_.push_back( parseCameraEvent(offset,e) );
      } break;
      
      case INACTION_SYNCHRONIZATION:
      {
        std::cerr << "Parsing trap [INACTION_SYNCHRONIZATION] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      case INACTION_SEND_REQUEST:
      {
        std::cerr << "Parsing trap [INACTION_SEND_REQUEST] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      case INACTION_CANCEL_REQUEST:
      {
        std::cerr << "Parsing trap [INACTION_CANCEL_REQUEST] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      case SYSTEM_SYNCHRONIZATION:
      {
        std::cerr << "Parsing trap [SYSTEM_SYNCHRONIZATION] @" << offset << std::endl;
        return; // Not implemented at the moment
      } break;
      
      default:
      {
        std::cerr << "Parsing trap... aborting." << std::endl;
        return;
      } break;
    }
  }
}

void GameEvents::parseHeader( off_t& offset, GameEvent& event )
{
  // --- Timestamp
  timestamp_t timestamp = 0;
  if ( buffer_[offset] & 0x03 ) // 2 bytes timestamp
  {
    timestamp = (buffer_[offset] >> 2) << 8 + buffer_[offset+1];
    offset += 2;
  }
  else  // 1 byte timestamp
  {
    timestamp = buffer_[offset] >> 2;
    offset += 1;
  }
  event.timestamp = timestamp;
  
  // --- Type
  event.type = static_cast<EventType>((buffer_[offset] & 0xE0) >> 5);
  
  // --- Flag
  event.flag = static_cast<EventFlag>((buffer_[offset] & 0x10) >> 4);
  
  // --- Player
  event.player = static_cast<player_t>(buffer_[offset] & 0x0F);
  
  offset += 1;
  
  // --- Code
  event.code = static_cast<EventCode>(buffer_[offset]);
  offset += 1;
}

InitializationSpawn* GameEvents::parseSpawnEvent( off_t& offset, GameEvent& event )
{
  InitializationSpawn* e = new InitializationSpawn(event);
  return e;
}

InitializationStart* GameEvents::parseStartEvent( off_t& offset, GameEvent& event )
{
  InitializationStart* e = new InitializationStart(event);
  return e;
}

ActionQuit* GameEvents::parseQuitEvent( off_t& offset, GameEvent& event )
{
  ActionQuit* e = new ActionQuit(event);
  return e;
}

ActionAbility* GameEvents::parseAbilityEvent( off_t& offset, GameEvent& event )
{
  ActionAbility* e = new ActionAbility(event);
  
  // Not implemented at the moment
  
  return e;
}

ActionSendResource* GameEvents::parseSendResourceEvent( off_t& offset, GameEvent& event )
{
  ActionSendResource* e = new ActionSendResource(event);
  
  // Not implemented at the moment
  
  return e;
}

ActionSelection* GameEvents::parseSelectionEvent( off_t& offset, GameEvent& event )
{
  ActionSelection* e = new ActionSelection(event);
  
  // Not implemented at the moment
  
  return e;
}

ActionUseHotkey* GameEvents::parseUseHotkey( off_t& offset, GameEvent& event )
{
  ActionUseHotkey* e = new ActionUseHotkey(event);
  
  // Not implemented at the moment
  
  return e;
}

ActionUpdateHotkey* GameEvents::parseUpdateHotkey( off_t& offset, GameEvent& event )
{
  ActionUpdateHotkey* e = new ActionUpdateHotkey(event);
  
  // Not implemented at the moment
  
  return e;
}

ReplayMoveCamera* GameEvents::parseCameraEvent( off_t& offset, GameEvent& event )
{
  ReplayMoveCamera* e = new ReplayMoveCamera(event);
  
  e->x = *(uint32_t*)(buffer_+offset);
  offset += 4;
  
  e->y = *(uint32_t*)(buffer_+offset);
  offset += 4;
  
  e->horizontal = *(uint32_t*)(buffer_+offset);
  offset += 4;
  
  e->vertical = *(uint32_t*)(buffer_+offset);
  offset += 4;
  
  e->unknown = *(uint32_t*)(buffer_+offset);
  offset += 4;
  
  return e;
}

InactionSynchronization* GameEvents::parseSyncEvent( off_t& offset, GameEvent& event )
{
  InactionSynchronization* e = new InactionSynchronization(event);
  
  // Not implemented at the moment
  
  return e;
}

InactionSendRequest* GameEvents::parseSendRequest( off_t& offset, GameEvent& event )
{
  InactionSendRequest* e = new InactionSendRequest(event);
  
  // Not implemented at the moment
  
  return e;
}

InactionCancelRequest* GameEvents::parseCancelRequest( off_t& offset, GameEvent& event )
{
  InactionCancelRequest* e = new InactionCancelRequest(event);
  
  // Not implemented at the moment
  
  return e;
}

SystemSynchronization* GameEvents::parseSystemSync( off_t& offset, GameEvent& event )
{
  SystemSynchronization* e = new SystemSynchronization(event);
  
  // Not implemented at the moment
  
  return e;
}

}
// Local Variables:
// mode:c++
// c-file-style:stroustrup
// end:

