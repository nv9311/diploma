//
// Created by Nina on 19.8.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "activity_selection.h"
#include "common.h"

//activities ordered by monotoically increasing finish time
//each activity has start time and finish time, we want to take a maximum size subset of mutually compatible activities

void swapActivities(activity* activities , const int left , const int right){
    activity tmp = activities[left];
    activities[left] = activities[right];
    activities[right] = tmp;
}

resultActivities* constructResultActivities(linkedListActivity* solutionFirst , linkedListActivity* solutionLast , int calls){
    resultActivities* r = (resultActivities*)malloc(sizeof(resultActivities));
    r->solutionFirst = solutionFirst;
    r->solutionLast = solutionLast;
    //r->solLength = 0;
    r->calls = 1;
    return r;
}

void appendActivityToResult(linkedListActivity** linkedListFirst , linkedListActivity** linkedListLast , activity a){
    linkedListActivity* newActivity = (linkedListActivity*)malloc(sizeof(linkedListActivity));
    newActivity->a = a;
    newActivity->next = NULL;
    if (*linkedListLast != NULL) {
        (*linkedListLast)->next = newActivity;
    }
    *linkedListLast = newActivity;
    if (*linkedListFirst == NULL) {
        *linkedListFirst = newActivity;
    }
}

void mergeResultsActivities(resultActivities* left, resultActivities* right){
    if (right->solutionFirst == NULL) {
        assert(right->solutionLast == NULL);
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
    //left->solLength = right->solLength;
    free(right);
}

activity* cloneActivities(const activity* activities , int activitiesLen){
    activity* newActivities = (activity*)malloc(sizeof(activity) * activitiesLen);
    memcpy(newActivities, activities, activitiesLen * sizeof(activity));
    return newActivities;
}

activity* generateRandomActivitiesArray(int numActivities , int maxStartTime , int maxDuration){
    activity* activites = (activity*)malloc(sizeof(activity) * numActivities);
    for (int i = 0 ; i < numActivities ; i++) {
        //rand from 0 to numtasks-1 --> +1
        activites[i].activityNumber = i;
        activites[i].startTime = rand() % maxStartTime;
        activites[i].finishTime = activites[i].startTime + (rand() % maxDuration) +1;
    }
    return activites;
}

void printLinkedListActivity(const linkedListActivity* linkedListFirst){
    printf("List of compatible Activities: \n");
    while (linkedListFirst != NULL){
        printf("%d. duration: %d - %d\n", linkedListFirst->a.activityNumber , linkedListFirst->a.startTime , linkedListFirst->a.finishTime);
        linkedListFirst = linkedListFirst->next;
    }
    printf("\n");
}

void printResultActivity(resultActivities * result){
    printf("Result:\n");
    printf("Number of Calls: %d \n" , result->calls);
    printLinkedListActivity(result->solutionFirst);
}

void freeLinkedListActivity(linkedListActivity* linkedListFirst){
    while(linkedListFirst != NULL) {
        linkedListActivity* next = linkedListFirst->next;
        free(linkedListFirst);
        linkedListFirst = next;
    }
}

void freeResultActivity(resultActivities* r){
    freeLinkedListActivity(r->solutionFirst);
    free(r);
}

int quicksortActivities(activity* activities , int left , int right){
    if(right <= left) return 1;
    //calls++;
    activity a = activities[left];
    int l = left;
    int r = right;
    while(l <= r){
        while(activities[l].finishTime < a.finishTime) l += 1;
        while(activities[r].finishTime > a.finishTime) r -= 1;
        if(l > r)break;
        swapActivities(activities , l , r);
        l += 1;
        r -= 1;
    }
    return quicksortActivities(activities, left, r) + quicksortActivities(activities, l, right);
}

resultActivities* activitySelector(activity* activities , int numActivities){
    int calls = quicksortActivities(activities , 0 , numActivities - 1);
    /*
    for(int i = 0 ; i < numActivities ; i++){
        printf("%d  %d - %d\n" , activities[i].activityNumber, activities[i].startTime , activities[i].finishTime);
    }
     */
    linkedListActivity* solutionFirst = NULL;
    linkedListActivity* solutionLast = NULL;

    int i = 0;
    appendActivityToResult(&solutionFirst , &solutionLast , activities[i]);
    for(int m = 1 ; m < numActivities ; m++){
        if(activities[m].startTime >= activities[i].finishTime){
            appendActivityToResult(&solutionFirst , &solutionLast , activities[m]);
            i = m;
        }
    }
    resultActivities* result = constructResultActivities(solutionFirst , solutionLast , calls);
    result->calls = calls;
    return result;
}

void considerActivities(resultActivities* r , activity a , int* previousFinishTime){

    if(a.startTime >= *previousFinishTime){
        appendActivityToResult(&(r->solutionFirst) , &(r->solutionLast) , a);
        *previousFinishTime = a.finishTime;
    }
}

//there is no condition to make less recursive calls because we must go through all the activities
//there is no last finish time
resultActivities* activitySelectorHybrid(activity* activities , int left , int right, int* finishTime){
    if(right < left){
        return constructResultActivities(NULL , NULL , 1);
    }
    activity a = activities[left];
    if(right == left){
        resultActivities* result = constructResultActivities(NULL , NULL , 1);
        considerActivities(result , a , finishTime);
        return result;
    }
    //calls++;
    int l = left;
    int r = right;
    while(l <= r){
        while(activities[l].finishTime < a.finishTime) l += 1;
        while(activities[r].finishTime > a.finishTime) r -= 1;
        if(l > r)break;
        swapActivities(activities , l , r);
        l += 1;
        r -= 1;
    }
    resultActivities* leftsol = activitySelectorHybrid(activities , left , r , finishTime);
    if(l - r == 2){
        considerActivities(leftsol , a , finishTime);
    }
    resultActivities* rightsol = activitySelectorHybrid(activities , l , right , finishTime);
    mergeResultsActivities(leftsol , rightsol);
    return leftsol;
}

int testa(){
    //int numActivities = 8;
    //activity* activities = (activity*)malloc(sizeof(activity) * numActivities);

    //activity activities[8] = {{0, 1, 3},{1, 0, 4},{2, 1, 2},{3, 4, 6},{4, 2, 9},{5, 5, 8},{6, 3, 5},{7, 4, 5}};
    /*
    Result:
    Number of Calls: 8
    List of compatible Activities:
    2. duration: 1 - 2
    6. duration: 3 - 5
    5. duration: 5 - 8
    */


    activity activities[12] = {{0,44,86}, {1,7,25}, {2,37,96} , {3,83,89} , {4,27,84} , {5,49,62} , {6,44,70} , {7,44,84} , {8,16,17} , {9,58,94} , {10,27,79} , {11,26,57}};
    /*
     *  Result:
        Number of Calls: 12
        List of compatible Activities:
        8. duration: 16 - 17
        11. duration: 26 - 57
        3. duration: 83 - 89
     */
    int numActivities = 12;
    int finishTime = INT_MIN;
    //resultActivities* result = activitySelector(activities , numActivities);
    resultActivities* result = activitySelectorHybrid(activities , 0 , numActivities - 1 , &finishTime);


    printResultActivity(result);

    //free(activities);
    freeResultActivity(result);

    return 0;
}
