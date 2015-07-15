/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

extern "C"
{
#include "lua.h"
};

// Eluna
#include "LuaEngine.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaUtility.h"
#include "LuaVal.h"

// Method includes
#include "GlobalMethods.h"
#include "ObjectMethods.h"
#include "WorldObjectMethods.h"
#include "UnitMethods.h"
#include "PlayerMethods.h"
#include "CreatureMethods.h"
#include "GroupMethods.h"
#include "GuildMethods.h"
#include "GameObjectMethods.h"
#include "ElunaQueryMethods.h"
#include "AuraMethods.h"
#include "ItemMethods.h"
#include "WorldPacketMethods.h"
#include "SpellMethods.h"
#include "QuestMethods.h"
#include "MapMethods.h"
#include "CorpseMethods.h"
#include "VehicleMethods.h"
#include "BattleGroundMethods.h"
#include "uint64Methods.h"

ElunaGlobal::ElunaRegister GlobalMethods[] =
{
    // Hooks
    { ENV_NONE, "RegisterServerEvent", &LuaGlobalFunctions::RegisterServerEvent },                       // RegisterServerEvent(event, function)
    { ENV_BOTH, "RegisterPlayerEvent", &LuaGlobalFunctions::RegisterPlayerEvent },                       // RegisterPlayerEvent(event, function)
    { ENV_NONE, "RegisterGuildEvent", &LuaGlobalFunctions::RegisterGuildEvent },                         // RegisterGuildEvent(event, function)
    { ENV_NONE, "RegisterGroupEvent", &LuaGlobalFunctions::RegisterGroupEvent },                         // RegisterGroupEvent(event, function)
    { ENV_NONE, "RegisterCreatureEvent", &LuaGlobalFunctions::RegisterCreatureEvent },                   // RegisterCreatureEvent(entry, event, function)
    { ENV_NONE, "RegisterUniqueCreatureEvent", &LuaGlobalFunctions::RegisterUniqueCreatureEvent },       // RegisterUniqueCreatureEvent(guid, instance, event, function)
    { ENV_NONE, "RegisterCreatureGossipEvent", &LuaGlobalFunctions::RegisterCreatureGossipEvent },       // RegisterCreatureGossipEvent(entry, event, function)
    { ENV_NONE, "RegisterGameObjectEvent", &LuaGlobalFunctions::RegisterGameObjectEvent },               // RegisterGameObjectEvent(entry, event, function)
    { ENV_NONE, "RegisterGameObjectGossipEvent", &LuaGlobalFunctions::RegisterGameObjectGossipEvent },   // RegisterGameObjectGossipEvent(entry, event, function)
    { ENV_NONE, "RegisterItemEvent", &LuaGlobalFunctions::RegisterItemEvent },                           // RegisterItemEvent(entry, event, function)
    { ENV_NONE, "RegisterItemGossipEvent", &LuaGlobalFunctions::RegisterItemGossipEvent },               // RegisterItemGossipEvent(entry, event, function)
    { ENV_NONE, "RegisterPlayerGossipEvent", &LuaGlobalFunctions::RegisterPlayerGossipEvent },           // RegisterPlayerGossipEvent(menu_id, event, function)
    { ENV_NONE, "RegisterBGEvent", &LuaGlobalFunctions::RegisterBGEvent },                               // RegisterBGEvent(event, function)

    { ENV_NONE, "ClearBattleGroundEvents", &LuaGlobalFunctions::ClearBattleGroundEvents },
    { ENV_NONE, "ClearCreatureEvents", &LuaGlobalFunctions::ClearCreatureEvents },
    { ENV_NONE, "ClearUniqueCreatureEvents", &LuaGlobalFunctions::ClearUniqueCreatureEvents },
    { ENV_NONE, "ClearCreatureGossipEvents", &LuaGlobalFunctions::ClearCreatureGossipEvents },
    { ENV_NONE, "ClearGameObjectEvents", &LuaGlobalFunctions::ClearGameObjectEvents },
    { ENV_NONE, "ClearGameObjectGossipEvents", &LuaGlobalFunctions::ClearGameObjectGossipEvents },
    { ENV_NONE, "ClearGroupEvents", &LuaGlobalFunctions::ClearGroupEvents },
    { ENV_NONE, "ClearGuildEvents", &LuaGlobalFunctions::ClearGuildEvents },
    { ENV_NONE, "ClearItemEvents", &LuaGlobalFunctions::ClearItemEvents },
    { ENV_NONE, "ClearItemGossipEvents", &LuaGlobalFunctions::ClearItemGossipEvents },
    { ENV_NONE, "ClearPlayerEvents", &LuaGlobalFunctions::ClearPlayerEvents },
    { ENV_NONE, "ClearPlayerGossipEvents", &LuaGlobalFunctions::ClearPlayerGossipEvents },
    { ENV_NONE, "ClearServerEvents", &LuaGlobalFunctions::ClearServerEvents },

    // Getters
    { ENV_BOTH, "GetMap", &LuaGlobalFunctions::GetMap },
    { ENV_BOTH, "GetLuaEngine", &LuaGlobalFunctions::GetLuaEngine },
    { ENV_BOTH, "GetCoreName", &LuaGlobalFunctions::GetCoreName },
    { ENV_BOTH, "GetCoreVersion", &LuaGlobalFunctions::GetCoreVersion },
    { ENV_BOTH, "GetCoreExpansion", &LuaGlobalFunctions::GetCoreExpansion },
    { ENV_BOTH, "GetQuest", &LuaGlobalFunctions::GetQuest },
    { ENV_NONE, "GetPlayerByGUID", &LuaGlobalFunctions::GetPlayerByGUID },
    { ENV_NONE, "GetPlayerByName", &LuaGlobalFunctions::GetPlayerByName },
    { ENV_BOTH, "GetGameTime", &LuaGlobalFunctions::GetGameTime },
    { ENV_WORLD, "GetPlayersInWorld", &LuaGlobalFunctions::GetPlayersInWorld },
    { ENV_NONE, "GetGuildByName", &LuaGlobalFunctions::GetGuildByName },
    { ENV_NONE, "GetGuildByLeaderGUID", &LuaGlobalFunctions::GetGuildByLeaderGUID },
    { ENV_NONE, "GetPlayerCount", &LuaGlobalFunctions::GetPlayerCount },
    { ENV_BOTH, "GetPlayerGUID", &LuaGlobalFunctions::GetPlayerGUID },
    { ENV_BOTH, "GetItemGUID", &LuaGlobalFunctions::GetItemGUID },
    { ENV_BOTH, "GetObjectGUID", &LuaGlobalFunctions::GetObjectGUID },
    { ENV_BOTH, "GetUnitGUID", &LuaGlobalFunctions::GetUnitGUID },
    { ENV_BOTH, "GetGUIDLow", &LuaGlobalFunctions::GetGUIDLow },
    { ENV_BOTH, "GetGUIDType", &LuaGlobalFunctions::GetGUIDType },
    { ENV_BOTH, "GetGUIDEntry", &LuaGlobalFunctions::GetGUIDEntry },
    { ENV_NONE, "GetAreaName", &LuaGlobalFunctions::GetAreaName },
    { ENV_BOTH, "bit_not", &LuaGlobalFunctions::bit_not },
    { ENV_BOTH, "bit_xor", &LuaGlobalFunctions::bit_xor },
    { ENV_BOTH, "bit_rshift", &LuaGlobalFunctions::bit_rshift },
    { ENV_BOTH, "bit_lshift", &LuaGlobalFunctions::bit_lshift },
    { ENV_BOTH, "bit_or", &LuaGlobalFunctions::bit_or },
    { ENV_BOTH, "bit_and", &LuaGlobalFunctions::bit_and },
    { ENV_BOTH, "GetItemLink", &LuaGlobalFunctions::GetItemLink },
    { ENV_WORLD, "GetMapById", &LuaGlobalFunctions::GetMapById },
    { ENV_BOTH, "GetCurrTime", &LuaGlobalFunctions::GetCurrTime },
    { ENV_BOTH, "GetTimeDiff", &LuaGlobalFunctions::GetTimeDiff },
    { ENV_BOTH, "PrintInfo", &LuaGlobalFunctions::PrintInfo },
    { ENV_BOTH, "PrintError", &LuaGlobalFunctions::PrintError },
    { ENV_BOTH, "PrintDebug", &LuaGlobalFunctions::PrintDebug },

    // Boolean
    { ENV_NONE, "IsInventoryPos", &LuaGlobalFunctions::IsInventoryPos },
    { ENV_NONE, "IsEquipmentPos", &LuaGlobalFunctions::IsEquipmentPos },
    { ENV_NONE, "IsBankPos", &LuaGlobalFunctions::IsBankPos },
    { ENV_NONE, "IsBagPos", &LuaGlobalFunctions::IsBagPos },

    // Other
    { ENV_NONE, "ReloadEluna", &LuaGlobalFunctions::ReloadEluna },
    { ENV_NONE, "SendWorldMessage", &LuaGlobalFunctions::SendWorldMessage },
    { ENV_NONE, "WorldDBQuery", &LuaGlobalFunctions::WorldDBQuery },
    { ENV_NONE, "WorldDBExecute", &LuaGlobalFunctions::WorldDBExecute },
    { ENV_NONE, "CharDBQuery", &LuaGlobalFunctions::CharDBQuery },
    { ENV_NONE, "CharDBExecute", &LuaGlobalFunctions::CharDBExecute },
    { ENV_NONE, "AuthDBQuery", &LuaGlobalFunctions::AuthDBQuery },
    { ENV_NONE, "AuthDBExecute", &LuaGlobalFunctions::AuthDBExecute },
    { ENV_NONE, "CreateLuaEvent", &LuaGlobalFunctions::CreateLuaEvent },
    { ENV_NONE, "RemoveEventById", &LuaGlobalFunctions::RemoveEventById },
    { ENV_NONE, "RemoveEvents", &LuaGlobalFunctions::RemoveEvents },
    { ENV_NONE, "PerformIngameSpawn", &LuaGlobalFunctions::PerformIngameSpawn },
    { ENV_NONE, "CreatePacket", &LuaGlobalFunctions::CreatePacket },
    { ENV_NONE, "AddVendorItem", &LuaGlobalFunctions::AddVendorItem },
    { ENV_NONE, "VendorRemoveItem", &LuaGlobalFunctions::VendorRemoveItem },
    { ENV_NONE, "VendorRemoveAllItems", &LuaGlobalFunctions::VendorRemoveAllItems },
    { ENV_NONE, "Kick", &LuaGlobalFunctions::Kick },
    { ENV_NONE, "Ban", &LuaGlobalFunctions::Ban },
    { ENV_NONE, "SaveAllPlayers", &LuaGlobalFunctions::SaveAllPlayers },
    { ENV_NONE, "SendMail", &LuaGlobalFunctions::SendMail },
    { ENV_NONE, "AddTaxiPath", &LuaGlobalFunctions::AddTaxiPath },
    { ENV_NONE, "AddCorpse", &LuaGlobalFunctions::AddCorpse },
    { ENV_NONE, "RemoveCorpse", &LuaGlobalFunctions::RemoveCorpse },
    { ENV_NONE, "ConvertCorpseForPlayer", &LuaGlobalFunctions::ConvertCorpseForPlayer },
    { ENV_NONE, "RemoveOldCorpses", &LuaGlobalFunctions::RemoveOldCorpses },
    { ENV_BOTH, "NewUint64", &LuaGlobalFunctions::NewUint64 },
    { ENV_BOTH, "StateChannelSend", &LuaGlobalFunctions::StateChannelSend },
    { ENV_BOTH, "StateChannelRegister", &LuaGlobalFunctions::StateChannelRegister },
    { ENV_BOTH, "StateChannelUnregister", &LuaGlobalFunctions::StateChannelUnregister },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Object> ObjectMethods[] =
{
    // Getters
    { ENV_NONE, "GetEntry", &LuaObject::GetEntry },                     // :GetEntry() - Returns the object's entryId
    { ENV_NONE, "GetGUID", &LuaObject::GetGUID },                       // :GetGUID() - Returns uint64 guid as hex string
    { ENV_NONE, "GetGUIDLow", &LuaObject::GetGUIDLow },                 // :GetGUIDLow() - Returns uint32 guid (low guid) that is used in database.
    { ENV_NONE, "GetInt32Value", &LuaObject::GetInt32Value },           // :GetInt32Value(index) - returns an int value from object fields
    { ENV_NONE, "GetUInt32Value", &LuaObject::GetUInt32Value },         // :GetUInt32Value(index) - returns an uint value from object fields
    { ENV_NONE, "GetFloatValue", &LuaObject::GetFloatValue },           // :GetFloatValue(index) - returns a float value from object fields
    { ENV_NONE, "GetByteValue", &LuaObject::GetByteValue },             // :GetByteValue(index, offset) - returns a byte value from object fields
    { ENV_NONE, "GetUInt16Value", &LuaObject::GetUInt16Value },         // :GetUInt16Value(index, offset) - returns a uint16 value from object fields
    { ENV_NONE, "GetUInt64Value", &LuaObject::GetUInt64Value },         // :GetUInt64Value(index) - returns a uint64 value from object fields
    { ENV_NONE, "GetScale", &LuaObject::GetScale },                     // :GetScale()
    { ENV_NONE, "GetTypeId", &LuaObject::GetTypeId },                   // :GetTypeId() - Returns the object's typeId

    // Setters
    { ENV_NONE, "SetInt32Value", &LuaObject::SetInt32Value },           // :SetInt32Value(index, value) - Sets an int value for the object
    { ENV_NONE, "SetUInt32Value", &LuaObject::SetUInt32Value },         // :SetUInt32Value(index, value) - Sets an uint value for the object
    { ENV_NONE, "UpdateUInt32Value", &LuaObject::UpdateUInt32Value },   // :UpdateUInt32Value(index, value) - Sets an uint value for the object
    { ENV_NONE, "SetFloatValue", &LuaObject::SetFloatValue },           // :SetFloatValue(index, value) - Sets a float value for the object
    { ENV_NONE, "SetByteValue", &LuaObject::SetByteValue },             // :SetByteValue(index, offset, value) - Sets a byte value for the object
    { ENV_NONE, "SetUInt16Value", &LuaObject::SetUInt16Value },         // :SetUInt16Value(index, offset, value) - Sets an uint16 value for the object
    { ENV_NONE, "SetInt16Value", &LuaObject::SetInt16Value },           // :SetInt16Value(index, offset, value) - Sets an int16 value for the object
    { ENV_NONE, "SetUInt64Value", &LuaObject::SetUInt64Value },         // :SetUInt64Value(index, value) - Sets an uint64 value for the object
    { ENV_NONE, "SetScale", &LuaObject::SetScale },                     // :SetScale(scale)
    { ENV_NONE, "SetFlag", &LuaObject::SetFlag },                       // :SetFlag(index, flag)

    // Boolean
    { ENV_NONE, "IsInWorld", &LuaObject::IsInWorld },                   // :IsInWorld() - Returns if the object is in world
    { ENV_NONE, "HasFlag", &LuaObject::HasFlag },                       // :HasFlag(index, flag)

    // Other
    { ENV_NONE, "ToGameObject", &LuaObject::ToGameObject },             // :ToGameObject()
    { ENV_NONE, "ToUnit", &LuaObject::ToUnit },                         // :ToUnit()
    { ENV_NONE, "ToCreature", &LuaObject::ToCreature },                 // :ToCreature()
    { ENV_NONE, "ToPlayer", &LuaObject::ToPlayer },                     // :ToPlayer()
    { ENV_NONE, "ToCorpse", &LuaObject::ToCorpse },                     // :ToCorpse()
    { ENV_NONE, "RemoveFlag", &LuaObject::RemoveFlag },                 // :RemoveFlag(index, flag)

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<WorldObject> WorldObjectMethods[] =
{
    // Getters
    { ENV_NONE, "GetName", &LuaWorldObject::GetName },                              // :GetName()
    { ENV_NONE, "GetMap", &LuaWorldObject::GetMap },                                // :GetMap() - Returns the WorldObject's current map object
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "GetPhaseMask", &LuaWorldObject::GetPhaseMask },                    // :GetPhaseMask()
#endif
    { ENV_NONE, "GetInstanceId", &LuaWorldObject::GetInstanceId },                  // :GetInstanceId()
    { ENV_NONE, "GetAreaId", &LuaWorldObject::GetAreaId },                          // :GetAreaId()
    { ENV_NONE, "GetZoneId", &LuaWorldObject::GetZoneId },                          // :GetZoneId()
    { ENV_NONE, "GetMapId", &LuaWorldObject::GetMapId },                            // :GetMapId() - Returns the WorldObject's current map ID
    { ENV_NONE, "GetX", &LuaWorldObject::GetX },                                    // :GetX()
    { ENV_NONE, "GetY", &LuaWorldObject::GetY },                                    // :GetY()
    { ENV_NONE, "GetZ", &LuaWorldObject::GetZ },                                    // :GetZ()
    { ENV_NONE, "GetO", &LuaWorldObject::GetO },                                    // :GetO()
    { ENV_NONE, "GetLocation", &LuaWorldObject::GetLocation },                      // :GetLocation() - returns X, Y, Z and O co - ords (in that order)
    { ENV_NONE, "GetPlayersInRange", &LuaWorldObject::GetPlayersInRange },          // :GetPlayersInRange([range]) - Returns a table with players in range of the WorldObject.
    { ENV_NONE, "GetCreaturesInRange", &LuaWorldObject::GetCreaturesInRange },      // :GetCreaturesInRange([range, entry]) - Returns a table with creatures of given entry in range of the WorldObject.
    { ENV_NONE, "GetGameObjectsInRange", &LuaWorldObject::GetGameObjectsInRange },  // :GetGameObjectsInRange([range, entry]) - Returns a table with gameobjects of given entry in range of the WorldObject.
    { ENV_NONE, "GetNearestPlayer", &LuaWorldObject::GetNearestPlayer },            // :GetNearestPlayer([range]) - Returns nearest player in sight or given range.
    { ENV_NONE, "GetNearestGameObject", &LuaWorldObject::GetNearestGameObject },    // :GetNearestGameObject([range, entry]) - Returns nearest gameobject with given entry in sight or given range entry can be 0 or nil for any.
    { ENV_NONE, "GetNearestCreature", &LuaWorldObject::GetNearestCreature },        // :GetNearestCreature([range, entry]) - Returns nearest creature with given entry in sight or given range entry can be 0 or nil for any.
    { ENV_NONE, "GetNearObject", &LuaWorldObject::GetNearObject },
    { ENV_NONE, "GetNearObjects", &LuaWorldObject::GetNearObjects },
    { ENV_NONE, "GetDistance", &LuaWorldObject::GetDistance },
    { ENV_NONE, "GetExactDistance", &LuaWorldObject::GetExactDistance },
    { ENV_NONE, "GetDistance2d", &LuaWorldObject::GetDistance2d },
    { ENV_NONE, "GetExactDistance2d", &LuaWorldObject::GetExactDistance2d },
    { ENV_NONE, "GetRelativePoint", &LuaWorldObject::GetRelativePoint },            // :GetRelativePoint(dist, rad) - Returns the x, y and z of a point dist away from worldobject.
    { ENV_NONE, "GetAngle", &LuaWorldObject::GetAngle },                            // :GetAngle(WorldObject or x, y) - Returns angle between world object and target or x and y coords.

    // Boolean
    { ENV_NONE, "IsWithinLoS", &LuaWorldObject::IsWithinLoS },

    // Other
    { ENV_NONE, "SummonGameObject", &LuaWorldObject::SummonGameObject },            // :SummonGameObject(entry, x, y, z, o[, respawnDelay]) - Spawns an object to location. Returns the object or nil
    { ENV_NONE, "SpawnCreature", &LuaWorldObject::SpawnCreature },                  // :SpawnCreature(entry, x, y, z, o[, spawnType, despawnDelay]) - Spawns a creature to location that despawns after given time (0 for infinite). Returns the creature or nil
    { ENV_NONE, "SendPacket", &LuaWorldObject::SendPacket },                        // :SendPacket(packet) - Sends a specified packet to everyone around
    { ENV_NONE, "RegisterEvent", &LuaWorldObject::RegisterEvent },
    { ENV_NONE, "RemoveEventById", &LuaWorldObject::RemoveEventById },
    { ENV_NONE, "RemoveEvents", &LuaWorldObject::RemoveEvents },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Unit> UnitMethods[] =
{
    // Getters
    { ENV_NONE, "GetLevel", &LuaUnit::GetLevel },                                   // :GetLevel()
    { ENV_NONE, "GetHealth", &LuaUnit::GetHealth },                                 // :GetHealth()
    { ENV_NONE, "GetDisplayId", &LuaUnit::GetDisplayId },                           // :GetDisplayId()
    { ENV_NONE, "GetNativeDisplayId", &LuaUnit::GetNativeDisplayId },               // :GetNativeDisplayId()
    { ENV_NONE, "GetPower", &LuaUnit::GetPower },                                   // :GetPower([type]) - returns power for power type. type can be omitted
    { ENV_NONE, "GetMaxPower", &LuaUnit::GetMaxPower },                             // :GetMaxPower([type]) - returns max power for power type. type can be omitted
    { ENV_NONE, "GetPowerType", &LuaUnit::GetPowerType },                           // :GetPowerType() - Returns the power type tye unit uses
    { ENV_NONE, "GetMaxHealth", &LuaUnit::GetMaxHealth },                           // :GetMaxHealth()
    { ENV_NONE, "GetHealthPct", &LuaUnit::GetHealthPct },                           // :GetHealthPct()
    { ENV_NONE, "GetPowerPct", &LuaUnit::GetPowerPct },                             // :GetPowerPct([type]) - returns power percent for power type. type can be omitted
    { ENV_NONE, "GetGender", &LuaUnit::GetGender },                                 // :GetGender() - returns the gender where male = 0 female = 1
    { ENV_NONE, "GetRace", &LuaUnit::GetRace },                                     // :GetRace()
    { ENV_NONE, "GetClass", &LuaUnit::GetClass },                                   // :GetClass()
    { ENV_NONE, "GetRaceAsString", &LuaUnit::GetRaceAsString },                     // :GetRaceAsString([locale])
    { ENV_NONE, "GetClassAsString", &LuaUnit::GetClassAsString },                   // :GetClassAsString([locale])
    { ENV_NONE, "GetAura", &LuaUnit::GetAura },                                     // :GetAura(spellID) - returns aura object
    { ENV_NONE, "GetCombatTime", &LuaUnit::GetCombatTime },                         // :GetCombatTime() - Returns how long the unit has been in combat
    { ENV_NONE, "GetFaction", &LuaUnit::GetFaction },                               // :GetFaction() - Returns the unit's factionId
    { ENV_NONE, "GetCurrentSpell", &LuaUnit::GetCurrentSpell },                     // :GetCurrentSpell(type) - Returns the currently casted spell of given type if any
    { ENV_NONE, "GetCreatureType", &LuaUnit::GetCreatureType },                     // :GetCreatureType() - Returns the unit's type
    { ENV_NONE, "GetMountId", &LuaUnit::GetMountId },                               // :GetMountId()
    { ENV_NONE, "GetOwner", &LuaUnit::GetOwner },                                   // :GetOwner() - Returns the owner
    { ENV_NONE, "GetFriendlyUnitsInRange", &LuaUnit::GetFriendlyUnitsInRange },     // :GetFriendlyUnitsInRange([range]) - Returns a list of friendly units in range, can return nil
    { ENV_NONE, "GetUnfriendlyUnitsInRange", &LuaUnit::GetUnfriendlyUnitsInRange }, // :GetUnfriendlyUnitsInRange([range]) - Returns a list of unfriendly units in range, can return nil
    { ENV_NONE, "GetOwnerGUID", &LuaUnit::GetOwnerGUID },                           // :GetOwnerGUID() - Returns the UNIT_FIELD_SUMMONEDBY owner
    { ENV_NONE, "GetCreatorGUID", &LuaUnit::GetCreatorGUID },                       // :GetCreatorGUID() - Returns the UNIT_FIELD_CREATEDBY creator
    { ENV_NONE, "GetMinionGUID", &LuaUnit::GetPetGUID },                            // :GetMinionGUID() - Decapreted. GetMinionGUID is same as GetPetGUID
    { ENV_NONE, "GetCharmerGUID", &LuaUnit::GetCharmerGUID },                       // :GetCharmerGUID() - Returns the UNIT_FIELD_CHARMEDBY charmer
    { ENV_NONE, "GetCharmGUID", &LuaUnit::GetCharmGUID },                           // :GetCharmGUID() - Returns the unit's UNIT_FIELD_CHARM guid
    { ENV_NONE, "GetPetGUID", &LuaUnit::GetPetGUID },                               // :GetPetGUID() - Returns the unit's pet GUID
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "GetCritterGUID", &LuaUnit::GetCritterGUID },                       // :GetCritterGUID() - Returns the critter's GUID
#endif
    { ENV_NONE, "GetControllerGUID", &LuaUnit::GetControllerGUID },                 // :GetControllerGUID() - Returns the Charmer or Owner GUID
    { ENV_NONE, "GetControllerGUIDS", &LuaUnit::GetControllerGUIDS },               // :GetControllerGUIDS() - Returns the charmer, owner or unit's own GUID
    { ENV_NONE, "GetStandState", &LuaUnit::GetStandState },                         // :GetStandState() - Returns the unit's stand state
    { ENV_NONE, "GetVictim", &LuaUnit::GetVictim },                                 // :GetVictim() - Returns creature's current target
    { ENV_NONE, "GetSpeed", &LuaUnit::GetSpeed },                                   // :GetSpeed(movementType) - Returns the unit's speed
    { ENV_NONE, "GetStat", &LuaUnit::GetStat },                                     // :GetStat(stat)
    { ENV_NONE, "GetBaseSpellPower", &LuaUnit::GetBaseSpellPower },                 // :GetBaseSpellPower()
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "GetVehicleKit", &LuaUnit::GetVehicleKit },                         // :GetVehicleKit() - Gets unit's Vehicle kit if the unit is a vehicle
    // { "GetVehicle", &LuaUnit::GetVehicle },                            // :GetVehicle() - Gets the Vehicle kit of the vehicle the unit is on
#endif
#ifdef MANGOS
    { ENV_NONE, "GetMovementType", &LuaUnit::GetMovementType },
#endif

    // Setters
    { ENV_NONE, "SetFaction", &LuaUnit::SetFaction },                   // :SetFaction(factionId) - Sets the unit's faction
    { ENV_NONE, "SetLevel", &LuaUnit::SetLevel },                       // :SetLevel(amount)
    { ENV_NONE, "SetHealth", &LuaUnit::SetHealth },                     // :SetHealth(amount)
    { ENV_NONE, "SetMaxHealth", &LuaUnit::SetMaxHealth },               // :SetMaxHealth(amount)
    { ENV_NONE, "SetPower", &LuaUnit::SetPower },                       // :SetPower([type,] amount)
    { ENV_NONE, "SetMaxPower", &LuaUnit::SetMaxPower },                 // :SetMaxPower([type,] amount)
    { ENV_NONE, "SetPowerType", &LuaUnit::SetPowerType },               // :SetPowerType(type)
    { ENV_NONE, "SetDisplayId", &LuaUnit::SetDisplayId },               // :SetDisplayId(id)
    { ENV_NONE, "SetNativeDisplayId", &LuaUnit::SetNativeDisplayId },   // :SetNativeDisplayId(id)
    { ENV_NONE, "SetFacing", &LuaUnit::SetFacing },                     // :SetFacing(o) - Sets the Unit facing / orientation to arg
    { ENV_NONE, "SetFacingToObject", &LuaUnit::SetFacingToObject },     // :SetFacingToObject(worldObject) - Sets the Unit facing / orientation towards the WorldObject
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "SetPhaseMask", &LuaUnit::SetPhaseMask },               // :SetPhaseMask(Phase[, update]) - Sets the phase of the unit
#endif
    { ENV_NONE, "SetSpeed", &LuaUnit::SetSpeed },                       // :SetSpeed(type, speed[, forced]) - Sets speed for the movement type (0 = walk, 1 = run ..)
    // { "SetStunned", &LuaUnit::SetStunned },                // :SetStunned([enable]) - Stuns or removes stun
    { ENV_NONE, "SetRooted", &LuaUnit::SetRooted },                       // :SetRooted([enable]) - Roots or removes root
    { ENV_NONE, "SetConfused", &LuaUnit::SetConfused },                   // :SetConfused([enable]) - Sets confused or removes confusion
    { ENV_NONE, "SetFeared", &LuaUnit::SetFeared },                       // :SetFeared([enable]) - Fears or removes fear
    { ENV_NONE, "SetPvP", &LuaUnit::SetPvP },                           // :SetPvP([apply]) - Sets the units PvP on or off
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "SetFFA", &LuaUnit::SetFFA },                           // :SetFFA([apply]) - Sets the units FFA tag on or off
    { ENV_NONE, "SetSanctuary", &LuaUnit::SetSanctuary },               // :SetSanctuary([apply]) - Enables or disables units sanctuary flag
#endif
    // { "SetCanFly", &LuaUnit::SetCanFly },                  // :SetCanFly(apply)
    // { "SetVisible", &LuaUnit::SetVisible },                // :SetVisible(x)
    { ENV_NONE, "SetOwnerGUID", &LuaUnit::SetOwnerGUID },               // :SetOwnerGUID(guid) - Sets the guid of the owner
    { ENV_NONE, "SetName", &LuaUnit::SetName },                         // :SetName(name) - Sets the unit's name
    { ENV_NONE, "SetSheath", &LuaUnit::SetSheath },                     // :SetSheath(SheathState) - Sets unit's sheathstate
    { ENV_NONE, "SetCreatorGUID", &LuaUnit::SetCreatorGUID },           // :SetOwnerGUID(uint64 ownerGUID) - Sets the owner's guid of a summoned creature, etc
    { ENV_NONE, "SetMinionGUID", &LuaUnit::SetPetGUID },                // Decapreted. Same as SetPetGUID
    { ENV_NONE, "SetCharmerGUID", &LuaUnit::SetCharmerGUID },           // :SetCharmerGUID(uint64 ownerGUID) - Sets the UNIT_FIELD_CHARMEDBY charmer GUID
    { ENV_NONE, "SetPetGUID", &LuaUnit::SetPetGUID },                   // :SetPetGUID(uint64 guid) - Sets the pet's guid
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "SetCritterGUID", &LuaUnit::SetCritterGUID },           // :SetCritterGUID(uint64 guid) - Sets the critter's guid
#endif
    { ENV_NONE, "SetWaterWalk", &LuaUnit::SetWaterWalk },               // :SetWaterWalk([enable]) - Sets WaterWalk on or off
    { ENV_NONE, "SetStandState", &LuaUnit::SetStandState },             // :SetStandState(state) - Sets the stand state (Stand, Kneel, sleep, etc) of the unit

    // Boolean
    { ENV_NONE, "IsAlive", &LuaUnit::IsAlive },                                 // :IsAlive()
    { ENV_NONE, "IsDead", &LuaUnit::IsDead },                                   // :IsDead() - Returns true if the unit is dead, false if they are alive
    { ENV_NONE, "IsDying", &LuaUnit::IsDying },                                 // :IsDying() - Returns true if the unit death state is JUST_DIED.
    { ENV_NONE, "IsPvPFlagged", &LuaUnit::IsPvPFlagged },                       // :IsPvPFlagged()
    { ENV_NONE, "IsInCombat", &LuaUnit::IsInCombat },                           // :IsInCombat()
    { ENV_NONE, "IsBanker", &LuaUnit::IsBanker },                               // :IsBanker() - Returns true if the unit is a banker, false if not
    { ENV_NONE, "IsBattleMaster", &LuaUnit::IsBattleMaster },                   // :IsBattleMaster() - Returns true if the unit is a battle master, false if not
    { ENV_NONE, "IsCharmed", &LuaUnit::IsCharmed },                             // :IsCharmed() - Returns true if the unit is charmed, false if not
    { ENV_NONE, "IsArmorer", &LuaUnit::IsArmorer },                             // :IsArmorer() - Returns true if the unit is an Armorer, false if not
    { ENV_NONE, "IsAttackingPlayer", &LuaUnit::IsAttackingPlayer },             // :IsAttackingPlayer() - Returns true if the unit is attacking a player, false if not
    { ENV_NONE, "IsInWater", &LuaUnit::IsInWater },                             // :IsInWater() - Returns true if the unit is in water
    { ENV_NONE, "IsUnderWater", &LuaUnit::IsUnderWater },                       // :IsUnderWater() - Returns true if the unit is under water
    { ENV_NONE, "IsAuctioneer", &LuaUnit::IsAuctioneer },                       // :IsAuctioneer()
    { ENV_NONE, "IsGuildMaster", &LuaUnit::IsGuildMaster },                     // :IsGuildMaster()
    { ENV_NONE, "IsInnkeeper", &LuaUnit::IsInnkeeper },                         // :IsInnkeeper()
    { ENV_NONE, "IsTrainer", &LuaUnit::IsTrainer },                             // :IsTrainer()
    { ENV_NONE, "IsGossip", &LuaUnit::IsGossip },                               // :IsGossip()
    { ENV_NONE, "IsTaxi", &LuaUnit::IsTaxi },                                   // :IsTaxi()
    { ENV_NONE, "IsSpiritHealer", &LuaUnit::IsSpiritHealer },                   // :IsSpiritHealer()
    { ENV_NONE, "IsSpiritGuide", &LuaUnit::IsSpiritGuide },                     // :IsSpiritGuide()
    { ENV_NONE, "IsTabardDesigner", &LuaUnit::IsTabardDesigner },               // :IsTabardDesigner()
    { ENV_NONE, "IsServiceProvider", &LuaUnit::IsServiceProvider },             // :IsServiceProvider()
    { ENV_NONE, "IsSpiritService", &LuaUnit::IsSpiritService },                 // :IsSpiritService()
    { ENV_NONE, "HealthBelowPct", &LuaUnit::HealthBelowPct },                   // :HealthBelowPct(int32 pct)
    { ENV_NONE, "HealthAbovePct", &LuaUnit::HealthAbovePct },                   // :HealthAbovePct(int32 pct)
    { ENV_NONE, "IsMounted", &LuaUnit::IsMounted },                             // :IsMounted()
    { ENV_NONE, "AttackStop", &LuaUnit::AttackStop },                           // :AttackStop()
    { ENV_NONE, "Attack", &LuaUnit::Attack },                                   // :Attack(who[, meleeAttack])
    // { "IsVisible", &LuaUnit::IsVisible },                          // :IsVisible()
    // { "IsMoving", &LuaUnit::IsMoving },                            // :IsMoving()
    // { "IsFlying", &LuaUnit::IsFlying },                            // :IsFlying()
    { ENV_NONE, "IsStopped", &LuaUnit::IsStopped },                             // :IsStopped()
    { ENV_NONE, "HasUnitState", &LuaUnit::HasUnitState },                       // :HasUnitState(state) - state from UnitState enum
    { ENV_NONE, "IsQuestGiver", &LuaUnit::IsQuestGiver },                       // :IsQuestGiver() - Returns true if the unit is a quest giver, false if not
    { ENV_NONE, "IsWithinDistInMap", &LuaUnit::IsWithinDistInMap },             // :IsWithinDistInMap(worldObject, radius) - Returns if the unit is within distance in map of the worldObject
    { ENV_NONE, "IsInAccessiblePlaceFor", &LuaUnit::IsInAccessiblePlaceFor },   // :IsInAccessiblePlaceFor(creature) - Returns if the unit is in an accessible place for the specified creature
    { ENV_NONE, "IsVendor", &LuaUnit::IsVendor },                               // :IsVendor() - Returns if the unit is a vendor or not
    { ENV_NONE, "IsRooted", &LuaUnit::IsRooted },                               // :IsRooted()
    { ENV_NONE, "IsFullHealth", &LuaUnit::IsFullHealth },                       // :IsFullHealth() - Returns if the unit is full health
    { ENV_NONE, "HasAura", &LuaUnit::HasAura },                                 // :HasAura(spellId) - Returns true if the unit has the aura from the spell
    { ENV_NONE, "IsStandState", &LuaUnit::IsStandState },                       // :IsStandState() - Returns true if the unit is standing
#ifndef CLASSIC
    { ENV_NONE, "IsOnVehicle", &LuaUnit::IsOnVehicle },                         // :IsOnVehicle() - Checks if the unit is on a vehicle
#endif

    // Other
    { ENV_NONE, "AddAura", &LuaUnit::AddAura },                                 // :AddAura(spellId, target) - Adds an aura to the specified target
    { ENV_NONE, "RemoveAura", &LuaUnit::RemoveAura },                           // :RemoveAura(spellId[, casterGUID]) - Removes an aura from the unit by the spellId, casterGUID(Original caster) is optional
    { ENV_NONE, "RemoveAllAuras", &LuaUnit::RemoveAllAuras },                   // :RemoveAllAuras() - Removes all the unit's auras
    { ENV_NONE, "ClearInCombat", &LuaUnit::ClearInCombat },                     // :ClearInCombat() - Clears the unit's combat list (unit will be out of combat), resets the timer to 0, etc
    { ENV_NONE, "DeMorph", &LuaUnit::DeMorph },                                 // :DeMorph() - Sets display back to native
    { ENV_NONE, "SendUnitWhisper", &LuaUnit::SendUnitWhisper },                 // :SendUnitWhisper(msg, lang, receiver[, bossWhisper]) - Sends a whisper to the receiver
    { ENV_NONE, "SendUnitEmote", &LuaUnit::SendUnitEmote },                     // :SendUnitEmote(msg[, receiver, bossEmote]) - Sends a text emote
    { ENV_NONE, "SendUnitSay", &LuaUnit::SendUnitSay },                         // :SendUnitSay(msg, language) - Sends a "Say" message with the specified language (all languages: 0)
    { ENV_NONE, "SendUnitYell", &LuaUnit::SendUnitYell },                       // :SendUnitYell(msg, language) - Sends a "Yell" message with the specified language (all languages: 0)
    { ENV_NONE, "CastSpell", &LuaUnit::CastSpell },                             // :CastSpell(target, spellID[, triggered]) - Casts spell on target (player/npc/creature), if triggered is true then instant cast
    { ENV_NONE, "CastCustomSpell", &LuaUnit::CastCustomSpell },                 // :CastCustomSpell([Unit] target, uint32 spell, bool triggered = false, int32 bp0 = nil, int32 bp1 = nil, int32 bp2 = nil, [Item] castItem = nil, uint64 originalCaster = 0) - Casts spell on target (player/npc/creature), if triggered is true then instant cast. pb0, 1 and 2 are modifiers for the base points of the spell.
    { ENV_NONE, "CastSpellAoF", &LuaUnit::CastSpellAoF },                       // :CastSpellAoF(x, y, z, spellID[, triggered]) - Casts the spell on coordinates, if triggered is false has mana cost and cast time
    { ENV_NONE, "PlayDirectSound", &LuaUnit::PlayDirectSound },                 // :PlayDirectSound(soundId[, player]) - Unit plays soundID to player, or everyone around if no player
    { ENV_NONE, "PlayDistanceSound", &LuaUnit::PlayDistanceSound },             // :PlayDistanceSound(soundId[, player]) - Unit plays soundID to player, or everyone around if no player. The sound fades the further you are
    { ENV_NONE, "Kill", &LuaUnit::Kill },                                       // :Kill(target, durabilityLoss) - Unit kills the target. Durabilityloss is true by default
    { ENV_NONE, "StopSpellCast", &LuaUnit::StopSpellCast },                     // :StopSpellCast([spellId]) - Stops the unit from casting a spell. If a spellId is defined, it will stop that unit from casting that spell
    { ENV_NONE, "InterruptSpell", &LuaUnit::InterruptSpell },                   // :InterruptSpell(spellType[, delayed]) - Interrupts the unit's spell by the spellType. If delayed is true it will skip if the spell is delayed.
    { ENV_NONE, "SendChatMessageToPlayer", &LuaUnit::SendChatMessageToPlayer }, // :SendChatMessageToPlayer(type, lang, msg, target) - Unit sends a chat message to the given target player
    { ENV_NONE, "Emote", &LuaUnit::Emote },                                     // :Emote(emote)
    { ENV_NONE, "CountPctFromCurHealth", &LuaUnit::CountPctFromCurHealth },     // :CountPctFromCurHealth(int32 pct)
    { ENV_NONE, "CountPctFromMaxHealth", &LuaUnit::CountPctFromMaxHealth },     // :CountPctFromMaxHealth()
    { ENV_NONE, "Dismount", &LuaUnit::Dismount },                               // :Dismount() - Dismounts the unit.
    { ENV_NONE, "Mount", &LuaUnit::Mount },                                     // :Mount(displayId) - Mounts the unit on the specified displayId.
    // { "RestoreDisplayId", &LuaUnit::RestoreDisplayId },            // :RestoreDisplayId()
    // { "RestoreFaction", &LuaUnit::RestoreFaction },                // :RestoreFaction()
    // { "RemoveBindSightAuras", &LuaUnit::RemoveBindSightAuras },    // :RemoveBindSightAuras()
    // { "RemoveCharmAuras", &LuaUnit::RemoveCharmAuras },            // :RemoveCharmAuras()
    { ENV_NONE, "ClearThreatList", &LuaUnit::ClearThreatList },                 // :ClearThreatList()
    { ENV_NONE, "ClearUnitState", &LuaUnit::ClearUnitState },                   // :ClearUnitState(state)
    { ENV_NONE, "AddUnitState", &LuaUnit::AddUnitState },                       // :AddUnitState(state)
    // { "DisableMelee", &LuaUnit::DisableMelee },                    // :DisableMelee([disable]) - if true, enables
    // { "SummonGuardian", &LuaUnit::SummonGuardian },                // :SummonGuardian(entry, x, y, z, o[, duration]) - summons a guardian to location. Scales with summoner, is friendly to him and guards him.
    { ENV_NONE, "NearTeleport", &LuaUnit::NearTeleport },                       // :NearTeleport(x, y, z, o) - Teleports to give coordinates. Does not leave combat or unsummon pet.
    { ENV_NONE, "MoveIdle", &LuaUnit::MoveIdle },                               // :MoveIdle()
    { ENV_NONE, "MoveRandom", &LuaUnit::MoveRandom },                           // :MoveRandom(radius)
    { ENV_NONE, "MoveHome", &LuaUnit::MoveHome },                               // :MoveHome()
    { ENV_NONE, "MoveFollow", &LuaUnit::MoveFollow },                           // :MoveFollow(target[, dist, angle])
    { ENV_NONE, "MoveChase", &LuaUnit::MoveChase },                             // :MoveChase(target[, dist, angle])
    { ENV_NONE, "MoveConfused", &LuaUnit::MoveConfused },                       // :MoveConfused()
    { ENV_NONE, "MoveFleeing", &LuaUnit::MoveFleeing },                         // :MoveFleeing(enemy[, time])
    { ENV_NONE, "MoveTo", &LuaUnit::MoveTo },                                   // :MoveTo(id, x, y, z[, genPath]) - Moves to point. id is sent to WP reach hook. genPath defaults to true
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "MoveJump", &LuaUnit::MoveJump },                               // :MoveJump(x, y, z, zSpeed, maxHeight, id)
#endif
    { ENV_NONE, "MoveStop", &LuaUnit::MoveStop },                               // :MoveStop()
    { ENV_NONE, "MoveExpire", &LuaUnit::MoveExpire },                           // :MoveExpire([reset])
    { ENV_NONE, "MoveClear", &LuaUnit::MoveClear },                             // :MoveClear([reset])
    { ENV_NONE, "DealDamage", &LuaUnit::DealDamage },                           // :DealDamage(target, amount[, durabilityloss]) - Deals damage to target, durabilityloss is true by default
    { ENV_NONE, "DealHeal", &LuaUnit::DealHeal },                               // :DealDamage(target, amount, spell[, critical]) - Heals target by given amount. This will be logged as being healed by spell as critical if true.
    { ENV_NONE, "AddThreat", &LuaUnit::AddThreat },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Player> PlayerMethods[] =
{
    // Getters
    { ENV_NONE, "GetSelection", &LuaPlayer::GetSelection },                                 // :GetSelection()
    { ENV_NONE, "GetGMRank", &LuaPlayer::GetGMRank },                                       // :GetSecurity()
    { ENV_NONE, "GetGuildId", &LuaPlayer::GetGuildId },                                     // :GetGuildId() - nil on no guild
    { ENV_NONE, "GetCoinage", &LuaPlayer::GetCoinage },                                     // :GetCoinage()
    { ENV_NONE, "GetTeam", &LuaPlayer::GetTeam },                                           // :GetTeam() - returns the player's team. 0 for ally, 1 for horde
    { ENV_NONE, "GetItemCount", &LuaPlayer::GetItemCount },                                 // :GetItemCount(item_id[, check_bank])
    { ENV_NONE, "GetGroup", &LuaPlayer::GetGroup },                                         // :GetGroup()
    { ENV_NONE, "GetGuild", &LuaPlayer::GetGuild },                                         // :GetGuild()
    { ENV_NONE, "GetAccountId", &LuaPlayer::GetAccountId },                                 // :GetAccountId()
    { ENV_NONE, "GetAccountName", &LuaPlayer::GetAccountName },                             // :GetAccountName()
#ifndef CATA
#ifndef CLASSIC
    { ENV_NONE, "GetArenaPoints", &LuaPlayer::GetArenaPoints },                             // :GetArenaPoints()
    { ENV_NONE, "GetHonorPoints", &LuaPlayer::GetHonorPoints },                             // :GetHonorPoints()
#endif
#endif
    { ENV_NONE, "GetLifetimeKills", &LuaPlayer::GetLifetimeKills },                         // :GetLifetimeKills() - Returns the player's lifetime (honorable) kills
    { ENV_NONE, "GetPlayerIP", &LuaPlayer::GetPlayerIP },                                   // :GetPlayerIP() - Returns the player's IP Address
    { ENV_NONE, "GetLevelPlayedTime", &LuaPlayer::GetLevelPlayedTime },                     // :GetLevelPlayedTime() - Returns the player's played time at that level
    { ENV_NONE, "GetTotalPlayedTime", &LuaPlayer::GetTotalPlayedTime },                     // :GetTotalPlayedTime() - Returns the total played time of that player
    { ENV_NONE, "GetItemByPos", &LuaPlayer::GetItemByPos },                                 // :GetItemByPos(bag, slot) - Returns item in given slot in a bag (bag: 19-22 slot: 0-35) or inventory (bag: 255 slot : 0-38)
    { ENV_NONE, "GetItemByEntry", &LuaPlayer::GetItemByEntry },                             // :GetItemByEntry(entry) - Gets an item if the player has it
    { ENV_NONE, "GetItemByGUID", &LuaPlayer::GetItemByGUID },
    { ENV_NONE, "GetReputation", &LuaPlayer::GetReputation },                               // :GetReputation(faction) - Gets player's reputation with given faction
    { ENV_NONE, "GetEquippedItemBySlot", &LuaPlayer::GetEquippedItemBySlot },               // :GetEquippedItemBySlot(slotId) - Returns equipped item by slot
    { ENV_NONE, "GetQuestLevel", &LuaPlayer::GetQuestLevel },                               // :GetQuestLevel(quest) - Returns quest's level
    { ENV_NONE, "GetChatTag", &LuaPlayer::GetChatTag },                                     // :GetChatTag() - Returns player chat tag ID
    { ENV_NONE, "GetRestBonus", &LuaPlayer::GetRestBonus },                                 // :GetRestBonus() - Gets player's rest bonus
    { ENV_NONE, "GetRestType", &LuaPlayer::GetRestType },                                   // :GetRestType() - Returns the player's rest type
#ifdef WOTLK
    { ENV_NONE, "GetPhaseMaskForSpawn", &LuaPlayer::GetPhaseMaskForSpawn },                 // :GetPhaseMaskForSpawn() - Gets the real phasemask for spawning things. Used if the player is in GM mode
#endif
    { ENV_NONE, "GetReqKillOrCastCurrentCount", &LuaPlayer::GetReqKillOrCastCurrentCount }, // :GetReqKillOrCastCurrentCount(questId, entry) - Gets the objective (kill or cast) current count done
    { ENV_NONE, "GetQuestStatus", &LuaPlayer::GetQuestStatus },                             // :GetQuestStatus(entry) - Gets the quest's status
    { ENV_NONE, "GetInGameTime", &LuaPlayer::GetInGameTime },                               // :GetInGameTime() - Returns player's ingame time
    { ENV_NONE, "GetComboPoints", &LuaPlayer::GetComboPoints },                             // :GetComboPoints() - Returns player's combo points
    { ENV_NONE, "GetComboTarget", &LuaPlayer::GetComboTarget },                             // :GetComboTarget() - Returns the player's combo target
    { ENV_NONE, "GetGuildName", &LuaPlayer::GetGuildName },                                 // :GetGuildName() - Returns player's guild's name or nil
    { ENV_NONE, "GetFreeTalentPoints", &LuaPlayer::GetFreeTalentPoints },                   // :GetFreeTalentPoints() - Returns the amount of unused talent points
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "GetActiveSpec", &LuaPlayer::GetActiveSpec },                               // :GetActiveSpec() - Returns the active specID
    { ENV_NONE, "GetSpecsCount", &LuaPlayer::GetSpecsCount },                               // :GetSpecsCount() - Returns the player's spec count
#endif
    { ENV_NONE, "GetSpellCooldownDelay", &LuaPlayer::GetSpellCooldownDelay },               // :GetSpellCooldownDelay(spellId) - Returns the spell's cooldown
    { ENV_NONE, "GetGuildRank", &LuaPlayer::GetGuildRank },                                 // :GetGuildRank() - Gets the player's guild rank
    { ENV_NONE, "GetDifficulty", &LuaPlayer::GetDifficulty },                               // :GetDifficulty([isRaid]) - Returns the current difficulty
    { ENV_NONE, "GetHealthBonusFromStamina", &LuaPlayer::GetHealthBonusFromStamina },       // :GetHealthBonusFromStamina() - Returns the HP bonus from stamina
    { ENV_NONE, "GetManaBonusFromIntellect", &LuaPlayer::GetManaBonusFromIntellect },       // :GetManaBonusFromIntellect() - Returns the mana bonus from intellect
    { ENV_NONE, "GetMaxSkillValue", &LuaPlayer::GetMaxSkillValue },                         // :GetMaxSkillValue(skill) - Gets max skill value for the given skill
    { ENV_NONE, "GetPureMaxSkillValue", &LuaPlayer::GetPureMaxSkillValue },                 // :GetPureMaxSkillValue(skill) - Gets max base skill value
    { ENV_NONE, "GetSkillValue", &LuaPlayer::GetSkillValue },                               // :GetSkillValue(skill) - Gets current skill value
    { ENV_NONE, "GetBaseSkillValue", &LuaPlayer::GetBaseSkillValue },                       // :GetBaseSkillValue(skill) - Gets current base skill value (no temp bonus)
    { ENV_NONE, "GetPureSkillValue", &LuaPlayer::GetPureSkillValue },                       // :GetPureSkillValue(skill) - Gets current base skill value (no bonuses)
    { ENV_NONE, "GetSkillPermBonusValue", &LuaPlayer::GetSkillPermBonusValue },             // :GetSkillPermBonusValue(skill) - Returns current permanent bonus
    { ENV_NONE, "GetSkillTempBonusValue", &LuaPlayer::GetSkillTempBonusValue },             // :GetSkillTempBonusValue(skill) - Returns current temp bonus
    { ENV_NONE, "GetReputationRank", &LuaPlayer::GetReputationRank },                       // :GetReputationRank(faction) - Returns the reputation rank with given faction
    { ENV_NONE, "GetDrunkValue", &LuaPlayer::GetDrunkValue },                               // :GetDrunkValue() - Returns the current drunkness value
    { ENV_NONE, "GetBattlegroundId", &LuaPlayer::GetBattlegroundId },                       // :GetBattlegroundId() - Returns the player's current battleground ID
    { ENV_NONE, "GetBattlegroundTypeId", &LuaPlayer::GetBattlegroundTypeId },               // :GetBattlegroundTypeId() - Returns the player's current battleground type ID
    { ENV_NONE, "GetXPRestBonus", &LuaPlayer::GetXPRestBonus },                             // :GetXPRestBonus(xp) - Returns the rested bonus XP from given XP
    { ENV_NONE, "GetRestTime", &LuaPlayer::GetRestTime },                                   // :GetRestTime() - Returns the timed rested
    { ENV_NONE, "GetGroupInvite", &LuaPlayer::GetGroupInvite },                             // :GetGroupInvite() - Returns the group invited to
    { ENV_NONE, "GetSubGroup", &LuaPlayer::GetSubGroup },                                   // :GetSubGroup() - Gets the player's current subgroup ID
    { ENV_NONE, "GetNextRandomRaidMember", &LuaPlayer::GetNextRandomRaidMember },           // :GetNextRandomRaidMember(radius) - Gets a random raid member in given radius
    { ENV_NONE, "GetOriginalGroup", &LuaPlayer::GetOriginalGroup },                         // :GetOriginalGroup() - Gets the original group object
    { ENV_NONE, "GetOriginalSubGroup", &LuaPlayer::GetOriginalSubGroup },                   // :GetOriginalSubGroup() - Returns the original subgroup ID
#ifdef TRINITY
    { ENV_NONE, "GetChampioningFaction", &LuaPlayer::GetChampioningFaction },               // :GetChampioningFaction() - Returns the player's championing faction
#endif
    { ENV_NONE, "GetLatency", &LuaPlayer::GetLatency },                                     // :GetLatency() - Returns player's latency
    // { "GetRecruiterId", &LuaPlayer::GetRecruiterId },                          // :GetRecruiterId() - Returns player's recruiter's ID
    { ENV_NONE, "GetDbLocaleIndex", &LuaPlayer::GetDbLocaleIndex },                         // :GetDbLocaleIndex() - Returns locale index
    { ENV_NONE, "GetDbcLocale", &LuaPlayer::GetDbcLocale },                                 // :GetDbcLocale() - Returns DBC locale
    { ENV_NONE, "GetCorpse", &LuaPlayer::GetCorpse },                                       // :GetCorpse() - Returns the player's corpse
    { ENV_NONE, "GetGossipTextId", &LuaPlayer::GetGossipTextId },                           // :GetGossipTextId(worldObject) - Returns the WorldObject's gossip textId
    { ENV_NONE, "GetQuestRewardStatus", &LuaPlayer::GetQuestRewardStatus },                 // :GetQuestRewardStatus(questId) - Returns the true/false of the quest reward status
#ifndef CATA
    { ENV_NONE, "GetShieldBlockValue", &LuaPlayer::GetShieldBlockValue },                   // :GetShieldBlockValue() - Returns block value
#endif
#ifdef CLASSIC
    { ENV_NONE, "GetHonorStoredKills", &LuaPlayer::GetHonorStoredKills },                     // :GetHonorStoredKills(on/off)
    { ENV_NONE, "GetRankPoints", &LuaPlayer::GetRankPoints },                                 // :GetRankPoints()
    { ENV_NONE, "GetHonorLastWeekStandingPos", &LuaPlayer::GetHonorLastWeekStandingPos },     // :GetHonorLastWeekStandingPos()
#endif

    // Setters
    { ENV_NONE, "AdvanceSkillsToMax", &LuaPlayer::AdvanceSkillsToMax },     // :AdvanceSkillsToMax() - Advances all currently known skills to the currently known max level
    { ENV_NONE, "AdvanceSkill", &LuaPlayer::AdvanceSkill },                 // :AdvanceSkill(skill_id, step) - Advances skill by ID and the amount(step)
    { ENV_NONE, "AdvanceAllSkills", &LuaPlayer::AdvanceAllSkills },         // :AdvanceAllSkills(value) - Advances all current skills to your input(value)
    { ENV_NONE, "AddLifetimeKills", &LuaPlayer::AddLifetimeKills },         // :AddLifetimeKills(val) - Adds lifetime (honorable) kills to your current lifetime kills
    { ENV_NONE, "SetCoinage", &LuaPlayer::SetCoinage },                     // :SetCoinage(amount) - sets plr's coinage to this
#ifndef CLASSIC
    { ENV_NONE, "SetKnownTitle", &LuaPlayer::SetKnownTitle },               // :SetKnownTitle(id)
    { ENV_NONE, "UnsetKnownTitle", &LuaPlayer::UnsetKnownTitle },           // :UnsetKnownTitle(id)
#endif
    { ENV_NONE, "SetBindPoint", &LuaPlayer::SetBindPoint },                 // :SetBindPoint(x, y, z, map, areaid) - sets home for hearthstone
#ifndef CATA
#ifndef CLASSIC
    { ENV_NONE, "SetArenaPoints", &LuaPlayer::SetArenaPoints },             // :SetArenaPoints(amount)
    { ENV_NONE, "SetHonorPoints", &LuaPlayer::SetHonorPoints },             // :SetHonorPoints(amount)
#endif
#endif
#ifdef CLASSIC
    { ENV_NONE, "SetHonorStoredKills", &LuaPlayer::SetHonorStoredKills },     // :SetHonorStoredKills(kills, [on/off])
    { ENV_NONE, "SetRankPoints", &LuaPlayer::SetRankPoints },                 // :SetRankPoints(rankPoints)
    { ENV_NONE, "SetHonorLastWeekStandingPos", &LuaPlayer::SetHonorLastWeekStandingPos }, // :SetHonorLastWeekStandingPos(standingPos)
#endif
    { ENV_NONE, "SetLifetimeKills", &LuaPlayer::SetLifetimeKills },         // :SetLifetimeKills(val) - Sets the overall lifetime (honorable) kills of the player
    { ENV_NONE, "SetGameMaster", &LuaPlayer::SetGameMaster },               // :SetGameMaster([on]) - Sets GM mode on or off
    { ENV_NONE, "SetGMChat", &LuaPlayer::SetGMChat },                       // :SetGMChat([on]) - Sets GM chat on or off
    { ENV_NONE, "SetTaxiCheat", &LuaPlayer::SetTaxiCheat },                 // :SetTaxiCheat([on]) - Sets taxi cheat on or off
    { ENV_NONE, "SetGMVisible", &LuaPlayer::SetGMVisible },                 // :SetGMVisible([on]) - Sets gm visibility on or off
    { ENV_NONE, "SetPvPDeath", &LuaPlayer::SetPvPDeath },                   // :SetPvPDeath([on]) - Sets PvP death on or off
    { ENV_NONE, "SetAcceptWhispers", &LuaPlayer::SetAcceptWhispers },       // :SetAcceptWhispers([on]) - Sets whisper accepting death on or off
    { ENV_NONE, "SetRestBonus", &LuaPlayer::SetRestBonus },                 // :SetRestBonus(bonusrate) - Sets new restbonus rate
    { ENV_NONE, "SetRestType", &LuaPlayer::SetRestType },                   // :SetRestType() - Sets rest type
    { ENV_NONE, "SetQuestStatus", &LuaPlayer::SetQuestStatus },             // :SetQuestStatus(entry, status) - Sets the quest's status
    { ENV_NONE, "SetReputation", &LuaPlayer::SetReputation },               // :SetReputation(faction, value) - Sets the faction reputation for the player
    { ENV_NONE, "SetFreeTalentPoints", &LuaPlayer::SetFreeTalentPoints },   // :SetFreeTalentPoints(points) - Sets the amount of unused talent points
    { ENV_NONE, "SetGuildRank", &LuaPlayer::SetGuildRank },                 // :SetGuildRank(rank) - Sets player's guild rank
    // { "SetMovement", &LuaPlayer::SetMovement },                // :SetMovement(type) - Sets player's movement type
    { ENV_NONE, "SetSkill", &LuaPlayer::SetSkill },                         // :SetSkill(skill, step, currVal, maxVal) - Sets the skill's boundaries and value
    { ENV_NONE, "SetFactionForRace", &LuaPlayer::SetFactionForRace },       // :SetFactionForRace(race) - Sets the faction by raceID
    { ENV_NONE, "SetDrunkValue", &LuaPlayer::SetDrunkValue },               // :SetDrunkValue(newDrunkValue) - Sets drunkness value
    { ENV_NONE, "SetRestTime", &LuaPlayer::SetRestTime },                   // :SetRestTime(value) - Sets the rested time
    { ENV_NONE, "SetAtLoginFlag", &LuaPlayer::SetAtLoginFlag },             // :SetAtLoginFlag(flag) - Adds an at login flag
    { ENV_NONE, "SetPlayerLock", &LuaPlayer::SetPlayerLock },               // :SetPlayerLock(on/off)
    { ENV_NONE, "SetGender", &LuaPlayer::SetGender },                       // :SetGender(value) - 0 = male 1 = female
    { ENV_NONE, "SetSheath", &LuaPlayer::SetSheath },                       // :SetSheath(SheathState) - Sets player's sheathstate
#ifndef TRINITY
    { ENV_NONE, "SetFFA", &LuaPlayer::SetFFA },                             // :SetFFA([apply]) - Sets the units FFA tag on or off
#endif

    // Boolean
    { ENV_NONE, "IsInGroup", &LuaPlayer::IsInGroup },                                               // :IsInGroup()
    { ENV_NONE, "IsInGuild", &LuaPlayer::IsInGuild },                                               // :IsInGuild()
    { ENV_NONE, "IsGM", &LuaPlayer::IsGM },                                                         // :IsGM()
    { ENV_NONE, "IsAlliance", &LuaPlayer::IsAlliance },                                             // :IsAlliance()
    { ENV_NONE, "IsHorde", &LuaPlayer::IsHorde },                                                   // :IsHorde()
#ifndef CLASSIC
    { ENV_NONE, "HasTitle", &LuaPlayer::HasTitle },                                                 // :HasTitle(id)
#endif
    { ENV_NONE, "HasItem", &LuaPlayer::HasItem },                                                   // :HasItem(itemId[, count, check_bank]) - Returns true if the player has the item(itemId) and specified count, else it will return false
    { ENV_NONE, "Teleport", &LuaPlayer::Teleport },                                                 // :Teleport(Map, X, Y, Z, O) - Teleports player to specified co - ordinates. Returns true if success and false if not
    { ENV_NONE, "AddItem", &LuaPlayer::AddItem },                                                   // :AddItem(id, amount) - Adds amount of item to player. Returns true if success and false if not
#ifndef CLASSIC
    { ENV_NONE, "IsInArenaTeam", &LuaPlayer::IsInArenaTeam },                                       // :IsInArenaTeam(type) - type : 0 = 2v2, 1 = 3v3, 2 = 5v5
#endif
    { ENV_NONE, "CanCompleteQuest", &LuaPlayer::CanCompleteQuest },
    { ENV_NONE, "CanEquipItem", &LuaPlayer::CanEquipItem },                                         // :CanEquipItem(entry/item, slot) - Returns true if the player can equip given item/item entry
    { ENV_NONE, "IsFalling", &LuaPlayer::IsFalling },                                               // :IsFalling() - Returns true if the unit is falling
    { ENV_NONE, "ToggleAFK", &LuaPlayer::ToggleAFK },                                               // :ToggleAFK() - Toggles AFK state for player
    { ENV_NONE, "ToggleDND", &LuaPlayer::ToggleDND },                                               // :ToggleDND() - Toggles DND state for player
    { ENV_NONE, "IsAFK", &LuaPlayer::IsAFK },                                                       // :IsAFK() - Returns true if the player is afk
    { ENV_NONE, "IsDND", &LuaPlayer::IsDND },                                                       // :IsDND() - Returns true if the player is in dnd mode
    { ENV_NONE, "IsAcceptingWhispers", &LuaPlayer::IsAcceptingWhispers },                           // :IsAcceptWhispers() - Returns true if the player accepts whispers
    { ENV_NONE, "IsGMChat", &LuaPlayer::IsGMChat },                                                 // :IsGMChat() - Returns true if the player has GM chat on
    { ENV_NONE, "IsTaxiCheater", &LuaPlayer::IsTaxiCheater },                                       // :IsTaxiCheater() - Returns true if the player has taxi cheat on
    { ENV_NONE, "IsGMVisible", &LuaPlayer::IsGMVisible },                                           // :IsGMVisible() - Returns true if the player is GM visible
    { ENV_NONE, "HasQuest", &LuaPlayer::HasQuest },                                                 // :HasQuest(entry) - Returns true if player has the quest
    { ENV_NONE, "InBattlegroundQueue", &LuaPlayer::InBattlegroundQueue },                           // :InBattlegroundQueue() - Returns true if the player is in a battleground queue
    // { "IsImmuneToEnvironmentalDamage", &LuaPlayer::IsImmuneToEnvironmentalDamage },    // :IsImmuneToEnvironmentalDamage() - Returns true if the player is immune to enviromental damage
    { ENV_NONE, "CanSpeak", &LuaPlayer::CanSpeak },                                                 // :CanSpeak() - Returns true if the player can speak
    { ENV_NONE, "HasAtLoginFlag", &LuaPlayer::HasAtLoginFlag },                                     // :HasAtLoginFlag(flag) - returns true if the player has the login flag
    // { "InRandomLfgDungeon", &LuaPlayer::InRandomLfgDungeon },                          // :InRandomLfgDungeon() - Returns true if the player is in a random LFG dungeon
    // { "HasPendingBind", &LuaPlayer::HasPendingBind },                                  // :HasPendingBind() - Returns true if the player has a pending instance bind
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "HasAchieved", &LuaPlayer::HasAchieved },                                           // :HasAchieved(achievementID) - Returns true if the player has achieved the achievement
#endif
    { ENV_NONE, "CanUninviteFromGroup", &LuaPlayer::CanUninviteFromGroup },                         // :CanUninviteFromGroup() - Returns true if the player can uninvite from group
    { ENV_NONE, "IsRested", &LuaPlayer::IsRested },                                                 // :IsRested() - Returns true if the player is rested
    // { "CanFlyInZone", &LuaPlayer::CanFlyInZone },                                      // :CanFlyInZone(mapid, zone) - Returns true if the player can fly in the area
    // { "IsNeverVisible", &LuaPlayer::IsNeverVisible },                                  // :IsNeverVisible() - Returns true if the player is never visible
    { ENV_NONE, "IsVisibleForPlayer", &LuaPlayer::IsVisibleForPlayer },                             // :IsVisibleForPlayer(player) - Returns true if the player is visible for the target player
    // { "IsUsingLfg", &LuaPlayer::IsUsingLfg },                                          // :IsUsingLfg() - Returns true if the player is using LFG
    { ENV_NONE, "HasQuestForItem", &LuaPlayer::HasQuestForItem },                                   // :HasQuestForItem(entry) - Returns true if the player has the quest for the item
    { ENV_NONE, "HasQuestForGO", &LuaPlayer::HasQuestForGO },                                       // :HasQuestForGO(entry) - Returns true if the player has the quest for the gameobject
    { ENV_NONE, "CanShareQuest", &LuaPlayer::CanShareQuest },                                       // :CanShareQuest(entry) - Returns true if the quest entry is shareable by the player
    // { "HasReceivedQuestReward", &LuaPlayer::HasReceivedQuestReward },                  // :HasReceivedQuestReward(entry) - Returns true if the player has recieved the quest's reward
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "HasTalent", &LuaPlayer::HasTalent },                                               // :HasTalent(talentId, spec) - Returns true if the player has the talent in given spec
#endif
    { ENV_NONE, "IsInSameGroupWith", &LuaPlayer::IsInSameGroupWith },                               // :IsInSameGroupWith(player) - Returns true if the players are in the same group
    { ENV_NONE, "IsInSameRaidWith", &LuaPlayer::IsInSameRaidWith },                                 // :IsInSameRaidWith(player) - Returns true if the players are in the same raid
    { ENV_NONE, "IsGroupVisibleFor", &LuaPlayer::IsGroupVisibleFor },                               // :IsGroupVisibleFor(player) - Player is group visible for the target
    { ENV_NONE, "HasSkill", &LuaPlayer::HasSkill },                                                 // :HasSkill(skill) - Returns true if the player has the skill
    { ENV_NONE, "IsHonorOrXPTarget", &LuaPlayer::IsHonorOrXPTarget },                               // :IsHonorOrXPTarget(victim) - Returns true if the victim gives honor or XP
    { ENV_NONE, "CanParry", &LuaPlayer::CanParry },                                                 // :CanParry() - Returns true if the player can parry
    { ENV_NONE, "CanBlock", &LuaPlayer::CanBlock },                                                 // :CanBlock() - Returns true if the player can block
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "CanTitanGrip", &LuaPlayer::CanTitanGrip },                                         // :CanTitanGrip() - Returns true if the player has titan grip
#endif
    { ENV_NONE, "InBattleground", &LuaPlayer::InBattleground },                                     // :InBattleground() - Returns true if the player is in a battleground
#ifndef CLASSIC
    { ENV_NONE, "InArena", &LuaPlayer::InArena },                                                   // :InArena() - Returns true if the player is in an arena
#endif
    // { "IsOutdoorPvPActive", &LuaPlayer::IsOutdoorPvPActive },                          // :IsOutdoorPvPActive() - Returns true if the player is outdoor pvp active
    // { "IsARecruiter", &LuaPlayer::IsARecruiter },                                      // :IsARecruiter() - Returns true if the player is a recruiter
    { ENV_NONE, "CanUseItem", &LuaPlayer::CanUseItem },                                             // :CanUseItem(item/entry) - Returns true if the player can use the item or item entry
    { ENV_NONE, "HasSpell", &LuaPlayer::HasSpell },                                                 // :HasSpell(id)
    { ENV_NONE, "HasSpellCooldown", &LuaPlayer::HasSpellCooldown },                                 // :HasSpellCooldown(spellId) - Returns true if the spell is on cooldown
    { ENV_NONE, "IsInWater", &LuaPlayer::IsInWater },                                               // :IsInWater() - Returns true if the player is in water
#ifndef CLASSIC
    { ENV_NONE, "CanFly", &LuaPlayer::CanFly },                                                     // :CanFly() - Returns true if the player can fly
#endif
    { ENV_NONE, "IsMoving", &LuaPlayer::IsMoving },                                                 // :IsMoving()
#ifndef CLASSIC
    { ENV_NONE, "IsFlying", &LuaPlayer::IsFlying },                                                 // :IsFlying()
#endif

    // Gossip
    { ENV_NONE, "GossipMenuAddItem", &LuaPlayer::GossipMenuAddItem },                               // :GossipMenuAddItem(icon, msg, sender, intid[, code, popup, money])
    { ENV_NONE, "GossipSendMenu", &LuaPlayer::GossipSendMenu },                                     // :GossipSendMenu(npc_text, unit[, menu_id]) - If unit is a player, you need to use a menu_id. menu_id is used to hook the gossip select function to the menu
    { ENV_NONE, "GossipComplete", &LuaPlayer::GossipComplete },                                     // :GossipComplete()
    { ENV_NONE, "GossipClearMenu", &LuaPlayer::GossipClearMenu },                                   // :GossipClearMenu() - Clears the gossip menu of options. Pretty much only useful with player gossip. Need to use before creating a new menu for the player

    // Other
    { ENV_NONE, "SendClearCooldowns", &LuaPlayer::SendClearCooldowns },                            // :SendClearCooldowns(spellId, (unit)target) - Clears the cooldown of the target with a specified spellId
    { ENV_NONE, "SendBroadcastMessage", &LuaPlayer::SendBroadcastMessage },                         // :SendBroadcastMessage(message)
    { ENV_NONE, "SendAreaTriggerMessage", &LuaPlayer::SendAreaTriggerMessage },                     // :SendAreaTriggerMessage(message) - Sends a yellow message in the middle of your screen
    { ENV_NONE, "SendNotification", &LuaPlayer::SendNotification },                                 // :SendNotification(message) - Sends a red message in the middle of your screen
    { ENV_NONE, "SendPacket", &LuaPlayer::SendPacket },                                             // :SendPacket(packet, selfOnly) - Sends a packet to player or everyone around also if selfOnly is false
    { ENV_NONE, "SendAddonMessage", &LuaPlayer::SendAddonMessage },                                 // :SendAddonMessage(prefix, message, channel, receiver) - Sends an addon message to the player. 
    { ENV_NONE, "ModifyMoney", &LuaPlayer::ModifyMoney },                                           // :ModifyMoney(amount[, sendError]) - Modifies (does not set) money (copper count) of the player. Amount can be negative to remove copper
    { ENV_NONE, "LearnSpell", &LuaPlayer::LearnSpell },                                             // :LearnSpell(id) - learns the given spell
    { ENV_NONE, "LearnTalent", &LuaPlayer::LearnTalent },
    { ENV_NONE, "RemoveItem", &LuaPlayer::RemoveItem },                                             // :RemoveItem(item/entry, amount) - Removes amount of item from player
    { ENV_NONE, "RemoveLifetimeKills", &LuaPlayer::RemoveLifetimeKills },                           // :RemoveLifetimeKills(val) - Removes a specified amount(val) of the player's lifetime (honorable) kills
    { ENV_NONE, "ResurrectPlayer", &LuaPlayer::ResurrectPlayer },                                   // :ResurrectPlayer([percent[, sickness(bool)]]) - Resurrects the player at percentage, player gets resurrection sickness if sickness set to true
    { ENV_NONE, "PlaySoundToPlayer", &LuaPlayer::PlaySoundToPlayer },                               // :PlaySoundToPlayer(soundId) - Plays the specified sound to the player
    { ENV_NONE, "EquipItem", &LuaPlayer::EquipItem },                                               // :EquipItem(entry/item, slot) - Equips given item or item entry for player to given slot. Returns the equipped item or nil
    { ENV_NONE, "ResetSpellCooldown", &LuaPlayer::ResetSpellCooldown },                             // :ResetSpellCooldown(spellId, update(bool~optional)) - Resets cooldown of the specified spellId. If update is true, it will send WorldPacket SMSG_CLEAR_COOLDOWN to the player, else it will just clear the spellId from m_spellCooldowns. This is true by default
    { ENV_NONE, "ResetTypeCooldowns", &LuaPlayer::ResetTypeCooldowns },                             // :ResetTypeCooldowns(category, update(bool~optional)) - Resets all cooldowns for the spell category(type). If update is true, it will send WorldPacket SMSG_CLEAR_COOLDOWN to the player, else it will just clear the spellId from m_spellCooldowns. This is true by default
    { ENV_NONE, "ResetAllCooldowns", &LuaPlayer::ResetAllCooldowns },                               // :ResetAllCooldowns() - Resets all spell cooldowns
    { ENV_NONE, "GiveXP", &LuaPlayer::GiveXP },                                                     // :GiveXP(xp[, victim, pureXP, triggerHook]) - Gives XP to the player. If pure is false, bonuses are count in. If triggerHook is false, GiveXp hook is not triggered.
    // { "RemovePet", &LuaPlayer::RemovePet },                                            // :RemovePet([mode, returnreagent]) - Removes the player's pet. Mode determines if the pet is saved and how
    // { "SummonPet", &LuaPlayer::SummonPet },                                            // :SummonPet(entry, x, y, z, o, petType, despwtime) - Summons a pet for the player
    { ENV_NONE, "Say", &LuaPlayer::Say },                                                           // :Say(text, lang) - The player says the text
    { ENV_NONE, "Yell", &LuaPlayer::Yell },                                                         // :Yell(text, lang) - The player yells the text
    { ENV_NONE, "TextEmote", &LuaPlayer::TextEmote },                                               // :TextEmote(text) - The player does a textemote with the text
    { ENV_NONE, "Whisper", &LuaPlayer::Whisper },                                                   // :Whisper(text, lang, receiver) - The player whispers the text to the receiver
    { ENV_NONE, "CompleteQuest", &LuaPlayer::CompleteQuest },                                       // :CompleteQuest(entry) - Completes a quest by entry
    { ENV_NONE, "IncompleteQuest", &LuaPlayer::IncompleteQuest },                                   // :IncompleteQuest(entry) - Uncompletes the quest by entry for the player
    { ENV_NONE, "FailQuest", &LuaPlayer::FailQuest },                                               // :FailQuest(entry) - Player fails the quest entry
    { ENV_NONE, "AddQuest", &LuaPlayer::AddQuest },
    { ENV_NONE, "RemoveQuest", &LuaPlayer::RemoveQuest },
    // { "RemoveActiveQuest", &LuaPlayer::RemoveActiveQuest },                            // :RemoveActiveQuest(entry) - Removes an active quest
    // { "RemoveRewardedQuest", &LuaPlayer::RemoveRewardedQuest },                        // :RemoveRewardedQuest(entry) - Removes a rewarded quest
    { ENV_NONE, "AreaExploredOrEventHappens", &LuaPlayer::AreaExploredOrEventHappens },             // :AreaExploredOrEventHappens(questId) - Satisfies an area or event requrement for the questId
    { ENV_NONE, "GroupEventHappens", &LuaPlayer::GroupEventHappens },                               // :GroupEventHappens(questId, worldObject) - Satisfies a group event for the questId with the world object
    { ENV_NONE, "KilledMonsterCredit", &LuaPlayer::KilledMonsterCredit },                           // :KilledMonsterCredit(entry) - Satisfies a monsterkill for the player
    // { "KilledPlayerCredit", &LuaPlayer::KilledPlayerCredit },                          // :KilledPlayerCredit() - Satisfies a player kill for the player
    // { "KillGOCredit", &LuaPlayer::KillGOCredit },                                      // :KillGOCredit(GOEntry[, GUID]) - Credits the player for destroying a GO, guid is optional
    { ENV_NONE, "TalkedToCreature", &LuaPlayer::TalkedToCreature },                                 // :TalkedToCreature(npcEntry, creature) - Satisfies creature talk objective for the player
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "ResetPetTalents", &LuaPlayer::ResetPetTalents },                                   // :ResetPetTalents() - Resets player's pet's talents
#endif
    { ENV_NONE, "AddComboPoints", &LuaPlayer::AddComboPoints },                                     // :AddComboPoints(target, count[, spell]) - Adds combo points to the target for the player
    // { "GainSpellComboPoints", &LuaPlayer::GainSpellComboPoints },                      // :GainSpellComboPoints(amount) - Player gains spell combo points
    { ENV_NONE, "ClearComboPoints", &LuaPlayer::ClearComboPoints },                                 // :ClearComboPoints() - Clears player's combo points
    { ENV_NONE, "RemoveSpell", &LuaPlayer::RemoveSpell },                                           // :RemoveSpell(entry[, disabled, learn_low_rank]) - Removes (unlearn) the given spell
    { ENV_NONE, "ResetTalents", &LuaPlayer::ResetTalents },                                         // :ResetTalents([no_cost]) - Resets player's talents
    { ENV_NONE, "ResetTalentsCost", &LuaPlayer::ResetTalentsCost },                                 // :ResetTalentsCost() - Returns the reset talents cost
    // { "AddTalent", &LuaPlayer::AddTalent },                                            // :AddTalent(spellid, spec, learning) - Adds a talent spell for the player to given spec
    { ENV_NONE, "RemoveFromGroup", &LuaPlayer::RemoveFromGroup },                                   // :RemoveFromGroup() - Removes the player from his group
    { ENV_NONE, "KillPlayer", &LuaPlayer::KillPlayer },                                             // :KillPlayer() - Kills the player
    { ENV_NONE, "DurabilityLossAll", &LuaPlayer::DurabilityLossAll },                               // :DurabilityLossAll(percent[, inventory]) - The player's items lose durability. Inventory true by default
    { ENV_NONE, "DurabilityLoss", &LuaPlayer::DurabilityLoss },                                     // :DurabilityLoss(item, percent) - The given item loses durability
    { ENV_NONE, "DurabilityPointsLoss", &LuaPlayer::DurabilityPointsLoss },                         // :DurabilityPointsLoss(item, points) - The given item loses durability
    { ENV_NONE, "DurabilityPointsLossAll", &LuaPlayer::DurabilityPointsLossAll },                   // :DurabilityPointsLossAll(points, inventory) - Player's items lose durability
    { ENV_NONE, "DurabilityPointLossForEquipSlot", &LuaPlayer::DurabilityPointLossForEquipSlot },   // :DurabilityPointLossForEquipSlot(slot) - Causes durability loss for the item in the given slot
    { ENV_NONE, "DurabilityRepairAll", &LuaPlayer::DurabilityRepairAll },                           // :DurabilityRepairAll([has_cost, discount, guildBank]) - Repairs all durability
    { ENV_NONE, "DurabilityRepair", &LuaPlayer::DurabilityRepair },                                 // :DurabilityRepair(position[, has_cost, discount, guildBank]) - Repairs item durability of item in given position
#ifndef CATA
#ifndef CLASSIC
    { ENV_NONE, "ModifyHonorPoints", &LuaPlayer::ModifyHonorPoints },                               // :ModifyHonorPoints(amount) - Modifies the player's honor points
    { ENV_NONE, "ModifyArenaPoints", &LuaPlayer::ModifyArenaPoints },                               // :ModifyArenaPoints(amount) - Modifies the player's arena points
#endif
#endif
    { ENV_NONE, "LeaveBattleground", &LuaPlayer::LeaveBattleground },                               // :LeaveBattleground([teleToEntryPoint]) - The player leaves the battleground
    // { "BindToInstance", &LuaPlayer::BindToInstance },                                  // :BindToInstance() - Binds the player to the current instance
    { ENV_NONE, "UnbindInstance", &LuaPlayer::UnbindInstance },                                     // :UnbindInstance(map, difficulty) - Unbinds the player from an instance
    { ENV_NONE, "UnbindAllInstances", &LuaPlayer::UnbindAllInstances },                             // :UnbindAllInstances() - Unbinds the player from all instances
    { ENV_NONE, "RemoveFromBattlegroundRaid", &LuaPlayer::RemoveFromBattlegroundRaid },             // :RemoveFromBattlegroundRaid() - Removes the player from a battleground or battlefield raid
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "ResetAchievements", &LuaPlayer::ResetAchievements },                               // :ResetAchievements() - Resets player�s achievements
#endif
    { ENV_NONE, "KickPlayer", &LuaPlayer::KickPlayer },                                             // :KickPlayer() - Kicks player from server
    { ENV_NONE, "LogoutPlayer", &LuaPlayer::LogoutPlayer },                                         // :LogoutPlayer([save]) - Logs the player out and saves if true
    { ENV_NONE, "SendTrainerList", &LuaPlayer::SendTrainerList },                                   // :SendTrainerList(WorldObject) - Sends trainer list from object to player
    { ENV_NONE, "SendListInventory", &LuaPlayer::SendListInventory },                               // :SendListInventory(WorldObject) - Sends vendor list from object to player
    { ENV_NONE, "SendShowBank", &LuaPlayer::SendShowBank },                                         // :SendShowBank(WorldObject) - Sends bank window from object to player
    { ENV_NONE, "SendTabardVendorActivate", &LuaPlayer::SendTabardVendorActivate },                 // :SendTabardVendorActivate(WorldObject) - Sends tabard vendor window from object to player
    { ENV_NONE, "SendSpiritResurrect", &LuaPlayer::SendSpiritResurrect },                           // :SendSpiritResurrect() - Sends resurrect window to player
    { ENV_NONE, "SendTaxiMenu", &LuaPlayer::SendTaxiMenu },                                         // :SendTaxiMenu(creature) - Sends flight window to player from creature
    { ENV_NONE, "RewardQuest", &LuaPlayer::RewardQuest },
    { ENV_NONE, "SendAuctionMenu", &LuaPlayer::SendAuctionMenu },                                   // :SendAuctionMenu(unit) - Sends auction window to player. Auction house is sent by object.
    { ENV_NONE, "SendShowMailBox", &LuaPlayer::SendShowMailBox },                                   // :SendShowMailBox([mailboxguid]) - Sends the mail window to player from the mailbox gameobject. The guid is required on patches below wotlk.
    { ENV_NONE, "StartTaxi", &LuaPlayer::StartTaxi },                                               // :StartTaxi(pathId) - player starts the given flight path
    { ENV_NONE, "GossipSendPOI", &LuaPlayer::GossipSendPOI },                                       // :GossipSendPOI(X, Y, Icon, Flags, Data, Name) - Sends a point of interest to the player
    { ENV_NONE, "GossipAddQuests", &LuaPlayer::GossipAddQuests },                                   // :GossipAddQuests(unit) - Adds unit's quests to player's gossip menu
    { ENV_NONE, "SendQuestTemplate", &LuaPlayer::SendQuestTemplate },                               // :SendQuestTemplate(questId, activeAccept) -- Sends quest template to player
    { ENV_NONE, "SpawnBones", &LuaPlayer::SpawnBones },                                             // :SpawnBones() - Removes the player's corpse and spawns bones
    { ENV_NONE, "RemovedInsignia", &LuaPlayer::RemovedInsignia },                                   // :RemovedInsignia(looter) - Looter removes the player's corpse, looting the player and replacing with lootable bones
    { ENV_NONE, "SendGuildInvite", &LuaPlayer::SendGuildInvite },                                   // :SendGuildInvite(player) - Sends a guild invite to the specific player
    { ENV_NONE, "CreateCorpse", &LuaPlayer::CreateCorpse },                                         // :CreateCorpse() - Creates the player's corpse
    { ENV_NONE, "Mute", &LuaPlayer::Mute },                                                         // :Mute(time[, reason]) - Mutes the player for given time in seconds.
    { ENV_NONE, "SummonPlayer", &LuaPlayer::SummonPlayer },                                         // :SummonPlayer(player, map, x, y, z, zoneId[, delay]) - Sends a popup to the player asking if he wants to be summoned if yes, teleported to coords. ZoneID defines the location name shown in the popup Delay is the time until the popup closes automatically.
    { ENV_NONE, "SaveToDB", &LuaPlayer::SaveToDB },                                                 // :SaveToDB() - Saves to database
    { ENV_NONE, "GroupInvite", &LuaPlayer::GroupInvite },
    { ENV_NONE, "GroupCreate", &LuaPlayer::GroupCreate },
#ifdef CLASSIC
    { ENV_NONE, "UpdateHonor", &LuaPlayer::UpdateHonor },                                             // :UpdateHonor() - Updates Player Honor
    { ENV_NONE, "ResetHonor", &LuaPlayer::ResetHonor },                                               // :ResetHonor() - Resets Player Honor
    { ENV_NONE, "ClearHonorInfo", &LuaPlayer::ClearHonorInfo },                                       // :ClearHonorInfo() - Clear Player Honor Info
#endif

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Creature> CreatureMethods[] =
{
    // Getters
    { ENV_NONE, "GetAITarget", &LuaCreature::GetAITarget },
    { ENV_NONE, "GetAITargets", &LuaCreature::GetAITargets },
    { ENV_NONE, "GetAITargetsCount", &LuaCreature::GetAITargetsCount },
    { ENV_NONE, "GetHomePosition", &LuaCreature::GetHomePosition },
    { ENV_NONE, "GetCorpseDelay", &LuaCreature::GetCorpseDelay },
    { ENV_NONE, "GetCreatureSpellCooldownDelay", &LuaCreature::GetCreatureSpellCooldownDelay },
    { ENV_NONE, "GetScriptId", &LuaCreature::GetScriptId },
    { ENV_NONE, "GetAIName", &LuaCreature::GetAIName },
    { ENV_NONE, "GetScriptName", &LuaCreature::GetScriptName },
    { ENV_NONE, "GetAttackDistance", &LuaCreature::GetAttackDistance },
    { ENV_NONE, "GetAggroRange", &LuaCreature::GetAggroRange },
    { ENV_NONE, "GetDefaultMovementType", &LuaCreature::GetDefaultMovementType },
    { ENV_NONE, "GetRespawnDelay", &LuaCreature::GetRespawnDelay },
    { ENV_NONE, "GetWanderRadius", &LuaCreature::GetWanderRadius },
    { ENV_NONE, "GetCurrentWaypointId", &LuaCreature::GetCurrentWaypointId },
#ifdef TRINITY
    { ENV_NONE, "GetWaypointPath", &LuaCreature::GetWaypointPath },
    { ENV_NONE, "GetLootMode", &LuaCreature::GetLootMode },
#endif
    { ENV_NONE, "GetLootRecipient", &LuaCreature::GetLootRecipient },
    { ENV_NONE, "GetLootRecipientGroup", &LuaCreature::GetLootRecipientGroup },
    { ENV_NONE, "GetNPCFlags", &LuaCreature::GetNPCFlags },
#ifndef CATA
    { ENV_NONE, "GetShieldBlockValue", &LuaCreature::GetShieldBlockValue },
#endif

    // Setters
    { ENV_NONE, "SetHover", &LuaCreature::SetHover },
    { ENV_NONE, "SetDisableGravity", &LuaCreature::SetDisableGravity },
    { ENV_NONE, "SetAggroEnabled", &LuaCreature::SetAggroEnabled },
    { ENV_NONE, "SetNoCallAssistance", &LuaCreature::SetNoCallAssistance },
    { ENV_NONE, "SetNoSearchAssistance", &LuaCreature::SetNoSearchAssistance },
    { ENV_NONE, "SetDefaultMovementType", &LuaCreature::SetDefaultMovementType },
    { ENV_NONE, "SetRespawnDelay", &LuaCreature::SetRespawnDelay },
    { ENV_NONE, "SetWanderRadius", &LuaCreature::SetWanderRadius },
    { ENV_NONE, "SetInCombatWithZone", &LuaCreature::SetInCombatWithZone },
    { ENV_NONE, "SetDisableReputationGain", &LuaCreature::SetDisableReputationGain },
#ifdef TRINITY
    { ENV_NONE, "SetLootMode", &LuaCreature::SetLootMode },
#endif
    { ENV_NONE, "SetNPCFlags", &LuaCreature::SetNPCFlags },
    { ENV_NONE, "SetDeathState", &LuaCreature::SetDeathState },
    { ENV_NONE, "SetWalk", &LuaCreature::SetWalk },
    { ENV_NONE, "SetHomePosition", &LuaCreature::SetHomePosition },
    { ENV_NONE, "SetEquipmentSlots", &LuaCreature::SetEquipmentSlots },

    // Booleans
    { ENV_NONE, "IsWorldBoss", &LuaCreature::IsWorldBoss },
    { ENV_NONE, "IsRacialLeader", &LuaCreature::IsRacialLeader },
    { ENV_NONE, "IsCivilian", &LuaCreature::IsCivilian },
#ifdef TRINITY
    { ENV_NONE, "IsTrigger", &LuaCreature::IsTrigger },
#endif
    { ENV_NONE, "IsGuard", &LuaCreature::IsGuard },
    { ENV_NONE, "IsElite", &LuaCreature::IsElite },
    { ENV_NONE, "IsInEvadeMode", &LuaCreature::IsInEvadeMode },
    { ENV_NONE, "HasCategoryCooldown", &LuaCreature::HasCategoryCooldown },
    { ENV_NONE, "CanWalk", &LuaCreature::CanWalk },
    { ENV_NONE, "CanSwim", &LuaCreature::CanSwim },
    { ENV_NONE, "CanAggro", &LuaCreature::CanAggro },
#ifdef TRINITY
    { ENV_NONE, "CanStartAttack", &LuaCreature::CanStartAttack },
#endif
    { ENV_NONE, "HasSearchedAssistance", &LuaCreature::HasSearchedAssistance },
    { ENV_NONE, "IsTappedBy", &LuaCreature::IsTappedBy },
    { ENV_NONE, "HasLootRecipient", &LuaCreature::HasLootRecipient },
    { ENV_NONE, "CanAssistTo", &LuaCreature::CanAssistTo },
    { ENV_NONE, "IsTargetableForAttack", &LuaCreature::IsTargetableForAttack },
    { ENV_NONE, "CanCompleteQuest", &LuaCreature::CanCompleteQuest },
    { ENV_NONE, "CanRegenerateHealth", &LuaCreature::CanRegenerateHealth },
    { ENV_NONE, "IsReputationGainDisabled", &LuaCreature::IsReputationGainDisabled },
#ifdef TRINITY
    { ENV_NONE, "IsDamageEnoughForLootingAndReward", &LuaCreature::IsDamageEnoughForLootingAndReward },
    { ENV_NONE, "HasLootMode", &LuaCreature::HasLootMode },
#endif
    { ENV_NONE, "HasSpell", &LuaCreature::HasSpell },
    { ENV_NONE, "HasQuest", &LuaCreature::HasQuest },
    { ENV_NONE, "HasSpellCooldown", &LuaCreature::HasSpellCooldown },
    { ENV_NONE, "CanFly", &LuaCreature::CanFly },

    // Other
    { ENV_NONE, "FleeToGetAssistance", &LuaCreature::FleeToGetAssistance },
    { ENV_NONE, "CallForHelp", &LuaCreature::CallForHelp },
    { ENV_NONE, "CallAssistance", &LuaCreature::CallAssistance },
    { ENV_NONE, "RemoveCorpse", &LuaCreature::RemoveCorpse },
    { ENV_NONE, "DespawnOrUnsummon", &LuaCreature::DespawnOrUnsummon },
    { ENV_NONE, "Respawn", &LuaCreature::Respawn },
    { ENV_NONE, "AttackStart", &LuaCreature::AttackStart },
#ifdef TRINITY
    { ENV_NONE, "AddLootMode", &LuaCreature::AddLootMode },
    { ENV_NONE, "ResetLootMode", &LuaCreature::ResetLootMode },
    { ENV_NONE, "RemoveLootMode", &LuaCreature::RemoveLootMode },
#endif
    { ENV_NONE, "SaveToDB", &LuaCreature::SaveToDB },
    { ENV_NONE, "SelectVictim", &LuaCreature::SelectVictim },
    { ENV_NONE, "MoveWaypoint", &LuaCreature::MoveWaypoint },
    { ENV_NONE, "UpdateEntry", &LuaCreature::UpdateEntry },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<GameObject> GameObjectMethods[] =
{
    // Getters
    { ENV_NONE, "GetDisplayId", &LuaGameObject::GetDisplayId },
    { ENV_NONE, "GetGoState", &LuaGameObject::GetGoState },
    { ENV_NONE, "GetLootState", &LuaGameObject::GetLootState },
    { ENV_NONE, "GetLootRecipient", &LuaGameObject::GetLootRecipient },
    { ENV_NONE, "GetLootRecipientGroup", &LuaGameObject::GetLootRecipientGroup },

    // Setters
    { ENV_NONE, "SetGoState", &LuaGameObject::SetGoState },
    { ENV_NONE, "SetLootState", &LuaGameObject::SetLootState },

    // Boolean
    { ENV_NONE, "IsTransport", &LuaGameObject::IsTransport },
    // { "IsDestructible", &LuaGameObject::IsDestructible },    // :IsDestructible()
    { ENV_NONE, "IsActive", &LuaGameObject::IsActive },
    { ENV_NONE, "HasQuest", &LuaGameObject::HasQuest },
    { ENV_NONE, "IsSpawned", &LuaGameObject::IsSpawned },

    // Other
    { ENV_NONE, "RemoveFromWorld", &LuaGameObject::RemoveFromWorld },
    { ENV_NONE, "UseDoorOrButton", &LuaGameObject::UseDoorOrButton },
    { ENV_NONE, "Despawn", &LuaGameObject::Despawn },
    { ENV_NONE, "Respawn", &LuaGameObject::Respawn },
    { ENV_NONE, "SaveToDB", &LuaGameObject::SaveToDB },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Item> ItemMethods[] =
{
    // Getters
    { ENV_NONE, "GetOwnerGUID", &LuaItem::GetOwnerGUID },                   // :GetOwnerGUID() - Returns the owner's guid
    { ENV_NONE, "GetOwner", &LuaItem::GetOwner },                           // :GetOwner() - Returns the owner object (player)
    { ENV_NONE, "GetCount", &LuaItem::GetCount },                           // :GetCount() - Returns item stack count
    { ENV_NONE, "GetMaxStackCount", &LuaItem::GetMaxStackCount },           // :GetMaxStackCount() - Returns item max stack count
    { ENV_NONE, "GetSlot", &LuaItem::GetSlot },                             // :GetSlot() - returns the slot the item is in
    { ENV_NONE, "GetBagSlot", &LuaItem::GetBagSlot },                       // :GetBagSlot() - returns the bagslot of the bag the item is in
    { ENV_NONE, "GetEnchantmentId", &LuaItem::GetEnchantmentId },           // :GetEnchantmentId(enchant_slot) - Returns the enchantment in given slot. (permanent = 0)
    { ENV_NONE, "GetSpellId", &LuaItem::GetSpellId },                       // :GetSpellId(index) - Returns spellID at given index (0 - 4)
    { ENV_NONE, "GetSpellTrigger", &LuaItem::GetSpellTrigger },             // :GetSpellTrigger(index) - Returns spell trigger at given index (0 - 4)
    { ENV_NONE, "GetItemLink", &LuaItem::GetItemLink },                     // :GetItemLink([localeID]) - Returns the shift clickable link of the item. Name translated if locale given and exists
    { ENV_NONE, "GetClass", &LuaItem::GetClass },                           // :GetClass()
    { ENV_NONE, "GetSubClass", &LuaItem::GetSubClass },                     // :GetSubClass()
    { ENV_NONE, "GetName", &LuaItem::GetName },                             // :GetName()
    { ENV_NONE, "GetDisplayId", &LuaItem::GetDisplayId },                   // :GetDisplayId()
    { ENV_NONE, "GetQuality", &LuaItem::GetQuality },                       // :GetQuality()
    { ENV_NONE, "GetBuyCount", &LuaItem::GetBuyCount },                     // :GetBuyCount()
    { ENV_NONE, "GetBuyPrice", &LuaItem::GetBuyPrice },                     // :GetBuyPrice()
    { ENV_NONE, "GetSellPrice", &LuaItem::GetSellPrice },                   // :GetSellPrice()
    { ENV_NONE, "GetInventoryType", &LuaItem::GetInventoryType },           // :GetInventoryType()
    { ENV_NONE, "GetAllowableClass", &LuaItem::GetAllowableClass },         // :GetAllowableClass()
    { ENV_NONE, "GetAllowableRace", &LuaItem::GetAllowableRace },           // :GetAllowableRace()
    { ENV_NONE, "GetItemLevel", &LuaItem::GetItemLevel },                   // :GetItemLevel()
    { ENV_NONE, "GetRequiredLevel", &LuaItem::GetRequiredLevel },           // :GetRequiredLevel()
#ifdef WOTLK
    { ENV_NONE, "GetStatsCount", &LuaItem::GetStatsCount },                 // :GetStatsCount()
#endif
    { ENV_NONE, "GetRandomProperty", &LuaItem::GetRandomProperty },         // :GetRandomProperty()
#ifndef CLASSIC
    { ENV_NONE, "GetRandomSuffix", &LuaItem::GetRandomSuffix },             // :GetRandomSuffix()
#endif
    { ENV_NONE, "GetItemSet", &LuaItem::GetItemSet },                       // :GetItemSet()
    { ENV_NONE, "GetBagSize", &LuaItem::GetBagSize },                       // :GetBagSize()

    // Setters
    { ENV_NONE, "SetOwner", &LuaItem::SetOwner },                           // :SetOwner(player) - Sets the owner of the item
    { ENV_NONE, "SetBinding", &LuaItem::SetBinding },                       // :SetBinding(bound) - Sets the item binding to true or false
    { ENV_NONE, "SetCount", &LuaItem::SetCount },                           // :SetCount(count) - Sets the item count

    // Boolean
    { ENV_NONE, "IsSoulBound", &LuaItem::IsSoulBound },                     // :IsSoulBound() - Returns true if the item is soulbound
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_NONE, "IsBoundAccountWide", &LuaItem::IsBoundAccountWide },       // :IsBoundAccountWide() - Returns true if the item is account bound
#endif
    { ENV_NONE, "IsBoundByEnchant", &LuaItem::IsBoundByEnchant },           // :IsBoundByEnchant() - Returns true if the item is bound with an enchant
    { ENV_NONE, "IsNotBoundToPlayer", &LuaItem::IsNotBoundToPlayer },       // :IsNotBoundToPlayer(player) - Returns true if the item is not bound with player
    { ENV_NONE, "IsLocked", &LuaItem::IsLocked },                           // :IsLocked() - Returns true if the item is locked
    { ENV_NONE, "IsBag", &LuaItem::IsBag },                                 // :IsBag() - Returns true if the item is a bag
#ifndef CLASSIC
    { ENV_NONE, "IsCurrencyToken", &LuaItem::IsCurrencyToken },             // :IsCurrencyToken() - Returns true if the item is a currency token
#endif
    { ENV_NONE, "IsNotEmptyBag", &LuaItem::IsNotEmptyBag },                 // :IsNotEmptyBag() - Returns true if the item is not an empty bag
    { ENV_NONE, "IsBroken", &LuaItem::IsBroken },                           // :IsBroken() - Returns true if the item is broken
    { ENV_NONE, "CanBeTraded", &LuaItem::CanBeTraded },                     // :CanBeTraded() - Returns true if the item can be traded
    { ENV_NONE, "IsInTrade", &LuaItem::IsInTrade },                         // :IsInTrade() - Returns true if the item is in trade
    { ENV_NONE, "IsInBag", &LuaItem::IsInBag },                             // :IsInBag() - Returns true if the item is in a bag
    { ENV_NONE, "IsEquipped", &LuaItem::IsEquipped },                       // :IsEquipped() - Returns true if the item is equipped
    { ENV_NONE, "HasQuest", &LuaItem::HasQuest },                           // :HasQuest(questId) - Returns true if the item starts the quest
    { ENV_NONE, "IsPotion", &LuaItem::IsPotion },                           // :IsPotion() - Returns true if the item is a potion
#ifndef CATA
    { ENV_NONE, "IsWeaponVellum", &LuaItem::IsWeaponVellum },               // :IsWeaponVellum() - Returns true if the item is a weapon vellum
    { ENV_NONE, "IsArmorVellum", &LuaItem::IsArmorVellum },                 // :IsArmorVellum() - Returns true if the item is an armor vellum
#endif
    { ENV_NONE, "IsConjuredConsumable", &LuaItem::IsConjuredConsumable },   // :IsConjuredConsumable() - Returns true if the item is a conjured consumable
    // { "IsRefundExpired", &LuaItem::IsRefundExpired },          // :IsRefundExpired() - Returns true if the item's refund time has expired
    { ENV_NONE, "SetEnchantment", &LuaItem::SetEnchantment },               // :SetEnchantment(enchantid, enchantmentslot) - Sets a new enchantment for the item. Returns true on success
    { ENV_NONE, "ClearEnchantment", &LuaItem::ClearEnchantment },           // :ClearEnchantment(enchantmentslot) - Removes the enchantment from the item if one exists. Returns true on success

    // Other
    { ENV_NONE, "SaveToDB", &LuaItem::SaveToDB },                           // :SaveToDB() - Saves to database

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Aura> AuraMethods[] =
{
    // Getters
    { ENV_BOTH, "GetCaster", &LuaAura::GetCaster },
    { ENV_BOTH, "GetCasterGUID", &LuaAura::GetCasterGUID },
    { ENV_BOTH, "GetCasterLevel", &LuaAura::GetCasterLevel },
    { ENV_BOTH, "GetDuration", &LuaAura::GetDuration },
    { ENV_BOTH, "GetMaxDuration", &LuaAura::GetMaxDuration },
    { ENV_BOTH, "GetAuraId", &LuaAura::GetAuraId },
    { ENV_BOTH, "GetStackAmount", &LuaAura::GetStackAmount },
    { ENV_BOTH, "GetOwner", &LuaAura::GetOwner },

    // Setters
    { ENV_BOTH, "SetDuration", &LuaAura::SetDuration },
    { ENV_BOTH, "SetMaxDuration", &LuaAura::SetMaxDuration },
    { ENV_BOTH, "SetStackAmount", &LuaAura::SetStackAmount },

    // Other
    { ENV_BOTH, "Remove", &LuaAura::Remove },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Spell> SpellMethods[] =
{
    // Getters
    { ENV_BOTH, "GetCaster", &LuaSpell::GetCaster },
    { ENV_BOTH, "GetCastTime", &LuaSpell::GetCastTime },
    { ENV_BOTH, "GetEntry", &LuaSpell::GetEntry },
    { ENV_BOTH, "GetDuration", &LuaSpell::GetDuration },
    { ENV_BOTH, "GetPowerCost", &LuaSpell::GetPowerCost },
    { ENV_BOTH, "GetTargetDest", &LuaSpell::GetTargetDest },
    { ENV_BOTH, "GetTarget", &LuaSpell::GetTarget },

    // Setters
    { ENV_NONE, "SetAutoRepeat", &LuaSpell::SetAutoRepeat },

    // Boolean
    { ENV_NONE, "IsAutoRepeat", &LuaSpell::IsAutoRepeat },

    // Other
    { ENV_NONE, "Cancel", &LuaSpell::Cancel },
    { ENV_NONE, "Cast", &LuaSpell::Cast },
    { ENV_NONE, "Finish", &LuaSpell::Finish },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Quest> QuestMethods[] =
{
    // Getters
    { ENV_BOTH, "GetId", &LuaQuest::GetId },
    { ENV_BOTH, "GetLevel", &LuaQuest::GetLevel },
    // { "GetMaxLevel", &LuaQuest::GetMaxLevel },                   // :GetMaxLevel() - Returns the quest's max level
    { ENV_BOTH, "GetMinLevel", &LuaQuest::GetMinLevel },
    { ENV_BOTH, "GetNextQuestId", &LuaQuest::GetNextQuestId },
    { ENV_BOTH, "GetPrevQuestId", &LuaQuest::GetPrevQuestId },
    { ENV_BOTH, "GetNextQuestInChain", &LuaQuest::GetNextQuestInChain },
    { ENV_BOTH, "GetFlags", &LuaQuest::GetFlags },
    { ENV_BOTH, "GetType", &LuaQuest::GetType },

    // Boolean
    { ENV_BOTH, "HasFlag", &LuaQuest::HasFlag },
#ifndef CLASSIC
    { ENV_BOTH, "IsDaily", &LuaQuest::IsDaily },
#endif
    { ENV_BOTH, "IsRepeatable", &LuaQuest::IsRepeatable },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Group> GroupMethods[] =
{
    // Getters
    { ENV_NONE, "GetMembers", &LuaGroup::GetMembers },
    { ENV_NONE, "GetLeaderGUID", &LuaGroup::GetLeaderGUID },
    { ENV_NONE, "GetGUID", &LuaGroup::GetGUID },
    { ENV_NONE, "GetMemberGroup", &LuaGroup::GetMemberGroup },
    { ENV_NONE, "GetMemberGUID", &LuaGroup::GetMemberGUID },
    { ENV_NONE, "GetMembersCount", &LuaGroup::GetMembersCount },

    // Setters
    { ENV_NONE, "SetLeader", &LuaGroup::SetLeader },
    { ENV_NONE, "SetMembersGroup", &LuaGroup::SetMembersGroup },
    { ENV_NONE, "SetTargetIcon", &LuaGroup::SetTargetIcon },

    // Boolean
    { ENV_NONE, "IsLeader", &LuaGroup::IsLeader },
    { ENV_NONE, "AddMember", &LuaGroup::AddMember },
    { ENV_NONE, "RemoveMember", &LuaGroup::RemoveMember },
    { ENV_NONE, "Disband", &LuaGroup::Disband },
    { ENV_NONE, "IsFull", &LuaGroup::IsFull },
    // { "IsLFGGroup", &LuaGroup::IsLFGGroup },                     // :IsLFGGroup() - Returns true if the group is an LFG group
    { ENV_NONE, "IsRaidGroup", &LuaGroup::IsRaidGroup },
    { ENV_NONE, "IsBGGroup", &LuaGroup::IsBGGroup },
    // { "IsBFGroup", &LuaGroup::IsBFGroup },                       // :IsBFGroup() - Returns true if the group is a battlefield group
    { ENV_NONE, "IsMember", &LuaGroup::IsMember },
    { ENV_NONE, "IsAssistant", &LuaGroup::IsAssistant },
    { ENV_NONE, "SameSubGroup", &LuaGroup::SameSubGroup },
    { ENV_NONE, "HasFreeSlotSubGroup", &LuaGroup::HasFreeSlotSubGroup },

    // Other
    { ENV_NONE, "SendPacket", &LuaGroup::SendPacket },
    // { "ConvertToLFG", &LuaGroup::ConvertToLFG },                 // :ConvertToLFG() - Converts the group to an LFG group
    { ENV_NONE, "ConvertToRaid", &LuaGroup::ConvertToRaid },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Guild> GuildMethods[] =
{
    // Getters
    { ENV_NONE, "GetMembers", &LuaGuild::GetMembers },                  // :GetMembers() - returns a table containing the players in this guild. (Online?)
    { ENV_NONE, "GetLeader", &LuaGuild::GetLeader },                    // :GetLeader() - Returns the guild learder's object
    { ENV_NONE, "GetLeaderGUID", &LuaGuild::GetLeaderGUID },            // :GetLeaderGUID() - Returns the guild learder's guid
    { ENV_NONE, "GetId", &LuaGuild::GetId },                            // :GetId() - Gets the guild's ID
    { ENV_NONE, "GetName", &LuaGuild::GetName },                        // :GetName() - Gets the guild name
    { ENV_NONE, "GetMOTD", &LuaGuild::GetMOTD },                        // :GetMOTD() - Gets the guild MOTD string
    { ENV_NONE, "GetInfo", &LuaGuild::GetInfo },                        // :GetInfo() - Gets the guild info string
    { ENV_NONE, "GetMemberCount", &LuaGuild::GetMemberCount },          // :GetMemberCount() - Returns the amount of players in the guild

    // Setters
#ifndef CLASSIC
    { ENV_NONE, "SetBankTabText", &LuaGuild::SetBankTabText },          // :SetBankTabText(tabId, text)
#endif
    { ENV_NONE, "SetMemberRank", &LuaGuild::SetMemberRank },         // :SetMemberRank(player, newRank) - Sets the player rank in the guild to the new rank
#ifndef CATA
    { ENV_NONE, "SetLeader", &LuaGuild::SetLeader },                    // :SetLeader() - Sets the guild's leader
#endif

    // Boolean

    // Other
    { ENV_NONE, "SendPacket", &LuaGuild::SendPacket },                  // :SendPacket(packet) - sends packet to guild
    { ENV_NONE, "SendPacketToRanked", &LuaGuild::SendPacketToRanked },  // :SendPacketToRanked(packet, rankId) - sends packet to guild, specifying a rankId will only send the packet to your ranked members
    { ENV_NONE, "Disband", &LuaGuild::Disband },                        // :Disband() - Disbands the guild
    { ENV_NONE, "AddMember", &LuaGuild::AddMember },                    // :AddMember(player, rank) - adds the player to the guild. Rank is optional
    { ENV_NONE, "DeleteMember", &LuaGuild::DeleteMember },              // :DeleteMember(player, disbanding, kicked) - Deletes the player from the guild. Disbanding and kicked are optional bools
#ifndef CLASSIC
    { ENV_NONE, "DepositBankMoney", &LuaGuild::DepositBankMoney },      // :DepositBankMoney(money) - Deposits money into the guild bank
    { ENV_NONE, "WithdrawBankMoney", &LuaGuild::WithdrawBankMoney },    // :WithdrawBankMoney(money) - Withdraws money from the guild bank
#endif

    { ENV_NONE, nullptr, nullptr },
};

#ifndef CLASSIC
#ifndef TBC
ElunaRegister<Vehicle> VehicleMethods[] =
{
    // Getters
    { ENV_NONE, "GetOwner", &LuaVehicle::GetOwner },                    // :GetOwner() - Returns the the vehicle unit
    { ENV_NONE, "GetEntry", &LuaVehicle::GetEntry },                    // :GetEntry() - Returns vehicle ID
    { ENV_NONE, "GetPassenger", &LuaVehicle::GetPassenger },            // :GetPassenger(seatId) - Returns the passenger by seatId

    // Boolean
    { ENV_NONE, "IsOnBoard", &LuaVehicle::IsOnBoard },                  // :IsOnBoard(unit) - Returns true if the unit is on board

    // Other
    { ENV_NONE, "AddPassenger", &LuaVehicle::AddPassenger },            // :AddPassenger(passenger, seatId) - Adds a vehicle passenger
    { ENV_NONE, "RemovePassenger", &LuaVehicle::RemovePassenger },      // :RemovePassenger(passenger) - Removes the passenger from the vehicle

    { ENV_NONE, nullptr, nullptr },
};
#endif
#endif

ElunaRegister<ElunaQuery> QueryMethods[] =
{
    { ENV_BOTH, "NextRow", &LuaQuery::NextRow },                        // :NextRow() - Advances to next rown in the query. Returns true if there is a next row, otherwise false
    { ENV_BOTH, "GetColumnCount", &LuaQuery::GetColumnCount },          // :GetColumnCount() - Gets the column count of the query
    { ENV_BOTH, "GetRowCount", &LuaQuery::GetRowCount },                // :GetRowCount() - Gets the row count of the query
    { ENV_BOTH, "GetRow", &LuaQuery::GetRow },

    { ENV_BOTH, "GetBool", &LuaQuery::GetBool },                        // :GetBool(column) - returns a bool from a number column (for example tinyint)
    { ENV_BOTH, "GetUInt8", &LuaQuery::GetUInt8 },                      // :GetUInt8(column) - returns the value of an unsigned tinyint column
    { ENV_BOTH, "GetUInt16", &LuaQuery::GetUInt16 },                    // :GetUInt16(column) - returns the value of a unsigned smallint column
    { ENV_BOTH, "GetUInt32", &LuaQuery::GetUInt32 },                    // :GetUInt32(column) - returns the value of an unsigned int or mediumint column
    { ENV_BOTH, "GetUInt64", &LuaQuery::GetUInt64 },                    // :GetUInt64(column) - returns the value of an unsigned bigint column as string
    { ENV_BOTH, "GetInt8", &LuaQuery::GetInt8 },                        // :GetInt8(column) - returns the value of an tinyint column
    { ENV_BOTH, "GetInt16", &LuaQuery::GetInt16 },                      // :GetInt16(column) - returns the value of a smallint column
    { ENV_BOTH, "GetInt32", &LuaQuery::GetInt32 },                      // :GetInt32(column) - returns the value of an int or mediumint column
    { ENV_BOTH, "GetInt64", &LuaQuery::GetInt64 },                      // :GetInt64(column) - returns the value of a bigint column as string
    { ENV_BOTH, "GetFloat", &LuaQuery::GetFloat },                      // :GetFloat(column) - returns the value of a float column
    { ENV_BOTH, "GetDouble", &LuaQuery::GetDouble },                    // :GetDouble(column) - returns the value of a double column
    { ENV_BOTH, "GetString", &LuaQuery::GetString },                    // :GetString(column) - returns the value of a string column, always returns a string
    { ENV_BOTH, "IsNull", &LuaQuery::IsNull },                          // :IsNull(column) - returns true if the column is null

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<WorldPacket> PacketMethods[] =
{
    // Getters
    { ENV_BOTH, "GetOpcode", &LuaPacket::GetOpcode },
    { ENV_BOTH, "GetSize", &LuaPacket::GetSize },

    // Setters
    { ENV_BOTH, "SetOpcode", &LuaPacket::SetOpcode },

    // Readers
    { ENV_BOTH, "ReadByte", &LuaPacket::ReadByte },
    { ENV_BOTH, "ReadUByte", &LuaPacket::ReadUByte },
    { ENV_BOTH, "ReadShort", &LuaPacket::ReadShort },
    { ENV_BOTH, "ReadUShort", &LuaPacket::ReadUShort },
    { ENV_BOTH, "ReadLong", &LuaPacket::ReadLong },
    { ENV_BOTH, "ReadULong", &LuaPacket::ReadULong },
    { ENV_BOTH, "ReadGUID", &LuaPacket::ReadGUID },
    { ENV_BOTH, "ReadString", &LuaPacket::ReadString },
    { ENV_BOTH, "ReadFloat", &LuaPacket::ReadFloat },
    { ENV_BOTH, "ReadDouble", &LuaPacket::ReadDouble },

    // Writers
    { ENV_BOTH, "WriteByte", &LuaPacket::WriteByte },                   // :WriteByte(val) - Writes an int8 value
    { ENV_BOTH, "WriteUByte", &LuaPacket::WriteUByte },                 // :WriteUByte(val) - Writes a uint8 value
    { ENV_BOTH, "WriteShort", &LuaPacket::WriteShort },                 // :WriteShort(val) - Writes an int16 value
    { ENV_BOTH, "WriteUShort", &LuaPacket::WriteUShort },               // :WriteUShort(val) - Writes a uint16 value
    { ENV_BOTH, "WriteLong", &LuaPacket::WriteLong },                   // :WriteLong(val) - Writes an int32 value
    { ENV_BOTH, "WriteULong", &LuaPacket::WriteULong },                 // :WriteULong(val) - Writes a uint32 value
    { ENV_BOTH, "WriteGUID", &LuaPacket::WriteGUID },                   // :WriteGUID(guid) - Writes a uint64 value
    { ENV_BOTH, "WriteString", &LuaPacket::WriteString },               // :WriteString(val) - Writes a string value
    { ENV_BOTH, "WriteFloat", &LuaPacket::WriteFloat },                 // :WriteFloat(val) - Writes a float value
    { ENV_BOTH, "WriteDouble", &LuaPacket::WriteDouble },               // :WriteDouble(val) - Writes a double value

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Map> MapMethods[] =
{
    // Getters
    { ENV_BOTH, "GetName", &LuaMap::GetName },                          // :GetName() - Returns the map's name UNDOCUMENTED
    { ENV_BOTH, "GetDifficulty", &LuaMap::GetDifficulty },              // :GetDifficulty() - Returns the map's difficulty UNDOCUMENTED
    { ENV_BOTH, "GetInstanceId", &LuaMap::GetInstanceId },              // :GetInstanceId() - Returns the map's instance ID UNDOCUMENTED
    { ENV_BOTH, "GetPlayers", &LuaMap::GetPlayers },
    { ENV_BOTH, "GetPlayerCount", &LuaMap::GetPlayerCount },            // :GetPlayerCount() - Returns the amount of players on map except GM's UNDOCUMENTED
    { ENV_BOTH, "GetMapId", &LuaMap::GetMapId },                        // :GetMapId() - Returns the map's ID UNDOCUMENTED
    { ENV_BOTH, "GetAreaId", &LuaMap::GetAreaId },                      // :GetAreaId(x, y, z) - Returns the map's area ID based on coords UNDOCUMENTED
    { ENV_BOTH, "GetHeight", &LuaMap::GetHeight },                      // :GetHeight(x, y[, phasemask]) - Returns ground Z coordinate. UNDOCUMENTED
    { ENV_BOTH, "GetWorldObject", &LuaMap::GetWorldObject },            // :GetWorldObject(guid) - Returns a worldobject (player, creature, gameobject..) from the map by it's guid

    // Setters
    { ENV_BOTH, "SetWeather", &LuaMap::SetWeather },

    // Booleans
#ifndef CLASSIC
    { ENV_BOTH, "IsArena", &LuaMap::IsArena },                          // :IsArena() - Returns the true if the map is an arena, else false UNDOCUMENTED
#endif
    { ENV_BOTH, "IsBattleground", &LuaMap::IsBattleground },            // :IsBattleground() - Returns the true if the map is a battleground, else false UNDOCUMENTED
    { ENV_BOTH, "IsDungeon", &LuaMap::IsDungeon },                      // :IsDungeon() - Returns the true if the map is a dungeon , else false UNDOCUMENTED
    { ENV_BOTH, "IsEmpty", &LuaMap::IsEmpty },                          // :IsEmpty() - Returns the true if the map is empty, else false UNDOCUMENTED
#ifndef CLASSIC
    { ENV_BOTH, "IsHeroic", &LuaMap::IsHeroic },                        // :IsHeroic() - Returns the true if the map is a heroic dungeon, else false UNDOCUMENTED
#endif
    { ENV_BOTH, "IsRaid", &LuaMap::IsRaid },                            // :IsRaid() - Returns the true if the map is a raid map, else false UNDOCUMENTED

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Corpse> CorpseMethods[] =
{
    { ENV_NONE, "GetOwnerGUID", &LuaCorpse::GetOwnerGUID },
    { ENV_NONE, "GetGhostTime", &LuaCorpse::GetGhostTime },
    { ENV_NONE, "GetType", &LuaCorpse::GetType },
    { ENV_NONE, "ResetGhostTime", &LuaCorpse::ResetGhostTime },
    { ENV_NONE, "SaveToDB", &LuaCorpse::SaveToDB },
    { ENV_NONE, "DeleteBonesFromWorld", &LuaCorpse::DeleteBonesFromWorld },

    { ENV_NONE, nullptr, nullptr }
};

ElunaRegister<AuctionHouseEntry> AuctionMethods[] =
{
    { ENV_NONE, nullptr, nullptr }
};

ElunaRegister<BattleGround> BattleGroundMethods[] =
{
    // Getters
    { ENV_NONE, "GetName", &LuaBattleGround::GetName },
    { ENV_NONE, "GetAlivePlayersCountByTeam", &LuaBattleGround::GetAlivePlayersCountByTeam },
    { ENV_NONE, "GetMap", &LuaBattleGround::GetMap },
    { ENV_NONE, "GetBonusHonorFromKillCount", &LuaBattleGround::GetBonusHonorFromKillCount },
    { ENV_NONE, "GetBracketId", &LuaBattleGround::GetBracketId },
    { ENV_NONE, "GetEndTime", &LuaBattleGround::GetEndTime },
    { ENV_NONE, "GetFreeSlotsForTeam", &LuaBattleGround::GetFreeSlotsForTeam },
    { ENV_NONE, "GetInstanceId", &LuaBattleGround::GetInstanceId },
    { ENV_NONE, "GetMapId", &LuaBattleGround::GetMapId },
    { ENV_NONE, "GetTypeId", &LuaBattleGround::GetTypeId },
    { ENV_NONE, "GetMaxLevel", &LuaBattleGround::GetMaxLevel },
    { ENV_NONE, "GetMinLevel", &LuaBattleGround::GetMinLevel },
    { ENV_NONE, "GetMaxPlayers", &LuaBattleGround::GetMaxPlayers },
    { ENV_NONE, "GetMinPlayers", &LuaBattleGround::GetMinPlayers },
    { ENV_NONE, "GetMaxPlayersPerTeam", &LuaBattleGround::GetMaxPlayersPerTeam },
    { ENV_NONE, "GetMinPlayersPerTeam", &LuaBattleGround::GetMinPlayersPerTeam },
    { ENV_NONE, "GetWinner", &LuaBattleGround::GetWinner },
    { ENV_NONE, "GetStatus", &LuaBattleGround::GetStatus },

    // Setters

    { ENV_NONE, nullptr, nullptr }
};

ElunaRegister<uint64> uint64Methods[] =
{
    { ENV_NONE, "__add", &Luauint64::__add },
    { ENV_NONE, "__sub", &Luauint64::__sub },
    { ENV_NONE, "__mul", &Luauint64::__mul },
    { ENV_NONE, "__div", &Luauint64::__div },
    { ENV_NONE, "__mod", &Luauint64::__mod },
    { ENV_NONE, "__pow", &Luauint64::__pow },
    { ENV_NONE, "__eq", &Luauint64::__eq },
    { ENV_NONE, "__lt", &Luauint64::__lt },
    { ENV_NONE, "__le", &Luauint64::__le },
    { ENV_NONE, "__tostring", &Luauint64::__tostring },

    { ENV_NONE, nullptr, nullptr }
};

template<typename T> const char* ElunaTemplate<T>::tname = nullptr;
template<typename T> bool ElunaTemplate<T>::manageMemory = false;

#if (!defined(TBC) && !defined(CLASSIC))
// fix compile error about accessing vehicle destructor
template<> int ElunaTemplate<Vehicle>::CollectGarbage(lua_State* L)
{
    ASSERT(!manageMemory);

    // Get object pointer (and check type, no error)
    ElunaObject* obj = Eluna::CHECKOBJ<ElunaObject>(L, 1, false);
    delete obj;
    return 0;
}
#endif

void RegisterFunctions(Eluna* E)
{
    ElunaGlobal::SetMethods(E, GlobalMethods);

    ElunaTemplate<Object>::Register(E, "Object");
    ElunaTemplate<Object>::SetMethods(E, ObjectMethods);

    ElunaTemplate<WorldObject>::Register(E, "WorldObject");
    ElunaTemplate<WorldObject>::SetMethods(E, ObjectMethods);
    ElunaTemplate<WorldObject>::SetMethods(E, WorldObjectMethods);

    ElunaTemplate<Unit>::Register(E, "Unit");
    ElunaTemplate<Unit>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, UnitMethods);

    ElunaTemplate<Player>::Register(E, "Player");
    ElunaTemplate<Player>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, UnitMethods);
    ElunaTemplate<Player>::SetMethods(E, PlayerMethods);

    ElunaTemplate<Creature>::Register(E, "Creature");
    ElunaTemplate<Creature>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, UnitMethods);
    ElunaTemplate<Creature>::SetMethods(E, CreatureMethods);

    ElunaTemplate<GameObject>::Register(E, "GameObject");
    ElunaTemplate<GameObject>::SetMethods(E, ObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, GameObjectMethods);

    ElunaTemplate<Corpse>::Register(E, "Corpse");
    ElunaTemplate<Corpse>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, CorpseMethods);

    ElunaTemplate<Item>::Register(E, "Item");
    ElunaTemplate<Item>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Item>::SetMethods(E, ItemMethods);

#ifndef CLASSIC
#ifndef TBC
    ElunaTemplate<Vehicle>::Register(E, "Vehicle");
    ElunaTemplate<Vehicle>::SetMethods(E, VehicleMethods);
#endif
#endif

    ElunaTemplate<Group>::Register(E, "Group");
    ElunaTemplate<Group>::SetMethods(E, GroupMethods);

    ElunaTemplate<Guild>::Register(E, "Guild");
    ElunaTemplate<Guild>::SetMethods(E, GuildMethods);

    ElunaTemplate<Aura>::Register(E, "Aura");
    ElunaTemplate<Aura>::SetMethods(E, AuraMethods);

    ElunaTemplate<Spell>::Register(E, "Spell");
    ElunaTemplate<Spell>::SetMethods(E, SpellMethods);

    ElunaTemplate<Quest>::Register(E, "Quest");
    ElunaTemplate<Quest>::SetMethods(E, QuestMethods);

    ElunaTemplate<Map>::Register(E, "Map");
    ElunaTemplate<Map>::SetMethods(E, MapMethods);

    ElunaTemplate<AuctionHouseEntry>::Register(E, "AuctionHouseEntry");
    ElunaTemplate<AuctionHouseEntry>::SetMethods(E, AuctionMethods);

    ElunaTemplate<BattleGround>::Register(E, "BattleGround");
    ElunaTemplate<BattleGround>::SetMethods(E, BattleGroundMethods);

    ElunaTemplate<WorldPacket>::Register(E, "WorldPacket", true);
    ElunaTemplate<WorldPacket>::SetMethods(E, PacketMethods);

    ElunaTemplate<ElunaQuery>::Register(E, "ElunaQuery", true);
    ElunaTemplate<ElunaQuery>::SetMethods(E, QueryMethods);

    ElunaTemplate<uint64>::Register(E, "uint64", true);
    ElunaTemplate<uint64>::SetMethods(E, uint64Methods);
}
