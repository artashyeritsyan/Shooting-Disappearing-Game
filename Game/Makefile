# Makefile for your project

CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lncurses

SRCS = main.cpp cube.cpp board.cpp game.cpp screen.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = cube.hpp board.hpp game.hpp screen.hpp

TARGET = my_game

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
