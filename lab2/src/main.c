#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct IntVector
{
    int *data;
    size_t size;
    size_t capacity;
};

void prmas(struct IntVector *v){
    for (int i = 0; i< v->size;i++){
        printf(" %d", v->data[i]);
    }
    printf("\n");
}

struct IntVector *int_vector_new(size_t initial_capacity)
{
    if (initial_capacity == 0) return NULL;
    struct IntVector *a1 = malloc(sizeof(struct IntVector));
        if ( !a1 ){
            printf("Not enough space for struct");
            free(a1);
            return NULL;
        }
    a1->size = 0;
    a1->capacity = initial_capacity;
    if (!(a1->data = malloc(sizeof(int) * initial_capacity)))
    {
        printf("Not enough space for massive");
        free(a1->data);
        free(a1);
        return NULL;
    }
        return a1;
        }


struct IntVector *int_vector_copy(struct IntVector *v){
    struct IntVector *copy = malloc(sizeof(struct IntVector));
    if ((!copy) || (v->capacity == 0)){
        free(copy);
        return NULL;
    }
    copy->size = v->size;
    copy->capacity = v->capacity;
    if (!(copy->data = malloc(copy->capacity * sizeof(int)))){
        free(copy->data);
        free(copy);
        return NULL;
    };
    for (int i = 0; i < v->capacity; i++){
        copy->data[i] = v->data[i];
    }
    return copy;
}

void int_vector_free(struct IntVector *v){
    free(v->data);
    free(v);
}

int int_vector_get_item(const struct IntVector *v, size_t index){
    return v->data[index];
}

void int_vector_set_item(struct IntVector *v, size_t index, int item){
    if (index < v->size)
    v->data[index] = item;
}

size_t int_vector_get_size(const struct IntVector *v){
    return v->size;
}

size_t int_vector_get_capacity(const struct IntVector *v){
    return v->capacity;
}

int int_vector_push_back(struct IntVector *v, int item){
    if (v->capacity > v->size) {
        v->data[v->size] = item;
        v->size++;
        return 0;
    }
    else {
        v->capacity = v->capacity * 2;
        v->data = realloc(v->data, v->capacity * sizeof(int));
        v->data[v->size] = item;
        v->size++;
        return 0;
    }
    if (errno) return -1;

}

void int_vector_pop_back(struct IntVector *v){
    if (v->size  == 0) {}
    else {
        v->size--;
    }
}

int int_vector_shrink_to_fit(struct IntVector *v){
    if (v->capacity == v->size) {
        return 0;
    }
    else
    {
        v->capacity = v->size;
        v->data = realloc(v->data, v->capacity * sizeof(int));
        return 0;
    }
    if (errno) return -1;
}

int int_vector_resize(struct IntVector *v, size_t new_size){
    if (new_size >= v->size){
        if (v->capacity < new_size){
            v->capacity = new_size;
            v->data = realloc(v->data, v->capacity * sizeof(int));
            }
        for (int i = new_size - (new_size - v->size); i < new_size; i++){
            v->data[i] = 0;
        }
        v->size = new_size;
        return 0;
    }
    else {
        v->size = new_size;
        int_vector_shrink_to_fit(v);
        return 0;
}
if (errno) return -1;
}

int int_vector_reserve(struct IntVector *v, size_t new_capacity){
    if (new_capacity > v->capacity){
        v->capacity = new_capacity;
        v->data = realloc(v->data, v->capacity * sizeof(int));
        return 0;
    }
    else return 0;
    if (errno) return -1;
}


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