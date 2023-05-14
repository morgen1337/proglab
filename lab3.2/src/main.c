#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "command.h"




int main(int argc, char *argv[]){
    if (argv[1] == NULL){
        printf("expected DECODE or ENCODE\n");
        return -1;
    }
    if (strcmp(argv[1], "encode") == 0){
        printf("encode\n");
        encode_file(argv[2],argv[3]);
    }
    else if (strcmp(argv[1], "decode") == 0){
        printf("decode\n");
        decode_file(argv[2],argv[3]);
    }

    return 0;
}