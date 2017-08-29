
#include <stdlib.h>
#include <time.h>
#include "task_scheduling.h"
#include "test_task_scheduling.h"

#define VERBOSE 1

//const task tasks2[] = {{1 , 2 , 100} , {2 , 2 , 27} , {3 , 3 , 15} , {4 , 1 , 19} , {5 , 1 , 25}};
const task tasks_example[] = {{1 , 4 , 50} , {2 , 1 , 30} , {3 , 6 , 10} , {4 , 4 , 70} , {5 , 4 , 20} , {6 , 2 , 60} , {7 , 3 , 40}};
const int numTasks_example = sizeof(tasks_example) / sizeof(task);

void test_task_scheduler_example(){
    task* tasks_copy = cloneTasks(tasks_example , numTasks_example);
    resultTasks* r = taskScheduler(tasks_copy , numTasks_example);
    if (VERBOSE) printResultTasks(r);
    freeResultTasks(r);
    free(tasks_copy);
}

void test_task_scheduler_hybrid_example(){
    task* tasks_copy = cloneTasks(tasks_example , numTasks_example);
    resultTasks* r = taskSchedulerHybrid(tasks_copy , numTasks_example);
    if (VERBOSE) printResultTasks(r);
    freeResultTasks(r);
    free(tasks_copy);
}


// REAL TESTS
/*
int numTasks = 1000;
int maxPenalty = 500;
*/
int numTasks = 20;
int maxPenalty = 50;
task* tasks = NULL;

void test_task_scheduler_initialize(){
    srand(42);
    //srand(time(NULL));
    tasks = generateRandomTasksArray(numTasks , maxPenalty);
}

void test_task_scheduler(){
    task* tasks_copy = cloneTasks(tasks , numTasks);
    resultTasks* r = taskScheduler(tasks_copy , numTasks);
    if (VERBOSE) printResultTasks(r);
    freeResultTasks(r);
    free(tasks_copy);
}

void test_task_scheduler_hybrid(){
    task* tasks_copy = cloneTasks(tasks , numTasks);
    resultTasks* r = taskSchedulerHybrid(tasks_copy , numTasks);
    if (VERBOSE) printResultTasks(r);
    freeResultTasks(r);
    free(tasks_copy);
}