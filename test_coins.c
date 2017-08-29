
#include <stdlib.h>
#include "test_coins.h"
#include "common.h"
#include "coins.h"

#define VERBOSE 1

// Example
int goal_example = 350;
const int coins_example[] = {2, 1, 50, 1, 100, 2, 200, 2, 50, 2, 5, 1, 10, 2};
const int coinsLen_example = sizeof(coins_example) / sizeof(int);

void test_coins0_example(){
    int* coins_copy = cloneIntArray(coins_example, coinsLen_example);
    result* r = coins0(coins_copy, goal_example, coinsLen_example);
    if (VERBOSE) printResult(r);
    freeResult(r);
    free(coins_copy);
}

void test_coins1_example(){
    int* coins_copy = cloneIntArray(coins_example, coinsLen_example);
    result* r = coins1(coins_copy, 0, coinsLen_example-1, goal_example, 0);
    if (VERBOSE) printResult(r);
    freeResult(r);
    free(coins_copy);
}

void test_coins2_example(){
    int* coins_copy = cloneIntArray(coins_example, coinsLen_example);
    result* r = coins2(coins_copy, 0, coinsLen_example-1, goal_example, 0);
    if (VERBOSE) printResult(r);
    freeResult(r);
    free(coins_copy);
}


// REAL TESTS

int goal = 1271;
int denominations[] = {1, 2, 5, 10, 50, 100, 200};
int n_denominations = sizeof(denominations) / sizeof(int);
int coinsLen = 30000;
int* coins = NULL;

void test_coins_initialize() {
    srand(42);
    coins = generateRandomIntArray(coinsLen, denominations, n_denominations);
}

void test_coins0(){
    int* coins_copy = cloneIntArray(coins, coinsLen);
    result* r = coins0(coins_copy, goal, coinsLen);
    if (VERBOSE) printResult(r);
    freeResult(r);
    free(coins_copy);
}

void test_coins1(){
    int* coins_copy = cloneIntArray(coins, coinsLen);
    result* r = coins1(coins_copy, 0, coinsLen-1, goal, 0);
    if (VERBOSE) printResult(r);
    freeResult(r);
    free(coins_copy);
}

void test_coins2(){
    int* coins_copy = cloneIntArray(coins, coinsLen);
    result* r = coins2(coins_copy, 0, coinsLen-1, goal, 0);
    if (VERBOSE) printResult(r);
    freeResult(r);
    free(coins_copy);
}
