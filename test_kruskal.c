//
// Created by Nina on 10.8.2017.
//

#include <stdlib.h>
#include <assert.h>
#include "test_kruskal.h"
#include "kruskal.h"
#include "common.h"

#define VERBOSE 1

const int V_example = 9;
const int E_example = 14;
graph* g_example = NULL;

void test_kruskal_initialize_example() {
    g_example = constructGraph(V_example , E_example);

    g_example->edges[0].source = 0;
    g_example->edges[0].dest = 1;
    g_example->edges[0].weight = 4;

    g_example->edges[1].source = 0;
    g_example->edges[1].dest = 7;
    g_example->edges[1].weight = 8;

    g_example->edges[2].source = 1;
    g_example->edges[2].dest = 2;
    g_example->edges[2].weight = 8;

    g_example->edges[3].source = 1;
    g_example->edges[3].dest = 7;
    g_example->edges[3].weight = 11;

    g_example->edges[4].source = 2;
    g_example->edges[4].dest = 3;
    g_example->edges[4].weight = 7;

    g_example->edges[5].source = 2;
    g_example->edges[5].dest = 5;
    g_example->edges[5].weight = 4;

    g_example->edges[6].source = 2;
    g_example->edges[6].dest = 8;
    g_example->edges[6].weight = 2;

    g_example->edges[7].source = 3;
    g_example->edges[7].dest = 4;
    g_example->edges[7].weight = 9;

    g_example->edges[8].source = 3;
    g_example->edges[8].dest = 5;
    g_example->edges[8].weight = 14;

    g_example->edges[9].source = 4;
    g_example->edges[9].dest = 5;
    g_example->edges[9].weight = 10;

    g_example->edges[10].source = 5;
    g_example->edges[10].dest = 6;
    g_example->edges[10].weight = 2;

    g_example->edges[11].source = 6;
    g_example->edges[11].dest = 7;
    g_example->edges[11].weight = 1;

    g_example->edges[12].source = 6;
    g_example->edges[12].dest = 8;
    g_example->edges[12].weight = 6;

    g_example->edges[13].source = 7;
    g_example->edges[13].dest = 8;
    g_example->edges[13].weight = 7;
}

void test_kruskalMST_example(){
    graph* graph_copy = cloneGraph(g_example);
    resultMST* r = MSTKruskal(graph_copy);
    if (VERBOSE) printResultMST(r);
    freeResultMST(r);
    free(graph_copy->edges);
    free(graph_copy);
}

void test_kruskalMSTHybrid_example(){
    graph* graph_copy = cloneGraph(g_example);
    resultMST* r = callKruskalHybrid(graph_copy);
    if (VERBOSE) printResultMST(r);
    freeResultMST(r);
    free(graph_copy->edges);
    free(graph_copy);
}



//REAL TESTS
const int V = 5;
//const int V = 30;
//const int E = 14;
int maxPrice = 10;
graph* g = NULL;

void test_kruskal_initialize() {
        // complete graph
        int E = V * (V - 1) / 2;
        g = constructGraph(V , E);

        int currentEdge = 0;
        for (int i = 0 ; i < V ; i++) {
            for (int j = i + 1 ; j < V ; j++) {
                g->edges[currentEdge].source = i;
                g->edges[currentEdge].dest   = j;
                g->edges[currentEdge].weight = (rand() % maxPrice) + 1;
                currentEdge++;
            }
        }
        assert(currentEdge == E);
}

void test_kruskalMST(){
    graph* graph_copy = cloneGraph(g);
    resultMST* r = MSTKruskal(graph_copy);
    if (VERBOSE) printResultMST(r);
    freeResultMST(r);
    free(graph_copy->edges);
    free(graph_copy);
}

void test_kruskalMSTHybrid(){
    graph* graph_copy = cloneGraph(g);
    resultMST* r = callKruskalHybrid(graph_copy);
    if (VERBOSE) printResultMST(r);
    freeResultMST(r);
    free(graph_copy->edges);
    free(graph_copy);
}

