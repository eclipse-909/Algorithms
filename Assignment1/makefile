# Variables
CXX = g++
CXXFLAGS = -std=c++20
SRCS = main.cpp
DEPS = node.hpp stack.hpp queue.hpp
TARGET = Assignment1
BIN_DIR = ../bin

# Detect the operating system
ifeq ($(OS),Windows_NT)
    # Windows-specific settings
    MKDIR = mkdir
    RM = del
else
    # Unix-like systems (Linux, macOS)
    MKDIR = mkdir -p
    RM = rm -f
endif

# Default rule to build the program
all: $(BIN_DIR)/$(TARGET)

# Rule to compile and create the executable in the bin directory
$(BIN_DIR)/$(TARGET): $(SRCS) $(DEPS)
	$(MKDIR) $(BIN_DIR) || true  # Create the bin directory if it doesn't exist; ignore errors
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(BIN_DIR)/$(TARGET)

# Clean up the executable
clean:
	$(RM) $(BIN_DIR)/$(TARGET)  # Make sure this line starts with a tab

# Rebuild the project
rebuild: clean $(BIN_DIR)/$(TARGET)