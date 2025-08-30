NAME=DeathRow.out
BUILD_PATH=./build
SERVER_BUILD_PATH=./build/server
SRC_PATH = ./src
SERVER_SRC_PATH = ./src/server_backend
CC=gcc
CFLAGS=-Wall -lSDL2 -lSDL2_image
CSERVERFLAGS=-Wall -lpthread -lm

all:
	if [ ! -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi
	$(CC) -o $(BUILD_PATH)/$(NAME) $(SRC_PATH)/*.c $(CFLAGS)

run:
	$(BUILD_PATH)/$(NAME)

server_build:
	if [ ! -d "$(SERVER_BUILD_PATH)" ]; then mkdir $(SERVER_BUILD_PATH); fi
	$(CC) -o $(SERVER_BUILD_PATH)/server $(SERVER_SRC_PATH)/*.c $(CSERVERFLAGS)

server_run:
	$(SERVER_BUILD_PATH)/server

clean:
	rm -rf $(BUILD_PATH)
