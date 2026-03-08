#include "fredlib.h"
#include <iostream>
#include <string>

#define FRED_NAME "Fred Runtime: "
#define FRED_VERSION "v1.2 [ALPHA]"
#define FRED_FULL FRED_NAME FRED_VERSION

#define FRED_ARG R"(
print(fred.color(fred.style("IT IS ME MY CHILD.", "bold"), "red"))
)"

#define PLEH_ARG R"(
print(fred.color("\n]AHPLA[ 0.1v emitnuR derF\n", "green"))
print(":egasU\n")
print("  elif )drf.( derF nuR            >drf.elif< derf")
print("  drf. ot auL elipmoC    >aul.elif< elipmoc derf")
print("  unem pleh siht wohS                    h- derf")
)"

#define VERSION_ARG R"(
    print("\n" .. fred.version())
)"

#define LOG_ARG R"(
    print("\n" .. fred.version() .. "\n\nUpdate Log:\n- Added new arguments\n- Revamped fredlib handling\n- Fixed 'util/[file.frd] not found'\n- Embedded .frd util files into C++")
)"

static int fred_version(lua_State* L) {
    lua_pushstring(L, FRED_FULL);
    return 1;
}

static int fred_color(lua_State* L) {
    const char* text  = luaL_checkstring(L, 1);
    const char* color = luaL_optstring(L, 2, "white");

    std::string colorCode = "";

    if (std::string(color) == "red")        colorCode = "\033[31m";
    else if (std::string(color) == "green") colorCode = "\033[32m";
    else if (std::string(color) == "blue")  colorCode = "\033[34m";

    std::string result = colorCode + std::string(text) + "\033[0m";
    lua_pushstring(L, result.c_str());
    return 1;
}

static int fred_style(lua_State* L) {
    const char* text  = luaL_checkstring(L, 1);
    const char* style = luaL_optstring(L, 2, "none");

    std::string styleCode = "";

    if (std::string(style) == "bold")           styleCode = "\033[1m";
    else if (std::string(style) == "italic")    styleCode = "\033[3m";
    else if (std::string(style) == "underline") styleCode = "\033[4m";

    std::string result = styleCode + std::string(text) + "\033[0m";
    lua_pushstring(L, result.c_str());
    return 1;
}

static const luaL_Reg fred_lib[] = {
    {"version", fred_version},
    {"color",   fred_color},
    {"style",   fred_style},
    {NULL, NULL}
};

void registerFred(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, fred_lib, 0);
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