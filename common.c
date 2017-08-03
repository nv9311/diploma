//
// Created by Nina on 3.8.2017.
//

#include <stdlib.h>
#include <mem.h>
#include "common.h"

int* generateRandomIntArray(int n, const int* denominations, int n_denominations){
    int* array = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        array[i] = denominations[(rand() % n_denominations)];
    }
    return array;
}

void insertIntArray(int**array1, int*array1len, const int*array2, const int array2len){
    int originalArray1Len = *array1len;
    *array1len += array2len;
    *array1 = (int*)realloc(*array1, *array1len * sizeof(int));
    memcpy(*array1 + originalArray1Len, array2, array2len * sizeof(int));
}

void swap(int* array, const int l, const int r){
    int tmp=array[l];
    array[l]=array[r];
    array[r]=tmp;
}

int quicksort(int* array, int left, int right){
    if(right<=left) return 1;
    int p=array[left];
    int l=left;
    int r=right;
    while(l<=r){
        while(array[l]>p)l+=1;
        while(array[r]<p)r-=1;
        if(l>r)break;
        swap(array,l,r);
        l+=1;
        r-=1;
    }
    return quicksort(array, left, r) + quicksort(array, l, right);
}
