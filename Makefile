CC = gcc
CFLAGS = `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`
SRC = src/main.c
TARGET = track-plotter

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
