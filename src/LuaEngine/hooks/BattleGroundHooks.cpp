/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    if (!IsEnabled())\
        return;\
    auto key = EventKey<BGEvents>(EVENT);\
    if (!BGEventBindings->HasBindingsFor(key))\
        return;\
    LOCK_ELUNA

void Eluna::OnBGStart(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_START);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGEnd(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId, TeamId winner)
{
    START_HOOK(BG_EVENT_ON_END);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    Push(winner);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGCreate(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_CREATE);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGDestroy(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_PRE_DESTROY);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    CallAllFunctions(BGEventBindings, key);
}

void Eluna::OnBGObjectiveCaptured(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId, Player* player, uint32 eventType)
{
    START_HOOK(BG_EVENT_ON_OBJECTIVE_CAPTURED);
    Push(bg);
    Push(bgId);
    Push(instanceId);
    Push(player);
    Push(eventType);
    CallAllFunctions(BGEventBindings, key);
    printf("OnBGObjectiveCaptured called for bgId: %u, instanceId: %u, player: %s, eventType: %u\n",
        static_cast<unsigned int>(bgId), instanceId, player ? player->GetName().c_str() : "NULL", eventType);
}

void Eluna::OnArenaEnd(Player* player, uint32 Own_MMRating, uint32 Opponent_MMRating, bool Won)
{
    START_HOOK(BG_EVENT_ON_ARENA_END);
    Push(player);
    Push(Own_MMRating);
    Push(Opponent_MMRating);
    Push(Won);
    CallAllFunctions(BGEventBindings, key);
}
