# Variables
# To activate DEBUG set in CFLAGS the flag -DDEBUG_MODE=1 (default is -DDEBUG_MODE=0)
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g -DDEBUG_MODE=0
TARGET = main
LIB_PATH = ../build/libqueue.a
INCLUDE_PATH = ../include
SRC = main.c
OBJS = main.o

# Default rule to build the example using the static library
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIB_PATH) -o $(TARGET)

# Compile main.c into main.o
main.o: main.c
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c main.c -o main.o

# Run the example
run: $(TARGET)
	./$(TARGET)

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: clean run
