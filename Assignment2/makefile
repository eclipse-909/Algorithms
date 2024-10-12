# Variables
CXX = g++
CXXFLAGS = -std=c++20
SRCS = main.cpp
TARGET = Assignment2
BIN_DIR = .

# Default rule to build the program
all: $(BIN_DIR)/$(TARGET)

# Rule to compile and create the executable in the bin directory
$(BIN_DIR)/$(TARGET): $(SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(BIN_DIR)/$(TARGET)

# Clean up the executable
clean:
	$(RM) $(BIN_DIR)/$(TARGET)  # Make sure this line starts with a tab

# Rebuild the project
rebuild: clean $(BIN_DIR)/$(TARGET)