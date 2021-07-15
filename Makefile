CC=g++

OBJS=*.cpp

FLAGS=-lSDL2 -lSDL2_image

all: $(OBJS)
		$(CC) $(OBJS) $(FLAGS)
