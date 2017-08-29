
#include <stdlib.h>
#include "fractional_knapsack.h"
#include "test_fractional_knapsack.h"

#define VERBOSE 1


int W_example = 50;
const item items_example[] ={{60 , 10} , {100 , 20} , {120 , 30}};
const int numItems_example = sizeof(items_example) / sizeof(item);

void test_fractional_knapsack_example(){
    item* items_copy = cloneItems(items_example , numItems_example);
    resultKnapsack* r = fractionalKnapsack(items_copy , W_example , numItems_example);
    if (VERBOSE) printResultKnapsack(r);
    freeResultKnapsack(r);
    free(items_copy);
}

void test_fractional_knapsack_hybrid_example(){
    item* items_copy = cloneItems(items_example , numItems_example);
    resultKnapsack* r = fractionalKnapsackHybrid(items_copy , 0 , numItems_example - 1 , W_example , 0.0);
    if (VERBOSE) printResultKnapsack(r);
    freeResultKnapsack(r);
    free(items_copy);
}



//REAL TESTS

int maxValue = 100;
int maxWeight = 50;
int numItems = 10;
int W = 100;

/*
int maxValue = 500;
int maxWeight = 250;
int numItems = 1000;
int W = 8000;
*/
item* items = NULL;

void test_fractional_knapsack_initialize(){
    srand(42);
    //srand(time(NULL));
    items = generateRandomItemsArray(numItems , maxValue , maxWeight);
}
void test_fractional_knapsack(){
    item* items_copy = cloneItems(items , numItems);
    resultKnapsack* r = fractionalKnapsack(items_copy , W , numItems);
    if (VERBOSE) printResultKnapsack(r);
    freeResultKnapsack(r);
    free(items_copy);
}

void test_fractional_knapsack_hybrid(){
    item* items_copy = cloneItems(items , numItems);
    resultKnapsack* r = fractionalKnapsackHybrid(items_copy , 0 , numItems - 1 , W , 0.0);
    if (VERBOSE) printResultKnapsack(r);
    freeResultKnapsack(r);
    free(items_copy);
}