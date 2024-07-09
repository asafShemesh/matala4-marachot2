CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -fPIC `pkg-config --cflags Qt5Widgets`
LDFLAGS = `pkg-config --libs Qt5Widgets`

MAIN_TARGET = tree
TEST_TARGET = test

MAIN_SRCS = main.cpp
TEST_SRCS = test.cpp

MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

HEADERS = complex.hpp tree.hpp node.hpp

all: $(MAIN_TARGET) $(TEST_TARGET)

$(MAIN_TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all clean
