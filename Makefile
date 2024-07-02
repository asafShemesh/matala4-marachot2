# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Targets
TARGET = tree

# Source files
SRCS = main.cpp 

# Object files
OBJS = $(SRCS:.cpp=.o)

# Dependencies
DEPS = node.hpp tree.hpp

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	./$(TARGET)

# Compile source files
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean tree