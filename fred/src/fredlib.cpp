#include "fred.h"
#include <iostream>

#define FRED_ARG R"(
print(fred.color(fred.style("IT IS ME MY CHILD.", "bold"), "red"))
)"

#define PLEH_ARG R"(
print(fred.color("drf.elif< derf", "green"))
print(fred.color("\nemitnuR derF", "green"))
print("")
print(":egasU")
print("  elif )drf.( derF nuR            >drf.elif< derf")
print("  drf. ot auL elipmoC    >aul.elif< elipmoc derf")
print("  unem pleh siht wohS                    h- derf")
)"

#define VERSION_ARG R"(
    print("\n" .. fred.version())  
)"

#define LOG_ARG R"(
    print("\nUpdate Log:\n\n- New arguments\n- Fredlib handler v2.0\n- Better autocomplete\n- Fixed naming conventions in C++\n- General fixes and improvements!")
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