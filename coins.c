
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "coins.h"

result* constructResult(linkedListInt* solutionFirst, linkedListInt* solutionLast, int goal){
    result* r = (result*)malloc(sizeof(result));
    r->solutionFirst = solutionFirst;
    r->solutionLast = solutionLast;
    r->goal = goal;
    r->calls = 1;
    return r;
}

void consider(result* r, int coin) {
    if (coin > r->goal) return;
    appendNode(&r->solutionFirst, &r->solutionLast, coin);
    r->goal -= coin;
}

// left will contain left and right
// right will be freed
void mergeResults(result* left, result* right) {
    if (right->solutionFirst == NULL) {
        assert(right->solutionLast == NULL);
        free(right);
        return;
    }
    if (left->solutionFirst == NULL) {
        assert(left->solutionLast == NULL);
        left->solutionFirst = right->solutionFirst;
    }
    else {
        assert(left->solutionLast != NULL);
        left->solutionLast->next = right->solutionFirst;
    }
    left->solutionLast = right->solutionLast;
    left->calls = right->calls + left->calls;
    left->goal = right->goal;
    free(right);
}

void printResult(result* r){
    printf("Result:\n");
    printf("Number of Calls: %d \n" , r->calls);
    printf("Goal: %d \n" , r->goal);
    printLinkedListInt(r->solutionFirst);
}

void freeResult(result* r){
    freeLinkedListInt(r->solutionFirst);
    free(r);
}

result* coins0(int* coins, int goal, int coinslen){
    int calls = quicksort(coins, 0, coinslen-1);
    linkedListInt* solutionFirst = NULL;
    linkedListInt* solutionLast = NULL;
    for(int i=0; i<coinslen; i++){
        if(coins[i] > goal) continue;
        goal -= coins[i];
        appendNode(&solutionFirst, &solutionLast, coins[i]);
    }
    result* res = constructResult(solutionFirst, solutionLast, goal);
    res->calls = calls;
    return res;
}

result* coins1(int* coins, int left, int right, int goal, int solutionLen){
    //solutionLen lahko stran dam ker ga nikjer ne rabim, rabila sem prej pri array
    if(right<left){
        return constructResult(NULL, NULL, goal);
    }
    int p = coins[left];
    if(right==left){
        result* r = constructResult(NULL, NULL, goal);
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

result* coins2(int* coins, int left, int right, int goal, int solutionLen){
    if(right<left){
        return constructResult(NULL, NULL, goal);
    }
    int p = coins[left];
    if(right==left){
        result* r = constructResult(NULL, NULL, goal);
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
