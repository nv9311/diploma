#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "common.h"
#include "test_coins.h"

#include "test_kruskal.h"

#include "test_activity_selection.h"

#include "test_fractional_knapsack.h"

#include "task_scheduling.h"

int N_ITERS = 1;

typedef void (*test_function_pointer)(void);
void do_test(const char* name, test_function_pointer f) {
    printf("*%s*\n", name);
    calls = 0;
    clock_t cpubegin = clock();
    for (int i = 0; i < N_ITERS; i++) {
        (*f)();
    }
    clock_t cpudelta = clock() - cpubegin;
    double cputime = (double)cpudelta * 1000 / CLOCKS_PER_SEC;
    printf("Average time: %lf ms\n", cputime / N_ITERS);
    printf("Average calls: %lf\n", (double)calls / N_ITERS);
    printf("\n");
}

int main(){
    srand(time(NULL));   // should only be called once

    //coins
    do_test("Coins0 Example", &test_coins0_example);
    do_test("Coins1 Example", &test_coins1_example);
    do_test("Coins2 Example", &test_coins2_example);

    test_coins_initialize();
    do_test("Coins0", &test_coins0);
    do_test("Coins1", &test_coins1);
    do_test("Coins2", &test_coins2);

    //kruskal
    test_kruskal_initialize();
    do_test("MST Kruskal",&test_kruskalMST);
    do_test("MST Kruskal Hybrid",&test_kruskalMSTHybrid);

    //activitySelector
    test_activity_selection_initialize();
    do_test("Activity Selection" , &test_activity_selector);
    do_test("Activity Selection Hybrid" , &test_activity_selector_hybrid);

    //fractionalKnapsack
    test_fractional_knapsack_initialize();
    do_test("Fractional Knapsack" , &test_fractional_knapsack);
    do_test("Fractional Knapsack Hybrid" , &test_fractional_knapsack_hybrid);
    //testf();

    test();
    return 0;
}
