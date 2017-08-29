//
// Created by Nina on 21.8.2017.
//

#ifndef CLION_TASK_SCHEDULING_H
#define CLION_TASK_SCHEDULING_H

typedef struct Task{
    int id;
    int deadline;
    int penalty;
}task;

typedef struct linkedListTask{
    task task;
    struct linkedListTask* next;
}linkedListTask;

typedef struct resultTasks{
    linkedListTask* solutionFirst;
    linkedListTask* solutionLast;
    int calls;
    int penalty;

}resultTasks;

task* cloneTasks(const task* tasks , int numTasks);
task* generateRandomTasksArray(int numTasks , int maxPenalty);
void printResultTasks(resultTasks * result);
void freeResultTasks(resultTasks* r);
resultTasks* taskScheduler(task* tasks , int numTasks);
resultTasks* taskSchedulerHybrid(task* tasks , int numTasks);
void test();

#endif //CLION_TASK_SCHEDULING_H
