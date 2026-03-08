#include <iostream>
#include <string>
#include "fred.h"

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
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        registerFred(L);
        versionArg(L);
        lua_close(L);
        std::cout << "Run 'fred -h' for usage.\n";
        return 0;
    }

    if (toLower(std::string(argv[1])) == "-h" || toLower(std::string(argv[1])) == "--help") {
        std::cout << "\nUsage:\n";
        std::cout << "  fred <file.frd>            Run Fred (.frd) file\n";
        std::cout << "  fred compile <file.lua>    Compile Lua to .frd\n";
        std::cout << "  fred -h, --help            Show this help menu\n";
        std::cout << "  fred -v, --version         Show this help menu\n";
        std::cout << "  fred -l, --log             View the latest update log\n";
        return 0;
    }

    if (toLower(std::string(argv[1])) == "--fred") {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        registerFred(L);
        plehArg(L);
        lua_close(L);
        return 0;
    }

    if (toLower(std::string(argv[1])) == "--pleh") {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        registerFred(L);
        plehArg(L);
        lua_close(L);
        return 0;
    }

    if (toLower(std::string(argv[1])) == "-v" || toLower(std::string(argv[1])) == "--version") {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        registerFred(L);
        versionArg(L);
        lua_close(L);
        return 0;
    }

    if (toLower(std::string(argv[1])) == "-l" || toLower(std::string(argv[1])) == "--log") {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        registerFred(L);
        logArg(L);
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