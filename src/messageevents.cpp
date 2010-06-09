#include "messageevents.h"

#include <fstream>
#include <algorithm>
#include <iostream>

namespace sc2replay
{

MessageEvents::MessageEvents()
  : buffer_    ( 0 ),
    bufferSize_( 0 )
{
}

MessageEvents::~MessageEvents()
{
  delete [] buffer_;
}

void MessageEvents::load( const uint8_t* buffer, unsigned long size )
{
  buffer_ = new uint8_t[size];
  std::copy( buffer, buffer+size, buffer_ );
  bufferSize_ = size;
  
  off_t offset = 0;
  // --- Unknowns
  // A bunch of unknowns, 7 bytes long each
  // 0x00 0x2? 0x80 0x00 0x00 0x?? (0x00|0x01)
  while ( buffer[offset+2]==0x80 )
    offset += 7 * sizeof(uint8_t);
  
  // --- Blinks
  // Trying to guess if there are some blinks
  while ( true )
  {
    Blink blink;
    
    // Assuming framesize is maximum 64b
    if ( buffer[offset+2]==0x83 )
    {
      blink.timestamp = *((uint8_t*)buffer+offset);
      offset += sizeof(uint8_t);
    }
    else if ( buffer[offset+3]==0x83 )
    {
      blink.timestamp = *((uint16_t*)buffer+offset);
      offset += sizeof(uint16_t);
    }
    else if ( buffer[offset+4]==0x83 )
    {
      blink.timestamp = *((uint16_t*)buffer+offset) << 8 + *((uint8_t*)buffer+offset+2);
      offset += 3 * sizeof(uint8_t);
    }
    else if ( buffer[offset+5]==0x83 )
    {
      blink.timestamp = *((uint32_t*)buffer+offset);
      offset += sizeof(uint32_t);
    }
      
    else if ( buffer[offset+6]==0x83 )
    {
      blink.timestamp = *((uint32_t*)buffer+offset ) << 8 +
                        *((uint8_t*)buffer+offset+4);
      offset += 5 * sizeof(uint8_t);
    }
    else if ( buffer[offset+7]==0x83 )
    {
      blink.timestamp = *((uint32_t*)buffer+offset  ) << 16 +
                        *((uint16_t*)buffer+offset+4);
      offset += 6 * sizeof(uint8_t);
    }
      
    else if ( buffer[offset+8]==0x83 )
    {
      blink.timestamp = *((uint32_t*)buffer+offset  ) << 24 +
                        *((uint16_t*)buffer+offset+4) <<  8 +
                        *((uint8_t *)buffer+offset+6);
      offset += 7 * sizeof(uint8_t);
    }
    else if ( buffer[offset+9]==0x83 )
    {
      blink.timestamp = *((uint64_t*)buffer+offset);
      offset += 8 * sizeof(uint8_t);
    }
    else
      break; // Does not seem to be a blink, this should be a message
    
    // Sender of the blink
    blink.player = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Blink opcode 0x83
    offset += sizeof(uint8_t);
    
    blink.x = *((uint32_t*)buffer+offset);
    offset += sizeof(uint32_t);
    
    blink.y = *((uint32_t*)buffer+offset);
    offset += sizeof(uint32_t);
    
    blinks_.push_back( blink );
  }
  
  // --- Messages
  // Trying to guess if there are some messages
  while ( true )
  {
    //std::cout << "Message beginning:" << std::endl;
    //std::cout << std::hex << (unsigned int)(buffer[offset+0]) << " "
    //                      << (unsigned int)(buffer[offset+1]) << " "
    //                      << (unsigned int)(buffer[offset+2]) << " "
    //                      << (unsigned int)(buffer[offset+3]) << " "
    //                      << (unsigned int)(buffer[offset+4]) << " "
    //                      << (unsigned int)(buffer[offset+5]) << " "
    //                      << (unsigned int)(buffer[offset+6]) << " "
    //                      << std::dec << std::endl;
    
    Message message;
    
    // Assuming framesize is maximum 64b
    if ( buffer[offset+2]==0x00 /*| buffer[offset+2]==0x02*/ )
    {
      message.timestamp = *((uint8_t*)buffer+offset);
      offset += sizeof(uint8_t);
    }
    else if ( buffer[offset+3]==0x00 /*| buffer[offset+3]==0x02*/ )
    {
      message.timestamp = *((uint16_t*)buffer+offset);
      offset += sizeof(uint16_t);
    }
    else if ( buffer[offset+4]==0x00 /*| buffer[offset+4]==0x02*/ )
    {
      message.timestamp = *((uint16_t*)buffer+offset) << 8 + *((uint8_t*)buffer+offset+2);
      offset += 3 * sizeof(uint8_t);
    }
    else if ( buffer[offset+5]==0x00 /*| buffer[offset+5]==0x02*/ )
    {
      message.timestamp = *((uint32_t*)buffer+offset);
      offset += sizeof(uint32_t);
    }
      
    else if ( buffer[offset+6]==0x00 /*| buffer[offset+6]==0x02*/ )
    {
      message.timestamp = *((uint32_t*)buffer+offset ) << 8 +
                        *((uint8_t*)buffer+offset+4);
      offset += 5 * sizeof(uint8_t);
    }
    else if ( buffer[offset+7]==0x00 /*| buffer[offset+7]==0x02*/ )
    {
      message.timestamp = *((uint32_t*)buffer+offset  ) << 16 +
                        *((uint16_t*)buffer+offset+4);
      offset += 6 * sizeof(uint8_t);
    }
      
    else if ( buffer[offset+8]==0x00 /*| buffer[offset+8]==0x02*/ )
    {
      message.timestamp = *((uint32_t*)buffer+offset  ) << 24 +
                        *((uint16_t*)buffer+offset+4) <<  8 +
                        *((uint8_t *)buffer+offset+6);
      offset += 7 * sizeof(uint8_t);
    }
    else if ( buffer[offset+9]==0x00 /*| buffer[offset+9]==0x02*/ )
    {
      message.timestamp = *((uint64_t*)buffer+offset);
      offset += 8 * sizeof(uint8_t);
    }
    else
      break; // Does not seem to be a blink, this should be a message
    
    // Sender of the message
    message.player = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Message type
    message.type = static_cast<MessageType>(buffer[offset]);
    offset += sizeof(uint8_t);
    
    // Message length
    uint8_t textLength = buffer[offset];
    offset += sizeof(uint8_t);
    
    // Message text
    message.text = std::string( (const char*)buffer+offset, textLength );
    offset += textLength * sizeof(uint8_t);
    
    messages_.push_back( message );
    
    if ( offset>=size )
      break;
  }
}

const MessageEvents::Messages& MessageEvents::getMessages() const
{
  return messages_;
}

const MessageEvents::Blinks& MessageEvents::getBlinks() const
{
  return blinks_;
}

off_t MessageEvents::getBufferSize() const
{
  return bufferSize_;
}

uint8_t* MessageEvents::getBuffer() const
{
  return buffer_;
}

void MessageEvents::exportDump( const std::string& filename ) const
{
  std::ofstream file( filename.c_str(), std::ios::binary );
  file.write( (const char*)buffer_, bufferSize_ );
  file.close();
}

}
// Local Variables:
// mode:c++
// c-file-style:stroustrup
// end:

