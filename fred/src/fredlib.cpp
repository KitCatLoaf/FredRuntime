#include "fred.h"
#include <iostream>

#define FRED_ARG R"(
print(fred.color(fred.style("IT IS ME MY CHILD.", "bold"), "red"))
)"

#define PLEH_ARG R"(
local lines = {
    "",
    fred.version(),
    "",
    "Usage:",
    "  fred <file.frd>            Run Fred (.frd) file",
    "  fred compile <file.lua>    Compile Lua to .frd",
    "  fred -h, --help            Show this help menu",
    "  fred -v, --version         Show version",
    "  fred -l, --log             View the latest update log",
    "",
}
for i = #lines, 1, -1 do
    print(string.reverse(lines[i]))
end
)"

#define VERSION_ARG R"(
    print("\n" .. fred.version())  
)"

#define LOG_ARG R"(
    print("\nUpdate Log:\n\n- More fs library additions\n- Autocomplete Update\n- FredSetup.exe file for easy installation\n- use require('fred.fs') and use fs.[command] now.")
)"

void registerFred(lua_State* L) {
    lua_newtable(L);
    registerCore(L);
    registerIO(L);
    registerFS(L);
    registerTime(L);
    lua_setglobal(L, "fred");
}

void fredArg(lua_State* L) {
    luaL_dostring(L, FRED_ARG);
}

void plehArg(lua_State* L) {
    luaL_dostring(L, PLEH_ARG);
}

void versionArg(lua_State* L) {
    luaL_dostring(L, VERSION_ARG);
}

void logArg(lua_State* L) {
    luaL_dostring(L, LOG_ARG);
}