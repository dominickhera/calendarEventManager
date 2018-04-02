cc = gcc
FILE = src/
CFLAGS += -std=c11 -Wall -g -pedantic
EXE = run
LIBS = -L/usr/local/lib -lm -lliblist -llibcparse

all: $(EXE)

$(EXE): BIN OBJ CalendarParser.o LinkedListAPI.o listLib parseLib

BIN:
	if [ ! -d "bin" ]; then mkdir bin; fi;

OBJ:
	if [ ! -d "obj" ]; then mkdir obj; fi;

parseLib: 
	$(CC) $(CFLAGS) -shared -o ./bin/parseLib.so -fPIC ./obj/CalendarParser.o ./obj/LinkedListAPI.o

listLib: 
	$(CC) $(CFLAGS) -shared -o ./bin/listLib.so -fPIC ./obj/LinkedListAPI.o

CalendarParser.o: ./src/CalendarParser.c
	$(CC) -c $(CFLAGS) -fPIC ./src/CalendarParser.c -I./include -o ./obj/CalendarParser.o

LinkedListAPI.o: ./src/LinkedListAPI.c
	$(CC) -c $(CFLAGS) -fPIC ./src/LinkedListAPI.c -I./include -o ./obj/LinkedListAPI.o

clean:
	rm -rf bin obj
