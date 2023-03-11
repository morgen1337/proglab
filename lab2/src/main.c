#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

struct IntVector
{
    int *data;
    size_t size;
    size_t capacity;
};

struct IntVector *int_vector_new(size_t N)
{
    if (N == 0) return NULL;
    struct IntVector *a1 = malloc(sizeof(struct IntVector));
        if ( !a1 ){
            free(a1);
            return NULL;
        }
    a1->size = 0;
    a1->capacity = N;
    if (!(a1->data = malloc(sizeof(int) * N)))
    {
        free(a1);
        return NULL;
    }
    else
        return a1;
        }





int main()
{
    struct IntVector *a1;
    
    a1 = int_vector_new(10);
    printf("%d",a1->capacity);
    _CrtDumpMemoryLeaks();
    return 0;
}