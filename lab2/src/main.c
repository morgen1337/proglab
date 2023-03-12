#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "IntVector.h"

struct IntVector
{
    int *data;
    size_t size;
    size_t capacity;
};


int main()
{
    struct IntVector *a1;
    struct IntVector *a2;
    a1 = int_vector_new(87);
    a2 = int_vector_copy(a1);

    int_vector_push_back(a2,224);
    int_vector_push_back(a2,222);
    int_vector_push_back(a2,1);
    int_vector_push_back(a2,8);
    printf("new and copy   capacity - %zu size - %zu", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);


    int_vector_shrink_to_fit(a2);
    printf("shrink to fit  capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    int_vector_pop_back(a2);
    printf("pop back       capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    int_vector_reserve(a2, 12);
    printf("reserve        capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    int_vector_resize(a2, 2);
    printf("resize         capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    int_vector_resize(a2, 7);
    printf("resize         capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    int_vector_push_back(a2, 1337);
    printf("pushback       capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    int_vector_pop_back(a2);
    printf("pop back       capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    int_vector_shrink_to_fit(a2);
    printf("shrink to fit  capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);

    a1 = int_vector_copy(a2);
    printf("copy      a1 - capacity - %zu size - %zu ", int_vector_get_capacity(a1), int_vector_get_size(a1));
    prmas(a1);

    int_vector_set_item(a2, 3, 1488);
    printf("set item       capacity - %zu size - %zu ", int_vector_get_capacity(a2), int_vector_get_size(a2));
    prmas(a2);


    int_vector_free(a1);
    int_vector_free(a2);
    return 0;
}