CC = g++
CFLAGS = $(shell pkg-config --cflags glfw3 glew)
LDFLAGS = $(shell pkg-config --libs glfw3 glew) -lGL
TARGET = main
SRCS = main.cpp glad.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)
