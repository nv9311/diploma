//
// Created by Nina on 3.8.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "coins.h"
#include "common.h"

void constructResult(result*r, int*solution, int goal, int sollength){
    r->solution=solution;
    r->solutionlength=sollength;
    r->goal=goal;
    r->calls=1;
}

result* consider(int*solution,int goal, int coin, int solutionlength){
    result*r=(result*)malloc(sizeof(result));
    if(coin>goal){
        constructResult(r,solution,goal,solutionlength);
    }
    else{
        solution=(int*)realloc(solution, (solutionlength+1) * sizeof(int));
        solution[solutionlength]=coin;
        constructResult(r,solution,goal-coin,solutionlength+1);
    }
    return r;
}

void insertResults(result* left, const result* right) {
    insertIntArray(&left->solution, &left->solutionlength, right->solution, right->solutionlength);
    left->calls = right->calls + left->calls;
    left->goal=right->goal;
}

result*coins0(int *coins, int goal, int coinslen){
    result*res=(result*) malloc(sizeof(result));
    int calls=quicksort(coins, 0, coinslen-1);
    int*solution=NULL;
    int sollength=0;
    for(int i=0; i<coinslen; i++){
        if(coins[i] > goal) continue;
        goal-=coins[i];
        solution=(int*)realloc(solution,i+1);
        solution[i]=coins[i];
        sollength++;
    }
    constructResult(res,solution,goal,sollength);
    res->calls=calls;
    return res;
}

result* coins1(int *coins, int left, int right, int goal, int solutionlength){
    result*res=(result*)malloc(sizeof(result));
    if(right<left){
        constructResult(res,NULL,goal,0);
        return res;
    }
    int p=coins[left];
    if(right==left) return consider(NULL,goal,p,0);
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
    result*leftsol= coins1(coins, left, r, goal, solutionlength);
    if((l-r)==2){
        int leftcalls=leftsol->calls;
        leftsol=consider(leftsol->solution,leftsol->goal,p,leftsol->solutionlength);
        leftsol->calls=leftcalls;
    }
    result*rightsol= coins1(coins, l, right, leftsol->goal, solutionlength);

    insertResults(leftsol, rightsol);
    return leftsol;
}

result* coins2(int *coins, int left, int right, int goal, int sollength){
    result*res=(result*)malloc(sizeof(result));
    if(right<left){
        constructResult(res,NULL,goal,0);
        return res;
    }
    int p=coins[left];
    if(right==left) return consider(NULL,goal,p,0);
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
    result*leftsol= coins2(coins, left, r, goal, sollength);
    if((l-r)==2){
        int leftcalls=leftsol->calls;
        leftsol=consider(leftsol->solution,leftsol->goal,p,leftsol->solutionlength);
        leftsol->calls=leftcalls;
    }
    if(leftsol->goal <= 0)return leftsol;
    result*rightsol= coins2(coins, l, right, leftsol->goal, sollength);
    insertResults(leftsol, rightsol);
    return leftsol;
}
