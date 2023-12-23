CC = g++
LDFLAGS = -lncurses

SRC_DIR = src
HDR_DIR = headers
OBJ_DIR = obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
HDR_FILES = $(wildcard $(HDR_DIR)/*.hpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = Shooting_Disappearing

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $< -I$(HDR_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean
