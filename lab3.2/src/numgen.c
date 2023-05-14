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
    return r % 2097151;
}


int main(){
    srand(wtime(NULL));
    FILE* unc = fopen("points.txt", "w");
    uint32_t num;
    num = generate_number();
    fprintf(unc, "%" PRIx32, num);
    for (int i = 1; i < SIZE; i++){
        num = generate_number();
        fprintf(unc,"\n" "%" PRIx32, num);
    }

    fclose(unc);

    return 0;
}