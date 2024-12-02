#include <stdio.h>
#include <stdlib.h>

#include "lib/parseLib3.h"
#include "lib/shellSort.h"


int greaterThen(void *a, void *b) {
    double n1 = *(double *)a;
    double n2 = *(double *)b;
    if(n2 <= 0 || n1 <= 0) return 0;
    return (n2 - n1) > 0 ? -1 : 0;
}

void main() {
    double *array = NULL;
    size_t count = 0;
    double a = 1;
    double b = 2;
    readMultDoubleWithDialog(&array, ',', "Please enter numbers separated by commas (1, 3, 4.4, ...)", &count);
    shellSortSteped(array, count, sizeof(double), 2, greaterThen);
    puts("Result:");
    for (size_t i = 0; i < count; i++) {
        printf("%.2lf, ", array[i]);
    }
    printf("\n");
}
