CC       = gcc
CXX      = g++
CFLAGS   = -I lua
CXXFLAGS = -I lua -I src

LUA_DIR   = lua
SRC_DIR   = src
BUILD_DIR = build
OBJ_DIR   = build/obj

DLLS = /ucrt64/bin/libgcc_s_seh-1.dll \
       /ucrt64/bin/libstdc++-6.dll \
       /ucrt64/bin/libwinpthread-1.dll

LUA_SRCS = $(wildcard $(LUA_DIR)/*.c)
LUA_OBJS = $(patsubst $(LUA_DIR)/%.c, $(OBJ_DIR)/%.o, $(LUA_SRCS))

SRC_SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/lib/*.cpp)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, \
           $(patsubst $(SRC_DIR)/lib/%.cpp, $(OBJ_DIR)/%.o, $(SRC_SRCS)))

LUA_LIB  = $(BUILD_DIR)/liblua.a
TARGET   = $(BUILD_DIR)/fred.exe

all: $(OBJ_DIR) $(LUA_LIB) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(LUA_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/lib/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LUA_LIB): $(LUA_OBJS)
	ar rcs $@ $^

$(TARGET): $(SRC_OBJS) $(LUA_LIB)
	$(CXX) -static-libgcc -static-libstdc++ $^ -o $@

deploy: all
	cp $(DLLS) $(BUILD_DIR)/

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all deploy clean