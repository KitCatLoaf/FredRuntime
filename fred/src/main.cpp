#include <iostream>

extern "C" {
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
}

#define FRED_NAME "FRED RUNTIME: "
#define FRED_VERSION "v1.0 [ALPHA]"
#define FRED_FULL FRED_NAME FRED_VERSION

static int fred_version(lua_State* L) {
    lua_pushstring(L, FRED_FULL);
    return 1;
}

static int fred_print(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
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
    const char* text = luaL_checkstring(L, 1);
    const char* style = luaL_optstring(L, 2, "none");

    std::string result = "";

    if (std::string(style) == "bold")       result = "\033[1m";
    else if (std::string(style) == "italic") result = "\033[3m";
    else if (std::string(style) == "underline") result = "\033[4m";

    result += std::string(text) + "\033[0m";

    lua_pushstring(L, result.c_str());
    return 1;
}

static const luaL_Reg fred_lib[] = {
    {"version", fred_version},
    {"color",   fred_print},
    {"style", fred_style},
    {NULL, NULL}
};

static void registerFred(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, fred_lib, 0);
    lua_setglobal(L, "fred");
}

std::string toLower(std::string s) {
    for (char& c : s) {
        c = tolower(c);
    }
    return s;
}

int runFile(lua_State* L, const char* filename) {
    if (luaL_dofile(L, filename)) {
        std::cout << "Error: " << lua_tostring(L, -1) << std::endl;
        return 1;
    }
    return 0;
}

int compileFile(lua_State* L, const char* input, const char* output) {
    if (luaL_loadfile(L, input)) {
        std::cout << "Compile error: " << lua_tostring(L, -1) << std::endl;
        return 1;
    }

    FILE* f = fopen(output, "wb");
    if (!f) {
        std::cout << "Could not open output file: " << output << std::endl;
        return 1;
    }

    lua_dump(L, [](lua_State*, const void* p, size_t sz, void* ud) -> int {
        fwrite(p, sz, 1, (FILE*)ud);
        return 0;
    }, f, 0);

    fclose(f);
    std::cout << "Compiled: " << input << " -> " << output << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "\nFred Runtime v1.0 [ALPHA]\n";
        std::cout << "Run 'fred -h' for usage.\n";
        return 0;
    }

    if (toLower(std::string(argv[1])) == "-h" || toLower(std::string(argv[1])) == "--help") {
        std::cout << "\nFred Runtime v1.0 [ALPHA]\n\n";
        std::cout << "Usage:\n";
        std::cout << "  fred <file.frd>            Run Fred (.frd) file\n";
        std::cout << "  fred compile <file.lua>    Compile Lua to .frd\n";
        std::cout << "  fred -h                    Show this help menu\n";
        // std::cout << " Fred runtime IS case sensitive. Commands and arguments require strict typing.\n";
        return 0;
    }

    if (toLower(std::string(argv[1])) == "--fred") {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        registerFred(L);
        runFile(L, "util/fred.frd");
        lua_close(L);
        return 0;
    }

    if (toLower(std::string(argv[1])) == "--pleh") {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        registerFred(L);
        runFile(L, "util/derf.frd");
        lua_close(L);
        return 0;
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    registerFred(L);

    std::string raw = argv[1];
    std::string cmd = toLower(raw);

    // if (raw != cmd) {
    //     std::cout << "Warning: commands are case insensitive, but lowercase is preferred.\n";
    // }

    if (cmd == "compile") {
        if (argc < 3) {
            std::cout << "Missing input file.\n";
            std::cout << "Run 'fred -h' for usage.\n";
            lua_close(L);
            return 1;
        }

        std::string input = argv[2];
        std::string output;

        if (argc >= 4) {
            output = argv[3];
        } else {
            output = input;
            size_t dot = output.rfind('.');
            if (dot != std::string::npos) output = output.substr(0, dot);
            output += ".frd";
        }

        int result = compileFile(L, input.c_str(), output.c_str());
        lua_close(L);
        return result;
    }

    if (cmd[0] == '-' || std::string(argv[1]) == "--help") {
        std::cout << "Unknown command: " << cmd << "\n";
        std::cout << "Run 'fred -h' for usage.\n";
        lua_close(L);
        return 1;
    }

    int result = runFile(L, argv[1]);
    lua_close(L);
    return result;
}