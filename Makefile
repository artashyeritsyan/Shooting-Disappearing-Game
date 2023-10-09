# Makefile for Shooting_Disappearing

# Compiler and flags
CXX = g++
CXXFLAGS = -g

# Libraries
LIBS = -lncurses

# Source file and output executable
SRC = Shooting_Disappearing.cpp
OUTPUT = /home/artash/MyRepo/Shooting-Disappearing-Game/output/Shooting_Disappearing

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC) $(LIBS)

clean:
	rm -f $(OUTPUT)
