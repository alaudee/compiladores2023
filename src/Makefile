CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

TARGET = main
TARGET_DEBUG = main-debug

.PHONY: all clean build run

all: build

build: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

$(TARGET_DEBUG): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o $(TARGET_DEBUG)

clean:
	rm -f $(TARGET) $(TARGET_DEBUG)

run: $(TARGET)
	./$(TARGET) teste.txt