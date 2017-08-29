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


item* cloneItems(const item* items , int numItems);
item* generateRandomItemsArray(int numItems , int maxValue , int maxWeight);
void printResultKnapsack(resultKnapsack * result);
void freeResultKnapsack(resultKnapsack* r);

resultKnapsack* fractionalKnapsack(item* items , int W , int itemsLen);
resultKnapsack* fractionalKnapsackHybrid(item* items , int left , int right ,int W , double profit);

int testf();
#endif //CLION_FRACTIONAL_KNAPSACK_H
