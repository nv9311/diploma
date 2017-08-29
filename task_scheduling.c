//
// Created by Nina on 21.8.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mem.h>

#include "common.h"
#include "task_scheduling.h"

//http://www.cs.toronto.edu/~siavosh/csc373h/files/TN2.pdf
//http://www.cs.mun.ca/~kol/courses/6783-w13/lec3.pdf


void swapTasks(task* tasks , const int l, const int r){
    task tmp = tasks[l];
    tasks[l] = tasks[r];
    tasks[r] = tmp;
}
void appendTaskToResult (linkedListTask** linkedListFirst , linkedListTask** linkedListLast , task t){
    linkedListTask* newTask = (linkedListTask*)malloc(sizeof(linkedListTask));
    newTask->task = t;
    newTask->next = NULL;
    if (*linkedListLast != NULL) {
        (*linkedListLast)->next = newTask;
    }
    *linkedListLast = newTask;
    if (*linkedListFirst == NULL) {
        *linkedListFirst = newTask;
    }
}

resultTasks* constructResultTasks (linkedListTask* solutionFirst , linkedListTask* solutionLast , int penalty){
    resultTasks* r = (resultTasks*)malloc(sizeof(resultTasks));
    r->solutionFirst = solutionFirst;
    r->solutionLast = solutionLast;
    r->penalty = penalty;
    r->calls = 1;
    return r;
}

void mergeResultsTasks(resultTasks* left, resultTasks* right){
    if (right->solutionFirst == NULL) {
        assert(right->solutionLast == NULL);
        left->calls = right->calls + left->calls;
        left->penalty = right->penalty;
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
    left->penalty = right->penalty;
    free(right);
}

task* cloneTasks(const task* tasks , int numTasks){
    task* newTasks = (task*)malloc(sizeof(task) * numTasks);
    memcpy(newTasks, tasks, numTasks * sizeof(task));
    return newTasks;
}

task* generateRandomTasksArray(int numTasks , int maxPenalty){
    task* tasks = (task*)malloc(sizeof(task) * numTasks);
    for (int i = 0 ; i < numTasks ; i++) {
        //rand from 0 to numtasks-1 --> +1
        tasks[i].id = i + 1;
        tasks[i].deadline = (rand() % numTasks) + 1;
        tasks[i].penalty = (rand() % maxPenalty) + 1;
    }
    return tasks;
}

void printLinkedListTasks(const linkedListTask* linkedListFirst){
    printf("List of Tasks in Schedule: \n");
    while (linkedListFirst != NULL){
        printf("task: %d ; (deadline: %d ; penalty: %d)\n", linkedListFirst->task.id , linkedListFirst->task.deadline , linkedListFirst->task.penalty);
        linkedListFirst = linkedListFirst->next;
    }
    printf("\n");
}

void printResultTasks(resultTasks * result){
    printf("Result:\n");
    printf("Number of Calls: %d \n" , result->calls);
    printf("Total penalty: %d \n" , result->penalty);
    printLinkedListTasks(result->solutionFirst);
}

void freeLinkedListTasks(linkedListTask* linkedListFirst){
    while(linkedListFirst != NULL) {
        linkedListTask* next = linkedListFirst->next;
        free(linkedListFirst);
        linkedListFirst = next;
    }
}

void freeResultTasks(resultTasks* r){
    freeLinkedListTasks(r->solutionFirst);
    free(r);
}

int quicksortTasks(task* tasks , int left , int right){
    if(right <= left) return 1;
    //calls++;
    task t = tasks[left];
    int l = left;
    int r = right;
    while(l <= r){
        while(tasks[l].penalty > t.penalty) l += 1;
        while(tasks[r].penalty < t.penalty) r -= 1;
        if(l > r)break;
        swapTasks(tasks , l , r);
        l += 1;
        r -= 1;
    }
    return quicksortTasks(tasks, left, r) + quicksortTasks(tasks, l, right);
}

void considerTasks(resultTasks* result , task t , node* disjointSetForest ,  int* latestAvailable){
    int j = latestAvailable[findSet(t.deadline , disjointSetForest)];
    int oldAvailable = -1;
    if(j != 0){
        //add task i-1 to interval (j-1,j)
        //schedule[j - 1] = tasks[i-1].id;
        appendTaskToResult(&(result->solutionFirst) , &(result->solutionLast) , t);
        oldAvailable = latestAvailable[ findSet(j - 1 , disjointSetForest) ];
        unionNodes(j - 1 , j , disjointSetForest);
        latestAvailable[ findSet(j , disjointSetForest) ] = oldAvailable;
    }
    else{
        result->penalty += t.penalty;
        printf("penaltcons: %d id: %d dead: %d\n", result->penalty, t.id , t.deadline);
    }
}

resultTasks* taskSchedulerHybridRecursive(task* tasks , int left , int right , node* disjointSetForest , int* latestAvailable , int penalty){
    if(right < left){
        return constructResultTasks(NULL , NULL , penalty);
    }
    task t = tasks[left];
    if(right == left){
        printf("r=l %d dead: %d \n", t.id , t.deadline);
        resultTasks* result = constructResultTasks(NULL , NULL , penalty);
        considerTasks(result , t , disjointSetForest , latestAvailable);
        return result;
    }
    calls++;
    int l = left;
    int r = right;
    while(l <= r){
        while(tasks[l].penalty > t.penalty) l += 1;
        while(tasks[r].penalty < t.penalty) r -= 1;
        if(l > r)break;
        swapTasks(tasks , l , r);
        l += 1;
        r -= 1;
    }
    resultTasks* leftsol = taskSchedulerHybridRecursive(tasks , left , r , disjointSetForest , latestAvailable , penalty);
    if(l - r == 2){
        considerTasks(leftsol , t , disjointSetForest , latestAvailable);
        printf("l-r: %d dead: %d \n", t.id , t.deadline);
    }
    resultTasks* rightsol = taskSchedulerHybridRecursive(tasks , l , right , disjointSetForest , latestAvailable , leftsol->penalty);
    mergeResultsTasks(leftsol, rightsol);
    //calls = leftsol->calls;
    return leftsol;
}

resultTasks* taskSchedulerHybrid(task* tasks , int numTasks){
    int * latestAvailable = (int*)malloc(sizeof(int) * (numTasks + 1));
    node * disjointSetForest = (node*)malloc(sizeof(node) * (numTasks + 1));
    int penalty =  0;

    for(int i = 0 ; i <= numTasks ; i++){
        latestAvailable[i] = i;
        disjointSetForest[i] = makeSet(i);
    }

    resultTasks* result = taskSchedulerHybridRecursive(tasks , 0 , numTasks - 1 , disjointSetForest , latestAvailable , penalty);
    free(latestAvailable);
    free(disjointSetForest);
    return result;
}

resultTasks* taskScheduler(task* tasks , int numTasks){
    linkedListTask* solutionFirst = NULL;
    linkedListTask* solutionLast = NULL;
    int penalty = 0;
    int oldAvailable = -1;
    int j = -1;
    int * latestAvailable = (int*)malloc(sizeof(int) * (numTasks + 1));
    node * disjointSetForest = (node*)malloc(sizeof(node) * (numTasks + 1));
    //int * schedule = (int*)malloc(sizeof(int) * numTasks);

    for(int i = 0 ; i <= numTasks ; i++){
        latestAvailable[i] = i;
        disjointSetForest[i] = makeSet(i);
    }

    int calls = quicksortTasks(tasks , 0 , numTasks - 1);
    printf("\n");
    for(int i=0; i< numTasks;i++){
        printf("quick: %d\n" , tasks[i].id);
    }
    printf("\n");


    for(int i = 1 ; i <= numTasks ; i++){
        j = latestAvailable[findSet(tasks[i - 1].deadline , disjointSetForest)];
        if(j != 0){
            //add task i-1 on interval (j-1,j)
            //schedule[j - 1] = tasks[i-1].id;
            appendTaskToResult(&solutionFirst , &solutionLast , tasks[i - 1]);
            oldAvailable = latestAvailable[ findSet(j - 1 , disjointSetForest) ];
            unionNodes(j - 1 , j ,disjointSetForest);
            latestAvailable[ findSet(j , disjointSetForest) ] = oldAvailable;
        }
        else{
            penalty += tasks[i - 1].penalty;
            printf("penal: %d id:%d dead: %d\n", penalty , tasks[i-1].id , tasks[i-1].deadline);
        }
    }
    resultTasks* result = constructResultTasks(solutionFirst , solutionLast , penalty);
    result->calls = calls;
    free(latestAvailable);
    free(disjointSetForest);
    return result;
}
void test(){
    int numTasks = 5;
    //task* tasks = (task*)malloc(sizeof(task) * numTasks);
    task tasks2[4] = {{1 , 2 , 5} , {2 , 2 , 5} , {3 , 1 , 100} , {4 , 4 , 10}};
    task tasks[5] = {{1 , 2 , 100} , {2 , 2 , 27} , {3 , 3 , 15} , {4 , 1 , 19} , {5 , 1 , 25}};
    resultTasks* result = taskSchedulerHybrid(tasks , numTasks);
    //printIntArray(scheduler , numTasks);
    printResultTasks(result);
    freeResultTasks(result);
}



