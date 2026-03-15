#include "../fred.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <direct.h>

static void createDirs(const std::string& path) {
    std::string current = "";
    for (size_t i = 0; i < path.size(); i++) {
        char c = path[i];
        if (c == '/' || c == '\\') {
            if (current != "" && current != "." && current != "..") {
                _mkdir(current.c_str());
            }
        }
        current += c;
    }
    _mkdir(current.c_str());
}

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

static std::string getDirName(const std::string& path) {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) return "";
    return path.substr(0, pos);
}


static int fredFsWrite(lua_State* L) {
    const char* path    = luaL_checkstring(L, 1);
    const char* content = luaL_checkstring(L, 2);

    std::string dir = getDirName(path);
    if (dir != "") {
        createDirs(dir);
    }

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

static int fredFsExists(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);

    std::ifstream file(path);
    lua_pushboolean(L, file.is_open() ? 1 : 0);
    return 1;
}

static int fredFsCopy(lua_State* L) {
    const char* src  = luaL_checkstring(L, 1);
    const char* dest = luaL_checkstring(L, 2);

    std::ifstream in(src, std::ios::binary);
    if (!in.is_open()) {
        lua_pushboolean(L, 0);
        lua_pushstring(L, "could not open source file");
        return 2;
    }

    std::string destDir = getDirName(dest);
    if (destDir != "") {
        createDirs(destDir);
    }

    std::ofstream out(dest, std::ios::binary);
    if (!out.is_open()) {
        lua_pushboolean(L, 0);
        lua_pushstring(L, "could not open destination file");
        return 2;
    }

    out << in.rdbuf();
    lua_pushboolean(L, 1);
    return 1;
}

static int fredFsMkdir(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);
    createDirs(path);
    lua_pushboolean(L, 1);
    return 1;
}

static const luaL_Reg fsLib[] = {
    {"read",   fredFsRead},
    {"write",  fredFsWrite},
    {"exists", fredFsExists},
    {"copy", fredFsCopy},
    {"make", fredFsMkdir},
    {NULL, NULL}
};

void registerFS(lua_State* L) {
    luaL_requiref(L, "fred.fs", [](lua_State* L) -> int {
        luaL_newlib(L, fsLib);
        return 1;
    }, 0);
    lua_pop(L, 1);
}