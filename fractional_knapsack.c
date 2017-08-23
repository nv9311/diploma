//
// Created by Nina on 20.8.2017.
//

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fractional_knapsack.h"


void swapItems(item* items , const int left , const int right){
    item tmp = items[left];
    items[left] = items[right];
    items[right] = tmp;
}

void appendItemToResult(linkedListItem** linkedListFirst , linkedListItem** linkedListLast , item i){
    linkedListItem* newItem = (linkedListItem*)malloc(sizeof(linkedListItem));
    newItem->i = i;
    newItem->next = NULL;
    if (*linkedListLast != NULL) {
        (*linkedListLast)->next = newItem;
    }
    *linkedListLast = newItem;
    if (*linkedListFirst == NULL) {
        *linkedListFirst = newItem;
    }
}

resultKnapsack* constructResultKnapsack(linkedListItem* solutionFirst , linkedListItem* solutionLast , int calls , double profit , int W){
    resultKnapsack* r = (resultKnapsack*)malloc(sizeof(resultKnapsack));
    r->solutionFirst = solutionFirst;
    r->solutionLast = solutionLast;
    r->totalProfit = profit;
    r->W = W;
    //r->solLength = 0;
    r->calls = 1;
    return r;
}

void mergeResultsItems(resultKnapsack* left, resultKnapsack* right){
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
    left->W = right->W;
    left->totalProfit = right->totalProfit;
    free(right);
}

item* cloneItems(const item* items , const int numItems){
    item* newItems = (item*)malloc(sizeof(item) * numItems);
    memcpy(newItems, items, numItems * sizeof(item));
    return newItems;
}

void printLinkedListItems(const linkedListItem* linkedListFirst){
    printf("List of items taken: \n");
    while (linkedListFirst != NULL){
        printf("item: (value: %d , weight: %d ) amount taken: %.2lf\n", linkedListFirst->i.value , linkedListFirst->i.weight , linkedListFirst->i.amountTaken);
        linkedListFirst = linkedListFirst->next;
    }
    printf("\n");
}

void printResultKnapsack(resultKnapsack * result){
    printf("Result:\n");
    printf("Number of Calls: %d \n" , result->calls);
    printf("Total profit: %.2lf\n", result->totalProfit);
    printf("W: %d\n", result->W);
    printLinkedListItems(result->solutionFirst);
}

void freeLinkedListItems(linkedListItem* linkedListFirst){
    while(linkedListFirst != NULL) {
        linkedListItem* next = linkedListFirst->next;
        free(linkedListFirst);
        linkedListFirst = next;
    }
}

void freeResultKnapsack(resultKnapsack* r){
    freeLinkedListItems(r->solutionFirst);
    free(r);
}

int quicksortItems(item* items , int left , int right){
    if(right <= left) return 1;
    //calls++;
    item i = items[left];
    int l = left;
    int r = right;
    while(l <= r){

        while((double) (items[l].value / items[l].weight) > (double) (i.value / i.weight)) l += 1;
        while((double) (items[r].value / items[r].weight) < (double) (i.value / i.weight)) r -= 1;
        if(l > r)break;
        swapItems(items , l , r);
        l += 1;
        r -= 1;
    }
    return quicksortItems(items, left, r) + quicksortItems(items, l, right);
}

resultKnapsack* fractionalKnapsack(item* items , int W , int itemsLen){

    int calls = quicksortItems(items , 0 , itemsLen - 1);
    linkedListItem* solutionFirst = NULL;
    linkedListItem* solutionLast = NULL;

    double totalProfit = 0.0;

    for(int i = 0 ; i < itemsLen ; i++){
        if(items[i].weight <= W){
            W -= items[i].weight;
            items[i].amountTaken = 1;
            totalProfit += items[i].value;
            appendItemToResult(&solutionFirst , &solutionLast , items[i]);
        }
        else{
            items[i].amountTaken = (double) W / items[i].weight;
            W -= items[i].amountTaken * items[i].weight;
            totalProfit += items[i].value * items[i].amountTaken;
            appendItemToResult(&solutionFirst , &solutionLast , items[i]);
            break;
        }
    }
    resultKnapsack* result = constructResultKnapsack(solutionFirst , solutionLast , calls , totalProfit , W);
    result->calls = calls;
    return result;
}

void considerItems(resultKnapsack* r , item i){
    if(i.weight <= r->W){
        r->W -= i.weight;
        i.amountTaken = 1;
        r->totalProfit += i.value;
        appendItemToResult(&(r->solutionFirst) , &(r->solutionLast) , i);
    }
    else{
        i.amountTaken = (double) r->W / i.weight;
        r->W -= i.amountTaken * i.weight;
        r->totalProfit += i.value * i.amountTaken;
        appendItemToResult(&(r->solutionFirst) , &(r->solutionLast) , i);
    }
}

resultKnapsack* fractionalKnapsackHybrid(item* items , int left , int right , int W , double profit){
    if(right < left){
        return constructResultKnapsack(NULL , NULL , 1 , profit , W);
    }
    item i = items[left];
    if(right == left){
        resultKnapsack* result = constructResultKnapsack(NULL , NULL , 1 , profit , W);
        considerItems(result , i);
        return result;
    }
    int l = left;
    int r = right;
    while(l <= r){

        while((double) (items[l].value / items[l].weight) > (double) (i.value / i.weight)) l += 1;
        while((double) (items[r].value / items[r].weight) < (double) (i.value / i.weight)) r -= 1;
        if(l > r)break;
        swapItems(items , l , r);
        l += 1;
        r -= 1;
    }
    resultKnapsack* leftsol = fractionalKnapsackHybrid(items , left , r , W , profit);
    if(l - r == 2){
        considerItems(leftsol , i);
    }
    if(leftsol->W <= 0) return leftsol;
    resultKnapsack* rightsol = fractionalKnapsackHybrid(items , l , right , leftsol->W , leftsol->totalProfit);
    mergeResultsItems(leftsol , rightsol);
    return leftsol;
}

int testf(){
    item items[3] ={{60 , 10} , {100 , 20},{120 , 30}};
    resultKnapsack* result = fractionalKnapsack(items , 50 , 3);
    //resultKnapsack* result = fractionalKnapsackHybrid(items , 0 , 2 , 50 , 0.0);
    //printf("profit: %.2lf W: %d" , result->totalProfit , result->W);
    printResultKnapsack(result);
    freeResultKnapsack(result);
    return 0;
}


