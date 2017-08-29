
#include <stdlib.h>

#include "test_activity_selection.h"
#include "activity_selection.h"

#define VERBOSE 1


const activity activities_example[] = {{0, 1, 3},{1, 0, 4},{2, 1, 2},{3, 4, 6},{4, 2, 9},{5, 5, 8},{6, 3, 5},{7, 4, 5}};
const int numActivities_example = sizeof(activities_example) / sizeof(activity);

//activity activities[12] = {{0,44,86}, {1,7,25}, {2,37,96} , {3,83,89} , {4,27,84} , {5,49,62} , {6,44,70} , {7,44,84} , {8,16,17} , {9,58,94} , {10,27,79} , {11,26,57}};

void test_activity_selector_example(){
    activity* activities_copy = cloneActivities(activities_example , numActivities_example);
    resultActivities* r = activitySelector(activities_copy , numActivities_example);
    if (VERBOSE) printResultActivity(r);
    freeResultActivity(r);
    free(activities_copy);
}

void test_activity_selector_hybrid_example(){
    int finishTime = INT_MIN;
    activity* activities_copy = cloneActivities(activities_example , numActivities_example);
    resultActivities* r = activitySelectorHybrid(activities_copy , 0 , numActivities_example - 1 , &finishTime);
    if (VERBOSE) printResultActivity(r);
    freeResultActivity(r);
    free(activities_copy);
}

//REAL TEST
activity* activities = NULL;

int numActivities = 50;
int maxStartTime = 25;
int maxDuration =  20;
/*
int numActivities = 1000;
int maxStartTime = 570;
int maxDuration =  300;
*/
/*
int numActivities = 30000;
int maxStartTime = 15000;
int maxDuration = 10000;
*/

void test_activity_selection_initialize(){
    srand(42);
    //srand(time(NULL));
    activities = generateRandomActivitiesArray(numActivities , maxStartTime , maxDuration);
}

void test_activity_selector(){
    activity* activities_copy = cloneActivities(activities , numActivities);
    resultActivities* r = activitySelector(activities_copy , numActivities);
    if (VERBOSE) printResultActivity(r);
    freeResultActivity(r);
    free(activities_copy);
}

void test_activity_selector_hybrid(){
    int finishTime = INT_MIN;
    activity* activities_copy = cloneActivities(activities , numActivities);
    resultActivities* r = activitySelectorHybrid(activities_copy , 0 , numActivities - 1 , &finishTime);
    if (VERBOSE) printResultActivity(r);
    freeResultActivity(r);
    free(activities_copy);
}
