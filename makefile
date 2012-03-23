LFLAGS=-lSDL -lSDL_image -lSDL_ttf
DBFLAG=-g
all: main.o dot.o basic.o timer.o player.o
	g++ -o game main.o $(LFLAGS)
main.o: main.cpp basic.h dot.h timer.h
	g++ $(DBFLAG) -c main.cpp
basic.o: basic.h
	g++ $(DBFLAG) -c basic.h
dot.o: dot.h basic.h
	g++ $(DBFLAG) -c dot.h
timer.o: timer.h basic.h
	g++ $(DBFLAG) -c timer.h
player.o: player.h
	g++ $(DBFLAG) -c player.h
