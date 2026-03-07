# Fred Runtime - Makefile
CC       = gcc
CXX      = g++
CFLAGS   = -I lua
CXXFLAGS = -I lua

LUA_DIR   = lua
SRC_DIR   = src
BUILD_DIR = build
OBJ_DIR   = build/obj

LUA_SRCS = $(wildcard $(LUA_DIR)/*.c)
LUA_OBJS = $(patsubst $(LUA_DIR)/%.c, $(OBJ_DIR)/%.o, $(LUA_SRCS))

LUA_LIB  = $(BUILD_DIR)/liblua.a
TARGET   = $(BUILD_DIR)/fred.exe

all: $(OBJ_DIR) $(LUA_LIB) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(LUA_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LUA_LIB): $(LUA_OBJS)
	ar rcs $@ $^

$(TARGET): $(SRC_DIR)/main.cpp $(LUA_LIB)
	$(CXX) $(CXXFLAGS) $< -L$(BUILD_DIR) -llua -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean