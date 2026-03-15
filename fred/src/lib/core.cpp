#include "../fred.h"
#include <string>

#define FRED_NAME "Fred Runtime"
#define FRED_VERSION " v1.3 [ALPHA]"
#define FRED_FULL FRED_NAME FRED_VERSION

static int fredVersion(lua_State* L) {
    lua_pushstring(L, FRED_FULL);
    return 1;
}

static int fredPlatform(lua_State* L) {
    #ifdef _WIN32
        lua_pushstring(L, "windows");
    #elif __APPLE__
        lua_pushstring(L, "mac");
    #elif __linux__
        lua_pushstring(L, "linux");
    #else
        lua_pushstring(L, "unknown");
    #endif
    return 1;
}

static int fredExit(lua_State* L) {
    int code = luaL_optinteger(L, 1, 0);
    exit(code);
    return 0;
}

static const luaL_Reg coreLib[] = {
    {"version",  fredVersion},
    {"platform", fredPlatform},
    {"exit",     fredExit},
    {NULL, NULL}
};

void registerCore(lua_State* L) {
    luaL_setfuncs(L, coreLib, 0);
}