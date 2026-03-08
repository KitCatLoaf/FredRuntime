#pragma once

extern "C" {
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}

void registerFred(lua_State* L);
void fredArg(lua_State* L);
void plehArg(lua_State* L);
void versionArg(lua_State* L);
void logArg(lua_State* L);