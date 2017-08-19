//
// Created by Nina on 19.8.2017.
//

#include <stdlib.h>

#include "test_activity_selection.h"
#include "activity_selection.h"

#define VERBOSE 1

int numActivities = 12;
int i = -1;
//activity* activities = NULL;
activity activities[12] = {{0,44,86}, {1,7,25}, {2,37,96} , {3,83,89} , {4,27,84} , {5,49,62} , {6,44,70} , {7,44,84} , {8,16,17} , {9,58,94} , {10,27,79} , {11,26,57}};



void test_activity_selection_initialize(){
    //to do for other examples
}
void test_activity_selector(){
    activity* activities_copy = cloneActivities(activities , numActivities);
    resultActivities* r = activitySelector(activities_copy , numActivities);
    if (VERBOSE) printResultActivity(r);
    freeResultActivity(r);
    free(activities_copy);
}

void test_activity_selector_hybrid(){
    activity* activities_copy = cloneActivities(activities , numActivities);
    resultActivities* r = activitySelectorHybrid(activities_copy , 0 , numActivities - 1 , &i);
    if (VERBOSE) printResultActivity(r);
    freeResultActivity(r);
    free(activities_copy);
}