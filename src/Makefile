CC = cc
CFLAGS = -std=c99 -pedantic -Wall
OBJECTS = main.o core/commands.o core/core.o


all: somgirc

main.c: main.c
	$(CC) $(CFLAGS) -c main.c core/commands.c core/core.c

somgirc: $(OBJECTS)
	$(CC) $(OBJECTS) -o ../build/somgirc -lncurses

clean:
	rm -f *.o ../build/somgirc