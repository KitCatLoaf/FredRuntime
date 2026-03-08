#include "../fred.h"
#include <iostream>
#include <string>

static int fredColor(lua_State* L) {
    const char* text  = luaL_checkstring(L, 1);
    const char* color = luaL_optstring(L, 2, "white");

    std::string colorCode = "";

    if (std::string(color) == "red")        colorCode = "\033[31m";
    else if (std::string(color) == "green") colorCode = "\033[32m";
    else if (std::string(color) == "blue")  colorCode = "\033[34m";
    else if (std::string(color) == "yellow")colorCode = "\033[33m";
    else if (std::string(color) == "cyan")  colorCode = "\033[36m";
    else if (std::string(color) == "white") colorCode = "\033[37m";

    std::string result = colorCode + std::string(text) + "\033[0m";
    lua_pushstring(L, result.c_str());
    return 1;
}

static int fredStyle(lua_State* L) {
    const char* text  = luaL_checkstring(L, 1);
    const char* style = luaL_optstring(L, 2, "none");

    std::string styleCode = "";

    if (std::string(style) == "bold")           styleCode = "\033[1m";
    else if (std::string(style) == "italic")    styleCode = "\033[3m";
    else if (std::string(style) == "underline") styleCode = "\033[4m";
    else if (std::string(style) == "dim")       styleCode = "\033[2m";

    std::string result = styleCode + std::string(text) + "\033[0m";
    lua_pushstring(L, result.c_str());
    return 1;
}

// fred.read(prompt) -> prints prompt, returns user input as string
static int fredRead(lua_State* L) {
    const char* prompt = luaL_optstring(L, 1, "");
    std::cout << prompt;

    std::string input;
    std::getline(std::cin, input);

    lua_pushstring(L, input.c_str());
    return 1;
}

static const luaL_Reg ioLib[] = {
    {"color", fredColor},
    {"style", fredStyle},
    {"read",  fredRead},
    {NULL, NULL}
};

void registerIO(lua_State* L) {
    luaL_setfuncs(L, ioLib, 0);
}