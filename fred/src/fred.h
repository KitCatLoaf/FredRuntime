#pragma once

extern "C" {
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}

void registerCore(lua_State* L);
void registerIO(lua_State* L);
void registerFS(lua_State* L);
void registerTime(lua_State* L);

void registerFred(lua_State* L);

void fredArg(lua_State* L);
void plehArg(lua_State* L);
void versionArg(lua_State* L);
void logArg(lua_State* L);