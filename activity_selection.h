//
// Created by Nina on 19.8.2017.
//

#ifndef CLION_ACTIVITY_SELECTION_H
#define CLION_ACTIVITY_SELECTION_H

typedef struct Activity{
    int activityNumber;
    int startTime;
    int finishTime;
}activity;

typedef struct linkedListActivity{
    activity a;
    struct linkedListActivity* next;
} linkedListActivity;

typedef struct resultActivities{
    linkedListActivity * solutionFirst;
    linkedListActivity * solutionLast;
    //int goal;
    //int solLength;
    int calls;
} resultActivities;



activity* cloneActivities(const activity* activities , int activitiesLen);
resultActivities* activitySelectorHybrid(activity* activities , int left , int right, int* i);
resultActivities* activitySelector(activity* activities , int numActivities);
void freeResultActivity(resultActivities* r);
void printResultActivity(resultActivities * result);
int test();

#endif //CLION_ACTIVITY_SELECTION_H
