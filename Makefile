all: main

main.o: main.c
    gcc -c main.c

main: main.o
    gcc main.o -o main

clean:
	rm -f *.o main