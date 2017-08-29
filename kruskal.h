
#ifndef CLION_KRUSKAL_H
#define CLION_KRUSKAL_H

typedef struct Edge{
    int source;
    int dest;
    int weight;
}edge;

typedef struct Graph{
    int V;
    int E;
    edge * edges;
}graph;

typedef struct linkedListEdge{
    edge e;
    struct linkedListEdge* next;
} linkedListEdge;

typedef struct resultMST{
    linkedListEdge * solutionFirst;
    linkedListEdge * solutionLast;
    //int goal;
    int solLength;
    int calls;
} resultMST;

graph* constructGraph(int V , int E);
graph* cloneGraph(const graph* g );
resultMST* MSTKruskal(graph* g);
resultMST* callKruskalHybrid(graph* g);
void printResultMST(resultMST * result);
void freeResultMST(resultMST* r);

#endif //CLION_KRUSKAL_H
