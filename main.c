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

    do_test("Coins0 Example", &test_coins0_example);
    do_test("Coins1 Example", &test_coins1_example);
    do_test("Coins2 Example", &test_coins2_example);

    test_coins_initialize();
    do_test("Coins1", &test_coins1);
    do_test("Coins2", &test_coins2);

    return 0;
}
