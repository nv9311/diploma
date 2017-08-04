//
// Created by Nina on 4.8.2017.
//

#include <stdlib.h>
#include "test_coins.h"
#include "common.h"
#include "coins.h"

#define VERBOSE 1

// Example
int goal_example=350;
int coins_example[] = {2, 1, 50, 1, 100, 2, 200, 2, 50, 2, 5, 1, 10, 2};
int coinsLen_example = sizeof(coins_example) / sizeof(int);

void test_coins0_example(){
    result* r = coins0(coins_example, goal_example, coinsLen_example);
    if (VERBOSE) printResult(r);
    free(r);
}

void test_coins1_example(){
    result* r = coins1(coins_example, 0, coinsLen_example-1, goal_example, 0);
    if (VERBOSE) printResult(r);
    free(r);
}

void test_coins2_example(){
    result* r = coins2(coins_example, 0, coinsLen_example-1, goal_example, 0);
    if (VERBOSE) printResult(r);
    free(r);
}


// Real tests
int goal=1001;
int denominations[] = {1, 2, 5, 10, 50, 100, 200};
int n_denominations = sizeof(denominations) / sizeof(int);
int coinsLen = 30000;
int* coins = NULL;

void test_coins_initialize() {
    srand(42);
    coins = generateRandomIntArray(coinsLen, denominations, n_denominations);
}

void test_coins0(){
    result* r = coins0(coins, goal, coinsLen);
    if (VERBOSE) printResult(r);
    free(r);
}

void test_coins1(){
    result* r = coins1(coins, 0, coinsLen-1, goal, 0);
    if (VERBOSE) printResult(r);
    free(r);
}

void test_coins2(){
    result* r = coins2(coins, 0, coinsLen-1, goal, 0);
    if (VERBOSE) printResult(r);
    free(r);
}
