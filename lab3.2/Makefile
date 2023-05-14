src/coder: src/main.c src/command.c src/coder.c
	gcc -c src/command.c
	gcc -c src/coder.c
	gcc -c src/main.c
	gcc main.o coder.o command.o -o src/coder
	rm main.o coder.o command.o

encode: src/coder
	./src/coder encode points.txt units.bin

decode: src/coder
	./src/coder decode units.bin points.txt

gen: src/numgen.c src/SIZE.h
	gcc src/numgen.c -o gen