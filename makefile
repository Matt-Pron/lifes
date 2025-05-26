# Makefile for lifes

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -fno-rtti -flto
LDFLAGS = -lncurses -s -flto

# Build mode: debug or release (default: release)
# Use `make BUILD=debug` for debug build
BUILD ?= release
ifeq ($(BUILD), debug)
    CXXFLAGS += -g -O0 -DDEBUG
    CXXFLAGS := $(filter-out -flto,$(CXXFLAGS))
    LDFLAGS := $(filter-out -flto,$(LDFLAGS))
else
    CXXFLAGS += -Os
endif

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/render.cpp $(SRC_DIR)/control.cpp $(SRC_DIR)/entities.cpp $(SRC_DIR)/data.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/lifes

# Header files for dependency tracking
HEADERS = $(SRC_DIR)/main.h

# Default target
all: $(EXECUTABLE)

# Link object files to create executable
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	@echo "Linking $@..."
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Compile source files and generate dependencies
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -M $< > $(OBJ_DIR)/$*.d
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if they don't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete."

# Phony targets
.PHONY: all clean

# Dependency tracking
# Automatically include generated dependency files
-include $(OBJECTS:.o=.d)
