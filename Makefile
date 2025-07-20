NAME=DeathRow
BUILD_PATH=./build
SRC_PATH = ./src
CC=gcc
CFLAGS=-Wall -lSDL2

all:
	if [ ! -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi
	$(CC) -o $(BUILD_PATH)/$(NAME) $(SRC_PATH)/*.c $(CFLAGS)

run:
	$(BUILD_PATH)/$(NAME)

clean:
	rm -rf $(BUILD_PATH)
