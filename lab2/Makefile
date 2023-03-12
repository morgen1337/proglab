main: src/main.o src/IntVector.o
		gcc -Wall src/main.o src/IntVector.o -o main
		rm src/IntVector.o src/main.o

main.o: src/main.c src/IntVector.h
		gcc -c src/main.c

main.o: src/IntVector.c src/IntVector.h
		gcc -c src/IntVector.c