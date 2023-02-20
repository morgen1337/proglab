#include <stdio.h>
#include <stdlib.h>
int* init(int n)
{
    int* arr = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; ++i) {
        arr[i] = i;
    }
    return arr;
}

int main()
{
    int n = 10;
    int* arr = init(n);
    int i;
    for (i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    return 0;
}
