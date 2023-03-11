#include <stdio.h>

IntVector *int_vector_new(size_t N){
    struct IntVector a1;
    a1.data = NULL;
    a1.size = 0;
    a1.capacity = N;
    if !(mas = malloc(sizeof(int)* N)) return NULL;
    else return *a1;
}