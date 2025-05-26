# Makefile for ncurses-based RPG app (lifes)
# Optimized for Lenovo IdeaPad G485 (2012, 4GB RAM) on Artix Linux with linux-zen
# Supports try/catch for std::stoi input validation

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
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Files
SOURCES = main.cpp render.cpp control.cpp entities.cpp data.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/lifes

# Header files for dependency tracking
HEADERS = main.h

# Default target
all: $(EXECUTABLE)

# Link object files to create executable
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	@echo "Linking $@..."
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling $<..."
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

# Generate dependency files during compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -M $< > $(OBJ_DIR)/$*.d
	$(CXX) $(CXXFLAGS) -c $< -o $@