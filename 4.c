#include <stdio.h>
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void bubble_sort(int* array, int size)
{
    int i, j;
    for (i = 0; i < size - 1; ++i) {
    for (j = 1; j < size - i; ++j) {
    if (array[j-1] > array[j]) {
    swap(&array[j-1], &array[j]);
}
}
}
}
int main()
{
    int array[100] = {10, 15, 5, 4, 21, 7};
    bubble_sort(array, 6);
    int i;
    for (i = 0; i < 6 ; ++i) {
    printf("%d ", array[i]);
}
    printf("\n");
}