#ifndef SC2REPLAY_GAMEEVENTS_H
#define SC2REPLAY_GAMEEVENTS_H

#include "types.h"

#include <list>
#include <string>

namespace sc2replay
{

struct GameEvent;
struct InitializationSpawn;
struct InitializationStart;
struct ActionQuit;
struct ActionAbility;
struct ActionSendResource;
struct ActionSelection;
struct ActionUseHotkey;
struct ActionUpdateHotkey;
struct ReplayMoveCamera;
struct InactionSynchronization;
struct InactionSendRequest;
struct InactionCancelRequest;
struct SystemSynchronization;

class GameEvents
{
// --- Ctors / Dtors
public:
  GameEvents();
  ~GameEvents();

// --- Methods
public:
  void load( const uint8_t* data, unsigned long size );
  
public:
  off_t    getBufferSize() const;
  uint8_t* getBuffer    () const;
  
public:
  void exportDump( const std::string& filename ) const;

// --- Parser
public:
  void parse();
  
  void parseHeader           ( off_t& offset, GameEvent& event );
  
  InitializationSpawn*     parseSpawnEvent       ( off_t& offset, GameEvent& event );
  InitializationStart*     parseStartEvent       ( off_t& offset, GameEvent& event );
  ActionQuit*              parseQuitEvent        ( off_t& offset, GameEvent& event );
  ActionAbility*           parseAbilityEvent     ( off_t& offset, GameEvent& event );
  ActionSendResource*      parseSendResourceEvent( off_t& offset, GameEvent& event );
  ActionSelection*         parseSelectionEvent   ( off_t& offset, GameEvent& event );
  ActionUseHotkey*         parseUseHotkey        ( off_t& offset, GameEvent& event );
  ActionUpdateHotkey*      parseUpdateHotkey     ( off_t& offset, GameEvent& event );
  ReplayMoveCamera*        parseCameraEvent      ( off_t& offset, GameEvent& event );
  InactionSynchronization* parseSyncEvent        ( off_t& offset, GameEvent& event );
  InactionSendRequest*     parseSendRequest      ( off_t& offset, GameEvent& event );
  InactionCancelRequest*   parseCancelRequest    ( off_t& offset, GameEvent& event );
  SystemSynchronization*   parseSystemSync       ( off_t& offset, GameEvent& event );
  
// --- List interface
public:
  typedef std::list<GameEvent*>     EventList;
  typedef EventList::const_iterator const_iterator;
  
public:
  EventList::const_iterator begin() const;
  EventList::const_iterator end()   const;
  
  size_t size() const;
  
// --- Attributes
private:
  uint8_t*  buffer_;
  off_t     bufferSize_;
  EventList events_;
};

//==================================================
// EVENTS STRUCTURES
//==================================================

enum EventType
{
  INITIALIZATION = 0x00,
  ACTION         = 0x01,
  UNKNOWN2       = 0x02,
  REPLAY         = 0x03,
  INACTION       = 0x04,
  SYSTEM         = 0x05,
  UNKNOWN6       = 0x06,
  UNKNOWN7       = 0x07
};

enum EventFlag
{
  PLAYER = 0x00,
  GLOBAL = 0x01
};

enum EventCode
{
  INITIALIZATION_SPAWN     = 0x1B,
  INITIALIZATION_START     = 0x05,

  ACTION_QUIT              = 0x09,
  ACTION_ABILITY           = 0x0B,
  ACTION_SEND_RESOURCE     = 0x2F,
  ACTION_SELECTION         = 0xAC,
  ACTION_USE_HOTKEY0       = 0x0D,
  ACTION_USE_HOTKEY1       = 0x1D,
  ACTION_USE_HOTKEY2       = 0x2D,
  ACTION_USE_HOTKEY3       = 0x3D,
  ACTION_USE_HOTKEY4       = 0x4D,
  ACTION_USE_HOTKEY5       = 0x5D,
  ACTION_USE_HOTKEY6       = 0x6D,
  ACTION_USE_HOTKEY7       = 0x7D,
  ACTION_USE_HOTKEY8       = 0x8D,
  ACTION_USE_HOTKEY9       = 0x9D,
  ACTION_UPDATE_HOTKEY0    = 0x0C,
  ACTION_UPDATE_HOTKEY1    = 0x1C,
  ACTION_UPDATE_HOTKEY2    = 0x2C,
  ACTION_UPDATE_HOTKEY3    = 0x3C,
  ACTION_UPDATE_HOTKEY4    = 0x4C,
  ACTION_UPDATE_HOTKEY5    = 0x5C,
  ACTION_UPDATE_HOTKEY6    = 0x6C,
  ACTION_UPDATE_HOTKEY7    = 0x7C,
  ACTION_UPDATE_HOTKEY8    = 0x8C,
  ACTION_UPDATE_HOTKEY9    = 0x9C,

  REPLAY_MOVE_CAMERA       = 0x81,

  INACTION_SYNCHRONIZATION = 0x00,
  INACTION_SEND_REQUEST    = 0x16,
  INACTION_CANCEL_REQUEST  = 0x18,

  SYSTEM_SYNCHRONIZATION   = 0x89
};

enum AbilityCode
{
  COMMON_STOP          = 0x020400,
  COMMON_HOLD_FIRE     = 0x020501,
  COMMON_MOVE          = 0x020600,
  COMMON_PATROL        = 0x020601,
  COMMON_HOLD_POSITION = 0x020602,
  COMMON_ATTACK        = 0x020900,
  COMMON_CANCEL        = 0x060800,
  COMMON_GATHER        = 0x060400,
  
  TERRAN_POINT_DEFENSE_DRONE           = 0x030A00,
  TERRAN_SEEKER_MISSILE                = 0x040700,
  TERRAN_SET_RALLY_POINT               = 0x050500,
  TERRAN_STIMPACK_MARAUDER             = 0x050D00,
  TERRAN_250MM_STRIKE_CANNON           = 0x050F00,
  TERRAN_RETURN_CARGO                  = 0x060401,
  TERRAN_BUILD_COMMAND_CENTER          = 0x060D00,
  TERRAN_BUILD_SUPPLY_DEPOT            = 0x060D01,
  TERRAN_BUILD_REFINERY                = 0x060D02,
  TERRAN_BUILD_BARRACKS                = 0x060D03,
  TERRAN_BUILD_ENGINEERING_BAY         = 0x060D04,
  TERRAN_BUILD_MISSILE_TURRET          = 0x060D05,
  TERRAN_BUILD_BUNKER                  = 0x060D06,
  TERRAN_BUILD_SENSOR_TOWER            = 0x060D08,
  TERRAN_BUILD_GHOST_ACADEMY           = 0x060D09,
  TERRAN_BUILD_FACTORY                 = 0x060D0A,
  TERRAN_BUILD_STARPORT                = 0x060D0B,
  TERRAN_BUILD_ARMORY                  = 0x060D0D,
  TERRAN_BUILD_FUSION_CORE             = 0x060D0F,
  TERRAN_STIMPACK_MARINE               = 0x060F00,
  TERRAN_CLOACK_GHOST                  = 0x070000,
  TERRAN_DECLOACK_GHOST                = 0x070001,
  TERRAN_SNIPER_ROUND                  = 0x070100,
  TERRAN_HEAL_MEDIVAC                  = 0x070200,
  TERRAN_SIEGE_MODE_SIEGE_TANK         = 0x070300,
  TERRAN_TANK_MODE_SIEGE_TANK          = 0x070400,
  TERRAN_CLOACK_BANSHEE                = 0x070500,
  TERRAN_DECLOACK_BANSHEE              = 0x070501,
  TERRAN_LOAD_MEDIVAC                  = 0x070600,
  TERRAN_UNLOAD_ALL_MEDIVAC            = 0x070602,
  TERRAN_YAMATO_CANNON                 = 0x070800,
  TERRAN_ASSAULT_MODE_VIKING           = 0x070900,
  TERRAN_FIGHTER_MODE_VIKING           = 0x070A00,
  TERRAN_UNLOAD_ALL_COMMAND_CENTER     = 0x070C01,
  TERRAN_LOAD_COMMAND_CENTER           = 0x070C04,
  TERRAN_LIFT_OFF_COMMAND_CENTER       = 0x070D00,
  TERRAN_LAND_COMMAND_CENTER           = 0x070E00,
  TERRAN_BUILD_TECH_LAB_BARRACKS       = 0x070F00,
  TERRAN_BUILD_REACTOR_BARRACKS        = 0x070F01,
  TERRAN_BUILD_TECH_LAB_FACTORY        = 0x080100,
  TERRAN_BUILD_TECH_LAB_STARPORT       = 0x080300,
  TERRAN_TRAIN_SCV                     = 0x080700,
  TERRAN_LOWER_SUPPLY_DEPOT            = 0x080900,
  TERRAN_RAISE_SUPPLY_DEPOT            = 0x080A00,
  TERRAN_TRAIN_MARINE                  = 0x080B00,
  TERRAN_TRAIN_REAPER                  = 0x080B01,
  TERRAN_TRAIN_GHOST                   = 0x080B02,
  TERRAN_TRAIN_MARAUDER                = 0x080B03,
  TERRAN_TRAIN_SIEGE_TANK              = 0x080C01,
  TERRAN_TRAIN_THOR                    = 0x080C04,
  TERRAN_TRAIN_HELLION                 = 0x080C05,
  TERRAN_TRAIN_MEDIVAC                 = 0x080D00,
  TERRAN_TRAIN_BANSHEE                 = 0x080D01,
  TERRAN_TRAIN_RAVEN                   = 0x080D02,
  TERRAN_TRAIN_BATTLECRUISER           = 0x080D03,
  TERRAN_TRAIN_VIKING                  = 0x080D04,
  TERRAN_UPGRADE_HI_SEC_AUTO_TRACKING  = 0x080E00,
  TERRAN_UPGRADE_BUILDING_ARMOR        = 0x080E01,
  TERRAN_UPGRADE_INFANTRY_WEAPONS_1    = 0x080E02,
  TERRAN_UPGRADE_INFANTRY_WEAPONS_2    = 0x080E03,
  TERRAN_UPGRADE_INFANTRY_WEAPONS_3    = 0x080E04,
  TERRAN_UPGRADE_INFANTRY_ARMOR_1      = 0x080E06,
  TERRAN_UPGRADE_INFANTRY_ARMOR_2      = 0x080E07,
  TERRAN_UPGRADE_INFANTRY_ARMOR_3      = 0x080E08,
  TERRAN_UPGRADE_NEOSTEEL_FRAME        = 0x080E05,
  TERRAN_RESEARCH_NITRO_PACKS          = 0x080F03,
  TERRAN_ARM_SILO_WITH_NUKE            = 0x090000,
  TERRAN_RESEARCH_STIMPACK             = 0x090100,
  TERRAN_RESEARCH_COMBAT_SHIELD        = 0x090101,
  TERRAN_RESEARCH_SIEGE_TECH           = 0x090200,
  TERRAN_RESEARCH_INFERNAL_PRE_IGNITER = 0x090201,
  TERRAN_RESEARCH_CLOACKING_FIELD      = 0x090300,
  TERRAN_RESEARCH_CADUCEUS_REACTOR     = 0x090302,
  TERRAN_RESEARCH_CORVID_REACTOR       = 0x090303,
  TERRAN_RESEARCH_SEEKER_MISSILES      = 0x090306,
  TERRAN_RESEARCH_DURABLE_MATERIALS    = 0x090307,
  TERRAN_RESEARCH_PERSONAL_CLOACKING   = 0x090400,
  TERRAN_RESEARCH_MOEBIUS_REACTOR      = 0x090401,
  TERRAN_UPGRADE_VEHICLE_PLATING_1     = 0x090502,
  TERRAN_UPGRADE_VEHICLE_PLATING_2     = 0x090503,
  TERRAN_UPGRADE_VEHICLE_PLATING_3     = 0x090504,
  TERRAN_UPGRADE_VEHICLE_WEAPONS_1     = 0x090505,
  TERRAN_UPGRADE_VEHICLE_WEAPONS_2     = 0x090506,
  TERRAN_UPGRADE_VEHICLE_WEAPONS_3     = 0x090507,
  TERRAN_UPGRADE_SHIP_WEAPONS_1        = 0x09050B,
  TERRAN_UPGRADE_SHIP_WEAPONS_2        = 0x09050C,
  TERRAN_UPGRADE_SHIP_WEAPONS_3        = 0x09050D,
  TERRAN_UPGRADE_SHIP_PLATING_1        = 0x090508,
  TERRAN_UPGRADE_SHIP_PLATING_2        = 0x090509,
  TERRAN_UPGRADE_SHIP_PLATING_3        = 0x09050A,
  TERRAN_UPGRADE_TO_PLANETARY_FORTRESS = 0x0C0700,
  TERRAN_RESEARCH_WEAPON_REFIT         = 0x0D0600,
  TERRAN_RESEARCH_BEHEMOTH_REACTOR     = 0x0D0601,
  TERRAN_TAC_NUCLEAR_STRIKE            = 0x0D0900,
  TERRAN_EMP_ROUND                     = 0x0D0C00,
  TERRAN_AUTO_TURRET                   = 0x0F0400,
};

struct GameEvent
{
  GameEvent( timestamp_t ti=0, EventType ty=INITIALIZATION, EventFlag fl=PLAYER, player_t pl=0, EventCode co=INITIALIZATION_SPAWN )
    : timestamp(ti), type(ty), flag(fl), player(pl), code(co) {}
  
  virtual void enable_dynamic_cast() const {}
  
  timestamp_t timestamp;
  EventType   type;
  EventFlag   flag;
  player_t    player;
  EventCode   code;
};

struct InitializationSpawn : public GameEvent
{
  InitializationSpawn( const GameEvent& e ) : GameEvent(e) {}
};

struct InitializationStart : public GameEvent
{
  InitializationStart( const GameEvent& e ) : GameEvent(e) {}
};

struct ActionQuit : public GameEvent
{
  ActionQuit( const GameEvent& e ) : GameEvent(e) {}
};

struct ActionAbility : public GameEvent
{
  ActionAbility( const GameEvent& e ) : GameEvent(e) {}
};

struct ActionSendResource : public GameEvent
{
  ActionSendResource( const GameEvent& e ) : GameEvent(e) {}
};

struct ActionSelection : public GameEvent
{
  ActionSelection( const GameEvent& e ) : GameEvent(e) {}
};

struct ActionUseHotkey : public GameEvent
{
  ActionUseHotkey( const GameEvent& e ) : GameEvent(e) {}
};

struct ActionUpdateHotkey : public GameEvent
{
  ActionUpdateHotkey( const GameEvent& e ) : GameEvent(e) {}
};

struct ReplayMoveCamera : public GameEvent
{
  ReplayMoveCamera( const GameEvent& e ) : GameEvent(e) {}
  
  uint32_t x;
  uint32_t y;
  uint32_t horizontal;
  uint32_t vertical;
  uint32_t unknown;
};

struct InactionSynchronization : public GameEvent
{
  InactionSynchronization( const GameEvent& e ) : GameEvent(e) {}
};

struct InactionSendRequest : public GameEvent
{
  InactionSendRequest( const GameEvent& e ) : GameEvent(e) {}
};

struct InactionCancelRequest : public GameEvent
{
  InactionCancelRequest( const GameEvent& e ) : GameEvent(e) {}
};

struct SystemSynchronization : public GameEvent
{
  SystemSynchronization( const GameEvent& e ) : GameEvent(e) {}
};

} // namespace sc2replay

#endif // SC2REPLAY_GAMEEVENTS_H
// Local Variables:
// mode:c++
// c-file-style: "stroustrup"
// end:

