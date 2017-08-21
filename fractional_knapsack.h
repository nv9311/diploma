//
// Created by Nina on 20.8.2017.
//

#ifndef CLION_FRACTIONAL_KNAPSACK_H
#define CLION_FRACTIONAL_KNAPSACK_H

typedef struct Item{
    int value;
    int weight;
    double amountTaken;
}item;

typedef struct linkedListItem{
    item i;
    struct linkedListItem* next;
}linkedListItem;

typedef struct resultKnapsack{
    linkedListItem* solutionFirst;
    linkedListItem* solutionLast;
    int calls;
    double totalProfit;
    int W;
}resultKnapsack;

resultKnapsack* fractionalKnapsack(item* items , int W , int itemsLen);
resultKnapsack* fractionalKnapsackHybrid(item* items , int left , int right ,int W , double profit);
item* cloneItems(const item* items , const int numItems);
void printResultKnapsack(resultKnapsack * result);
void freeResultKnapsack(resultKnapsack* r);


int testf();
#endif //CLION_FRACTIONAL_KNAPSACK_H
