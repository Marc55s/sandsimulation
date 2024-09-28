# Compiler
CC = gcc

# Raylib directory (adjust to your Raylib path if it's not in a standard location)
RAYLIB_PATH = /usr/local/lib

# Compiler flags
CFLAGS = -Wall -std=c99 -I$(RAYLIB_PATH)/include
LDFLAGS = -L$(RAYLIB_PATH) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# Source files
SRC = main.c mouse.c util.c particle.c

# Output executable
OUT = game

# Build the executable
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean up generated files
clean:
	rm -f $(OUT)
