//
// Created by Nina on 4.8.2017.
//

#include "test_coins.h"
#include "coins.h"

int goal=350;
int coins[14] = {2, 1, 50, 1, 100, 2, 200, 2, 50, 2, 5, 1, 10, 2};

void test_coins0(){
    result* r= coins0(coins, goal, 14);
    printResult(r);
}

void test_coins1(){
    result* r= coins1(coins, 0, 13, goal, 0);
    printResult(r);
}

void test_coins2(){
    result* r= coins2(coins, 0, 13, goal, 0);
    printResult(r);
}