//
// Created by Nina on 3.8.2017.
//

#include "common.h"

#ifndef CLION_COINS_H
#define CLION_COINS_H


typedef struct result{
    linkedListInt* solutionFirst;
    linkedListInt* solutionLast;
    int solutionlength;
    int goal;
    int calls;
} result;

void printResult(result* r);
void freeResult(result* r);

result* coins0(int *coins, int goal, int coinslen);
result* coins1(int *coins, int left, int right, int goal, int solutionLen);
result* coins2(int *coins, int left, int right, int goal, int solutionLen);


#endif //CLION_COINS_H
