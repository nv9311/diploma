//
// Created by Nina on 3.8.2017.
//

#ifndef CLION_COINS_H
#define CLION_COINS_H

#endif //CLION_COINS_H

typedef struct result{
    int* solution;
    int solutionlength;
    int goal;
    int calls;
} result;

void constructResult(result*r, int*solution, int goal, int sollength);
result* consider(int*solution,int goal, int coin, int solutionlength);
void insertResults(result* left, const result* right);
void printResult(result* r);

result* coins0(int *coins, int goal, int coinslen);
result* coins1(int *coins, int left, int right, int goal, int solutionlength);
result* coins2(int *coins, int left, int right, int goal, int sollength);
