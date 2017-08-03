#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "coins.h"
#include "common.h"

int main(){
    srand(time(NULL));   // should only be called once
    int goal=350;
    int coins [14] = {2, 1, 50, 1, 100, 2, 200, 2, 50, 100, 5, 1, 10, 2};
    calls=0;


    //coins1
    clock_t cpubegin = clock();

    result*r1= coins1(coins, 0, 13, goal, 0);

    clock_t cputime = clock() - cpubegin;
    cputime = cputime * 1000 / CLOCKS_PER_SEC;
    printf("r1 : %ld ms\n", cputime);

    printf("Calls: %d\n", calls);
    printf("Greedy1: %d %d %d\n",r1->goal,r1->calls,r1->solutionlength);
    for(int i=0; i < r1->solutionlength; i++){
        printf("%d ", r1->solution[i]);
    }
    printf("\n");
    printf("\n");

    //coins2
    cpubegin = clock();

    result*r2= coins2(coins, 0, 13, goal, 0);

    cputime = clock() - cpubegin;
    cputime = cputime * 1000 / CLOCKS_PER_SEC;
    printf("r2 : %ld ms\n", cputime);

    printf("Greedy2: %d %d %d\n",r2->goal,r2->calls,r2->solutionlength);
    for(int i=0; i < r2->solutionlength; i++){
        printf("%d ", r2->solution[i]);
    }
    printf("\n");
    printf("\n");

    //greedy3
    cpubegin = clock();

    result*r0= coins0(coins, goal, 14);

    cputime = clock() - cpubegin;
    cputime = cputime * 1000 / CLOCKS_PER_SEC;
    printf("r0 : %ld ms\n", cputime);

    printf("Greedy0: %d %d %d\n",r0->goal,r0->calls,r0->solutionlength);
    for(int i=0; i < r0->solutionlength; i++){
        printf("%d ", r0->solution[i]);
    }

    int n=30;
    int values [7] = {1, 2, 5, 10, 50, 100, 200};
    int goal2=1001;
    int r=0;

    int*coins2=(int*)malloc(sizeof(int)*n);
    for(int i=0; i<n; i++){
        //nevem al bi mela skos isti seed
        r = rand() % 7;
        //printf("Rand: %d ",r);
        coins2[i]=values[r];
    }


    /////timing experiment
    /*
    //greedy1
    srand(42);
	clock_t cpubegin = clock();

    result*r1=coins1(coins2,0,n-1,goal2,0);

    clock_t cputime = clock() - cpubegin;
	cputime = cputime * 1000 / CLOCKS_PER_SEC;
	printf("r1 : %ld ms\n", cputime);

    printf("Calls: %d\n", calls);
	printf("Greedy1: %d %d %d\n",r1->goal,r1->calls,r1->solutionlength);
	for(int i=0; i < r1->solutionlength; i++){
		printf("%d ", r1->solution[i]);
	}
    printf("\n");
    free(r1);

    //greedy2
    srand(42);
	cpubegin = clock();

    result*r2=coins2(coins2,0,n-1,goal2,0);

    cputime = clock() - cpubegin;
	cputime = cputime * 1000 / CLOCKS_PER_SEC;
	printf("r2 : %ld ms\n", cputime);

	printf("Greedy2: %d %d %d\n",r2->goal,r2->calls,r2->solutionlength);
	for(int i=0; i < r2->solutionlength; i++){
		printf("%d ", r2->solution[i]);
	}
     printf("\n");
    free(r2);

    //greedy3
    srand(42);
	cpubegin = clock();

    result*r0=coins0(coins2,goal2,n);

    cputime = clock() - cpubegin;
	cputime = cputime * 1000 / CLOCKS_PER_SEC;
	printf("r0 : %ld ms\n", cputime);

	printf("Greedy0: %d %d %d\n",r0->goal,r0->calls,r0->solutionlength);
	for(int i=0; i < r0->solutionlength; i++){
		printf("%d ", r0->solution[i]);
	}
    free(r0);
    */
    free(coins2);
    return 0;
}
