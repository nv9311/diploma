//
// Created by Nina on 3.8.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "coins.h"
#include "common.h"

result* constructResult(int*solution, int goal, int sollength){
    result* r = (result*)malloc(sizeof(result));
    r->solution = solution;
    r->solutionlength = sollength;
    r->goal = goal;
    r->calls = 1;
    return r;
}

void consider(result* r, int coin) {
    if (coin > r->goal) return;
    insertInt(&(r->solution), &(r->solutionlength), coin);
    r->goal -= coin;
}

// left will contain left and right
// right will be freed
void mergeResults(result *left, result *right) {
    concatIntArray(&left->solution, &left->solutionlength, right->solution, right->solutionlength);
    left->calls = right->calls + left->calls;
    left->goal=right->goal;
    free(right);
}

void printResult(result* r){
    printf("Result: %d %d %d\n", r->goal, r->calls, r->solutionlength);
    for(int i=0; i < r->solutionlength; i++){
        printf("%d ", r->solution[i]);
    }
    printf("\n");
}

void freeResult(result* r){
    free(r->solution);
    free(r);
}

result* coins0(int *coins, int goal, int coinslen){
    int calls = quicksort(coins, 0, coinslen-1);
    int* solution = NULL;
    int sollength = 0;
    for(int i=0; i<coinslen; i++){
        if(coins[i] > goal) continue;
        goal -= coins[i];
        sollength++;
        solution = (int*)realloc(solution, sollength * sizeof(int));
        solution[sollength-1] = coins[i];
    }
    result* res = constructResult(solution,goal,sollength);
    res->calls=calls;
    return res;
}

result* coins1(int *coins, int left, int right, int goal, int solutionLen){
    if(right<left){
        return constructResult(NULL,goal,0);
    }
    int p = coins[left];
    if(right==left){
        result* r = constructResult(NULL, goal, 0);
        consider(r, p);
        return r;
    }
    calls++;
    int l=left;
    int r=right;
    while(l<=r){
        while(coins[l]>p)l+=1;
        while(coins[r]<p)r-=1;
        if(l>r)break;
        swap(coins,l,r);
        l+=1;
        r-=1;
    }
    result* leftsol = coins1(coins, left, r, goal, solutionLen);
    if(l-r==2){
        consider(leftsol, p);
    }
    result* rightsol = coins1(coins, l, right, leftsol->goal, solutionLen);

    mergeResults(leftsol, rightsol);
    return leftsol;
}

result* coins2(int *coins, int left, int right, int goal, int solutionLen){
    if(right<left){
        return constructResult(NULL,goal,0);
    }
    int p = coins[left];
    if(right==left){
        result* r = constructResult(NULL, goal, 0);
        consider(r, p);
        return r;
    }
    calls++;
    int l=left;
    int r=right;
    while(l<=r){
        while(coins[l]>p)l+=1;
        while(coins[r]<p)r-=1;
        if(l>r)break;
        swap(coins,l,r);
        l+=1;
        r-=1;
    }
    result* leftsol = coins2(coins, left, r, goal, solutionLen);
    if(l-r==2){
        consider(leftsol, p);
    }
    if(leftsol->goal <= 0) return leftsol;
    result* rightsol = coins2(coins, l, right, leftsol->goal, solutionLen);
    mergeResults(leftsol, rightsol);
    return leftsol;
}
