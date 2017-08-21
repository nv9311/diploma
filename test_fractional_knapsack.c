//
// Created by Nina on 21.8.2017.
//

#include <stdlib.h>
#include "fractional_knapsack.h"
#include "test_fractional_knapsack.h"

#define VERBOSE 1

int numItems = 3;
int W = 50;

item items[3] ={{60 , 10} , {100 , 20},{120 , 30}};
//item* items = NULL;

void test_fractional_knapsack_initialize(){
//to do for bigger inputs
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
    resultKnapsack* r = fractionalKnapsackHybrid(items , 0 , numItems - 1 , W , 0.0);
    if (VERBOSE) printResultKnapsack(r);
    freeResultKnapsack(r);
    free(items_copy);
}