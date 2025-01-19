# Variables 
# To activate DEBUG set in CFLAGS the flag -DDEBUG_MODE=1 (default is -DDEBUG_MODE=0)
CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g -DDEBUG_MODE=0
ARFLAGS = rcs

# Target for static library
TARGET_LIB = build/libqueue.a
OBJS = build/queue.o

# Default rule to build the static library
$(TARGET_LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(TARGET_LIB) $(OBJS)
	@echo "Static library created at $(TARGET_LIB)"

# Compile queue.c into queue.o
build/queue.o: src/queue.c include/queue.h
	$(CC) $(CFLAGS) -Iinclude -c src/queue.c -o build/queue.o

# Clean rule to remove object files and the static library
clean:
	rm -f build/*.o $(TARGET_LIB)

# Phony targets
.PHONY: clean