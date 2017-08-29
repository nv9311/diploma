
#ifndef CLION_ACTIVITY_SELECTION_H
#define CLION_ACTIVITY_SELECTION_H

typedef struct Activity{
    int activityNumber;
    int startTime;
    int finishTime;
} activity;

typedef struct linkedListActivity{
    activity a;
    struct linkedListActivity* next;
} linkedListActivity;

typedef struct resultActivities{
    linkedListActivity* solutionFirst;
    linkedListActivity* solutionLast;
    //int goal;
    //int solLength;
    int calls;
} resultActivities;



activity* cloneActivities(const activity* activities , int activitiesLen);
activity* generateRandomActivitiesArray(int numActivities , int maxStartTime , int maxDuration);
void freeResultActivity(resultActivities* r);
void printResultActivity(resultActivities * result);

resultActivities* activitySelectorHybrid(activity* activities , int left , int right, int* i);
resultActivities* activitySelector(activity* activities , int numActivities);

int testa();

#endif //CLION_ACTIVITY_SELECTION_H
