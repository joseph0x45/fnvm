# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c11 -Werror -pedantic
SRC_DIR = src
OBJ_DIR = build
BIN = fnvm.out
LIBS = -lcurl

# Find all .c files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Replace .c with .o and put in OBJ_DIR
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(BIN)

# Build binary
$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

# Compile .c files to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Optional: run the binary
run: $(BIN)
	./$(BIN)

.PHONY: all clean run

