
#include <stdlib.h>
#include <mem.h>
#include <stdio.h>
#include "common.h"
#include "kruskal.h"


// LINKED-LIST FUNCTIONS
void printLinkedListInt(const linkedListInt* linkedListFirst){
    printf("List of coins: ");
    while (linkedListFirst != NULL){
        printf("%d ", linkedListFirst->value);
        linkedListFirst = linkedListFirst->next;
    }
    printf("\n");
}

void appendNode(linkedListInt** linkedListFirst, linkedListInt** linkedListLast, int value){
    linkedListInt* newNode = (linkedListInt*)malloc(sizeof(linkedListInt));
    newNode->value = value;
    newNode->next = NULL;
    if (*linkedListLast != NULL) {
        (*linkedListLast)->next = newNode;
    }
    *linkedListLast = newNode;
    if (*linkedListFirst == NULL) {
        *linkedListFirst = newNode;
    }
}

void freeLinkedListInt(linkedListInt* linkedListFirst){
    while(linkedListFirst != NULL) {
        linkedListInt* next = linkedListFirst->next;
        free(linkedListFirst);
        linkedListFirst = next;
    }
}


// ARRAY FUNCTIONS

void printIntArray(const int* array, int arrayLen){
    printf("Array: ");
    for (int i = 0; i < arrayLen; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* cloneIntArray(const int* array, int arrayLen){
    int* newArray = (int*)malloc(arrayLen * sizeof(int));
    memcpy(newArray, array, arrayLen * sizeof(int));
    return newArray;
}

int* generateRandomIntArray(int n, const int* denominations, int n_denominations){
    int* array = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        array[i] = denominations[(rand() % n_denominations)];
    }
    return array;
}

void insertInt(int** array, int* arrayLen, int newInt) {
    (*arrayLen)++;
    *array = (int*)realloc(*array, (*arrayLen) * sizeof(int));
    (*array)[(*arrayLen)-1] = newInt;
}

// array1 will contain all elements of array1 and array2
// array2 will be freed
void concatIntArray(int **array1, int *array1len, int *array2, int array2len){
    int originalArray1Len = *array1len;
    *array1len += array2len;
    *array1 = (int*)realloc(*array1, *array1len * sizeof(int));
    memcpy(*array1 + originalArray1Len, array2, array2len * sizeof(int));
    free(array2);
}

//DISJOINT SET FUNCTIONS

node makeSet(int x){
    node n;
    n.parent = x;
    n.rank = 0;
    return n;
}

int findSet(int x , node *  forest){
    int newParent = forest[x].parent;
    if(x != newParent){
        newParent = findSet(newParent , forest);
    }
    return newParent;
}
void link(int x , int y , node * forest){
    int rankX = forest[x].rank;
    int rankY = forest[y].rank;
    if(rankX > rankY){
        forest[y].parent = x;
    }
    else{
        forest[x].parent = y;
        if( rankX == rankY ){
            forest[y].rank = rankY + 1;
        }
    }
}

void unionNodes(int x , int y , node * forest){
    link(findSet( x , forest ) , findSet( y , forest) , forest);
}


// QUICKSORT

void swap(int* array, const int l, const int r){
    int tmp=array[l];
    array[l]=array[r];
    array[r]=tmp;
}

int quicksort(int* array, int left, int right){
    if(right<=left) return 1;
    calls++;
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

