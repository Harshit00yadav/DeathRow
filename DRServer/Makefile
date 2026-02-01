NAME = DRServer.out
BUILD_PATH = build

SRC_PATH = src
SRC = $(foreach D,$(SRC_PATH),$(wildcard $(D)/*.c))

OBJECTS = $(patsubst %.c,$(BUILD_PATH)/%.o,$(SRC))
DEPFILES = $(OBJECTS:.o=.d)

SERVER_SRC_PATH = ./src/server_backend
CC = gcc
OPT = -O0
DEPFLAGS = -MP -MMD
CFLAGS = -Wall -lpthread -lm

all: $(NAME)


$(NAME): $(OBJECTS)
	$(CC) $^ -o $(BUILD_PATH)/$@ $(CFLAGS)
	@echo "Build Completed"

$(BUILD_PATH)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling source to object files"
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "cleaning build..."
	rm -rf $(BUILD_PATH)
