#include <stdio.h>

#include "lib/parseLib3.h"
#include "lib/shellSort.h"
#include <float.h>





void printArray(double** inputArray, unsigned rowCount, unsigned columnCount) {
    for (size_t i = 0; i < rowCount; i++) {
        printf("| ");
        for (size_t j = 0; j < columnCount; j++) {
            printf("%.1lf, ", inputArray[i][j]);
            if (inputArray[i][j] == 0) break;
        }
        printf("|\n");
    }
}

int condition(void *a, void *b, void * length){
    double* arr1 = *(double**)a;
    double* arr2 = *(double**)b;
    double arr1Min = DBL_MAX;
    double arr2Min = DBL_MAX;
    long len = *(long*)length;
    for (long i = 0; i < len; i++){
        if (arr1[i] < arr1Min) arr1Min = arr1[i];
        if (arr2[i] < arr2Min) arr2Min = arr2[i];
    }
    return (arr2Min - arr1Min) < 0 ? -1 : 0;

}

void main(){
    long seed = 0;
    long rowCount = 0;
    long columnCount = 0;
    double** inputArray = NULL;
    char tmpStr[100] = {0};
    int byHandFlag = 0;
    do {
        if (readLongWithDialog(&rowCount, "Please enter row count of the matrix (positive number < LONG_MAX)")) handleMallocError();
        if (rowCount <= 0) puts("Row count should be greater then 0. Please try again.");
    } while (rowCount <= 0);
    do {
        if (readLongWithDialog(&columnCount, "Please enter column count of the matrix (positive number < LONG_MAX)")) handleMallocError();
        if (columnCount <= 0) puts("Column count should be greater then 0. Please try again.");
    } while (columnCount <= 0);

    if ((inputArray = calloc(rowCount, sizeof(double*))) == NULL) handleMallocError();

    readYNWithDialog("Fill by-hand? (Y/N):", &byHandFlag);

    byHandFlag ? fill2DArrayByHand(inputArray, rowCount, columnCount, NULL) : fill2DArrayWithRandom(inputArray, rowCount, columnCount, -100, 100);

    puts("Input:");
    printArray(inputArray, rowCount, columnCount);

    insSortPassThrought(inputArray, rowCount, sizeof(double), condition, &columnCount);


    puts("Result:");
    printArray(inputArray, rowCount, columnCount);

    for (size_t i = 0; i < columnCount; i++){
        free(inputArray[i]);
    }
    free(inputArray);
}