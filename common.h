
#ifndef CLION_COMMON_H
#define CLION_COMMON_H


typedef struct linkedListInt{
    int value;
    struct linkedListInt* next;
} linkedListInt;


typedef struct Node{
    int parent;
    int rank;
}node;

int calls;


// LINKED-LIST FUNCTIONS
void printLinkedListInt(const linkedListInt* linkedListFirst);
void appendNode(linkedListInt** linkedListFirst, linkedListInt** linkedListLast, int value);
void freeLinkedListInt(linkedListInt* linkedListFirst);


// ARRAY FUNCTIONS

void printIntArray(const int* array, int arrayLen);
int* cloneIntArray(const int* array, int arrayLen);
int* generateRandomIntArray(int n, const int* denominations, int n_denominations);
void insertInt(int** array, int* arrayLen, int newInt);

// array1 will contain all elements of array1 and array2
// array2 will be freed
void concatIntArray(int **array1, int *array1len, int *array2, int array2len);


// DISJOINT SET  FUNCTIONS

node makeSet(int x);
int findSet(int x , node *  forest);
void link(int x , int y , node * forest);
void unionNodes(int x , int y , node * forest);


// QUICKSORT
void swap(int* array, int l, int r);
int quicksort(int* array, int left, int right);


#endif //CLION_COMMON_H
