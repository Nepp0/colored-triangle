# Makefile
CC = g++
CFLAGS = $(shell pkg-config --cflags glfw3 glew)
LDFLAGS = $(shell pkg-config --libs glfw3 glew) -lGL
TARGET = main

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
