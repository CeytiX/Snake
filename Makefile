CC=g++
EXEC=Snake
LIBS=`sdl-config --cflags --libs` -lSDL -lSDLmain -lSDL_image -lSDL_ttf
FLAGS= -std=c++11

all:
	$(CC) src/main.cpp -o $(EXEC) $(LIBS) $(FLAGS)

clean:
	rm $(EXEC)
