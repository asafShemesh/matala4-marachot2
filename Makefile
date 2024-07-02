# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -fPIC -g

# Qt includes and libraries
QT_INCLUDES = $(shell pkg-config --cflags Qt5Widgets)
QT_LIBS = $(shell pkg-config --libs Qt5Widgets)

# Target executables
TARGET = tree
COMPLEX_TARGET = complex
TEST_TARGET = test

# Source files
SRCS = main.cpp



# Object files
OBJS = $(SRCS:.cpp=.o)



# Header files
HDRS = Node.hpp Tree.hpp

# Default target
all: $(TARGET) 

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(QT_LIBS)

# Link the complex executable
$(COMPLEX_TARGET): $(COMPLEX_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(QT_LIBS)

# Link the test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(QT_LIBS)

# Compile source files to object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) $(QT_INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(COMPLEX_OBJS) $(TEST_OBJS) $(TARGET) $(COMPLEX_TARGET) $(TEST_TARGET)

# Phony targets
.PHONY: all clean