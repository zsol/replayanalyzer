#ifndef SC2REPLAY_TYPES_H
#define SC2REPLAY_TYPES_H

namespace sc2replay
{

//
// Assuming common type sizes
//

typedef unsigned char uint8_t;
typedef signed   char int8_t;

typedef unsigned short uint16_t;
typedef signed   short int16_t;

typedef unsigned int uint32_t;
typedef signed   int int32_t;

#ifdef _MSC_VER
typedef unsigned __int64 uint64_t;
typedef signed   __int64 int64_t;
#else
typedef unsigned long long uint64_t;
typedef signed   long long int64_t;
#endif

typedef int64_t off_t;

//
// Custom types
//

typedef uint8_t  player_t;
typedef uint32_t timestamp_t;

} // namespace sc2replay

#endif // S2REPLAY_TYPES_H
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

