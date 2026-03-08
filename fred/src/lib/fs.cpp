#include "../fred.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// fred.fs.read(path) -> returns file contents as a string
static int fredFsRead(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);

    std::ifstream file(path);
    if (!file.is_open()) {
        lua_pushnil(L);
        lua_pushstring(L, "could not open file");
        return 2;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    lua_pushstring(L, buffer.str().c_str());
    return 1;
}

// fred.fs.write(path, content) -> writes string to file
static int fredFsWrite(lua_State* L) {
    const char* path    = luaL_checkstring(L, 1);
    const char* content = luaL_checkstring(L, 2);

    std::ofstream file(path);
    if (!file.is_open()) {
        lua_pushboolean(L, 0);
        lua_pushstring(L, "could not open file for writing");
        return 2;
    }

    file << content;
    lua_pushboolean(L, 1);
    return 1;
}

// fred.fs.exists(path) -> returns true or false
static int fredFsExists(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);

    std::ifstream file(path);
    lua_pushboolean(L, file.is_open() ? 1 : 0);
    return 1;
}

static const luaL_Reg fsLib[] = {
    {"read",   fredFsRead},
    {"write",  fredFsWrite},
    {"exists", fredFsExists},
    {NULL, NULL}
};

void registerFS(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, fsLib, 0);
    lua_setfield(L, -2, "fs");
}