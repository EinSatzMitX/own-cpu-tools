SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

CC = clang
CFLAGS = -Wall -Wextra -I$(INC_DIR) -g -O2  
LDFLAGS := 

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
all: $(BIN_DIR)/test

# Rule to create the object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to create the binary directory if it doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the final binary
$(BIN_DIR)/test: $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Clean up generated files
clean:
	@if [ -d "$(OBJ_DIR)" ]; then rm -rf $(OBJ_DIR); fi
	@if [ -d "$(BIN_DIR)" ]; then rm -rf $(BIN_DIR); fi

.PHONY: all clean
