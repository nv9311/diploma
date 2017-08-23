//
// Created by Nina on 21.8.2017.
//

#include "task_scheduling.h"

//http://www.cs.toronto.edu/~siavosh/csc373h/files/TN2.pdf
//http://www.cs.mun.ca/~kol/courses/6783-w13/lec3.pdf

typedef struct Task{
    int deadline;
    int penalty;
}task;

typedef struct linkedListTask{
    task i;
    struct linkedListTask* next;
}linkedListTask;

typedef struct resultTasks{
    linkedListTask* solutionFirst;
    linkedListTask* solutionLast;
    int calls;
    int penalty;

}resultTasks;

void swapTasks(task* tasks , const int l, const int r){
    task tmp = tasks[l];
    tasks[l] = tasks[r];
    tasks[r] = tmp;
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

/*
resultTasks* taskScheduler(task* tasks , int numTasks){
    int calls = quicksortTasks(tasks , 0 , numTasks - 1);

}

//kruskal funtions


void  makeSet(int ){
    node n;
    n.parent = x;
    n.rank = 0;
    return n;
}

int findSet(int x , node *  forest){
    int newParent = forest[x].parent;
    if(x != newParent){
        newParent = findSet(newParent , forest);
    }
    return newParent;
}
void link(int x , int y , node * forest){
    int rankX = forest[x].rank;
    int rankY = forest[y].rank;
    if(rankX > rankY){
        forest[y].parent = x;
    }
    else{
        forest[x].parent = y;
        if( rankX == rankY ){
            forest[y].rank = rankY + 1;
        }
    }
}

void unionNodes(int x , int y , node * forest){
    link(findSet( x , forest ) , findSet( y , forest) , forest);
}

*/