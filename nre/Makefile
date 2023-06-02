CC = gcc
TARGET = nre

.PHONY: all build clean

all: build

build: $(TARGET)

$(TARGET): main.c
	$(CC) -o $@ $<

clean:
	rm -f $(TARGET)