# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra `pkg-config --cflags Qt5Widgets` -fPIC
LDFLAGS = `pkg-config --libs Qt5Widgets`

# Targets
TARGET = tree
TEST_TARGET = test

# Source files
SRCS = main.cpp
TEST_SRCS = test.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Header files (for dependency tracking)
HEADERS = complex.hpp tree.hpp node.hpp

# Rules
all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run_test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

.PHONY: all clean run_test
