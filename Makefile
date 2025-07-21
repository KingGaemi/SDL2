#===============================================================================
# Toolchain
#===============================================================================
CXX      := g++
CXXFLAGS := -Wall -std=c++17 -m64 -g -Iinclude -MMD -MP

LDFLAGS  := -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image \
            -lSDL2_ttf -lSDL2_mixer -lbox2d

#===============================================================================
# Directories
#===============================================================================
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

DEBUG_BIN   := $(BIN_DIR)/debug/main
RELEASE_BIN := $(BIN_DIR)/release/main

#===============================================================================
# Source  → Object mapping (recursive)
#===============================================================================
SOURCES := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPENDS := $(OBJECTS:.o=.d)

#===============================================================================
# Default target
#===============================================================================
.PHONY: all debug release clean
all: debug

#===============================================================================
# Debug & Release
#===============================================================================
debug: $(DEBUG_BIN)

release: CXXFLAGS += -O3 -s
release: $(RELEASE_BIN)

$(DEBUG_BIN) $(RELEASE_BIN): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@ $(LDFLAGS)

#===============================================================================
# Compile each .cpp → .o
#===============================================================================
# obj/foo/bar.o  <--  src/foo/bar.cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# include dependency files
-include $(DEPENDS)

#===============================================================================
# Clean up
#===============================================================================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

