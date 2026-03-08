CC       = gcc
CXX      = g++
CFLAGS   = -I lua
CXXFLAGS = -I lua -I src

LUA_DIR   = lua
SRC_DIR   = src
BUILD_DIR = build
OBJ_DIR   = build/obj

LUA_SRCS = $(wildcard $(LUA_DIR)/*.c)
LUA_OBJS = $(patsubst $(LUA_DIR)/%.c, $(OBJ_DIR)/%.o, $(LUA_SRCS))

SRC_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_SRCS))

LUA_LIB  = $(BUILD_DIR)/liblua.a
TARGET   = $(BUILD_DIR)/fred.exe

all: $(OBJ_DIR) $(LUA_LIB) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(LUA_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LUA_LIB): $(LUA_OBJS)
	ar rcs $@ $^

$(TARGET): $(SRC_OBJS) $(LUA_LIB)
	$(CXX) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean