CC = g++
CFLAGS = -std=c++11 -Wall
SDL_FLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
EXEC = $(BIN_DIR)/3partitiontetris

all: $(EXEC)

$(EXEC): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(SDL_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE_DIR) $(SDL_FLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

