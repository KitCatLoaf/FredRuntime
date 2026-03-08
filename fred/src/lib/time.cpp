#include "../fred.h"
#include <ctime>
#include <string>

static int fredTime(lua_State* L) {
    lua_pushnumber(L, (double)time(NULL));
    return 1;
}

static int fredDate(lua_State* L) {
    const char* fmt = luaL_optstring(L, 1, "%Y-%m-%d %H:%M:%S");

    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    char buf[128];
    strftime(buf, sizeof(buf), fmt, t);

    lua_pushstring(L, buf);
    return 1;
}

static const luaL_Reg timeLib[] = {
    {"time", fredTime},
    {"date", fredDate},
    {NULL, NULL}
};

void registerTime(lua_State* L) {
    luaL_setfuncs(L, timeLib, 0);
}