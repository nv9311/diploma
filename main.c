#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "coins.h"
#include "test_coins.h"

typedef void (*test_function_pointer)(void);
void do_test(const char* name, test_function_pointer f) {
    printf("*%s*\n", name);
    calls=0;
    clock_t cpubegin = clock();
    (*f)();
    clock_t cputime = clock() - cpubegin;
    cputime = cputime * 1000 / CLOCKS_PER_SEC;
    printf("Time: %ld ms\n", cputime);
    printf("Calls: %d\n", calls);
    printf("\n");
}

int main(){
    srand(time(NULL));   // should only be called once

    do_test("Coins0", &test_coins0);
    do_test("Coins1", &test_coins1);
    do_test("Coins2", &test_coins2);

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
