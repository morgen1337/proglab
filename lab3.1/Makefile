all: gen main decode
	./gen
	./main

gen: numgen.c SIZE.h
	gcc -Wall -g3 -O0 numgen.c -o gen

main: main.c SIZE.h
	gcc -Wall -g3 -O0 main.c -o main

decode: decode.c SIZE.h
	gcc -Wall -g3 -O0 decode.c -o decode

clear: 
	rm decode gen encode