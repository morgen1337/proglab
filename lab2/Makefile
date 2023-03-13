main: src/main.o src/IntVector.o src/IntVector.h
		gcc -Wall src/main.o src/IntVector.o -g3 -O0 -o main

main.o: src/main.c src/IntVector.h
		gcc -c -g3 -O0 src/main.c

IntVector.o: src/IntVector.c src/IntVector.h
		gcc -c -g3 -O0 src/IntVector.c
