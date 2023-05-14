#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>
#include <inttypes.h>
#include "SIZE.h"

double wtime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}


int main(){
    srand(wtime(NULL));
    FILE* unc = fopen("uncompressed.dat", "wb");
    uint32_t num;
    for (int i = 0; i < SIZE; i++){
        num = generate_number();
        fwrite(&num, 4, 1, unc);
    }

    fclose(unc);

    return 0;
}