CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -fno-rtti -flto
LDFLAGS = -lncurses -s -flto

BUILD ?= release
ifeq ($(BUILD), debug)
    CXXFLAGS += -g -O0 -DDEBUG
    CXXFLAGS := $(filter-out -flto,$(CXXFLAGS))
    LDFLAGS := $(filter-out -flto,$(LDFLAGS))
else
    CXXFLAGS += -Os
endif

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/render.cpp $(SRC_DIR)/control.cpp $(SRC_DIR)/entities.cpp $(SRC_DIR)/data.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
EXECUTABLE = $(BIN_DIR)/lifes

HEADERS = $(SRC_DIR)/main.h

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	@echo "Linking $@..."
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete."

.PHONY: all clean

-include $(OBJECTS:.o=.d)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -M $< > $(OBJ_DIR)/$*.d
	$(CXX) $(CXXFLAGS) -c $< -o $@
