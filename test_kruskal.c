//
// Created by Nina on 10.8.2017.
//

#include <stdlib.h>
#include "test_kruskal.h"
#include "kruskal.h"
#include "common.h"

#define VERBOSE 0

int V = 9;
int E = 14;
graph* g = NULL;



void test_kruskal_initialize() {
    g = constructGraph(V , E);

    g->edges[0].source = 0;
    g->edges[0].dest = 1;
    g->edges[0].weight = 4;

    g->edges[1].source = 0;
    g->edges[1].dest = 7;
    g->edges[1].weight = 8;

    g->edges[2].source = 1;
    g->edges[2].dest = 2;
    g->edges[2].weight = 8;

    g->edges[3].source = 1;
    g->edges[3].dest = 7;
    g->edges[3].weight = 11;

    g->edges[4].source = 2;
    g->edges[4].dest = 3;
    g->edges[4].weight = 7;

    g->edges[5].source = 2;
    g->edges[5].dest = 5;
    g->edges[5].weight = 4;

    g->edges[6].source = 2;
    g->edges[6].dest = 8;
    g->edges[6].weight = 2;

    g->edges[7].source = 3;
    g->edges[7].dest = 4;
    g->edges[7].weight = 9;

    g->edges[8].source = 3;
    g->edges[8].dest = 5;
    g->edges[8].weight = 14;

    g->edges[9].source = 4;
    g->edges[9].dest = 5;
    g->edges[9].weight = 10;

    g->edges[10].source = 5;
    g->edges[10].dest = 6;
    g->edges[10].weight = 2;

    g->edges[11].source = 6;
    g->edges[11].dest = 7;
    g->edges[11].weight = 1;

    g->edges[12].source = 6;
    g->edges[12].dest = 8;
    g->edges[12].weight = 6;

    g->edges[13].source = 7;
    g->edges[13].dest = 8;
    g->edges[13].weight = 7;
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

