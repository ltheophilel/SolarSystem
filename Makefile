# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lm

# make DYNAMICS=1
ifeq ($(DYNAMICS),1)
    CFLAGS += -DDYNAMICS
endif

ifeq ($(ONSCALE),1)
    CFLAGS += -DONSCALE
endif

# Source and object files
SRC_DIR = src
OBJ_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Final binary name
TARGET = solarsystem

# Default target
all: $(TARGET)

# Link objects to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile .c to .o into build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build/ dir if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Optional: run the program
run: all
	./$(TARGET)

.PHONY: all clean run