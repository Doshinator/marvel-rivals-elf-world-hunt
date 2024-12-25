# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files
SRCS = main.cpp

# Output executable
TARGET = main

# Default rule
all: $(TARGET)

# Linking and building the target executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean rule to remove the built files
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
