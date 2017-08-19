//
// Created by Nina on 10.8.2017.
//
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"

#include "common.h"
#include "kruskal.h"



//Cormen et al. suggest an implementation in which the vertices are
// represented by index numbers.[2] Their representation uses an array indexed
// by vertex number, in which the array cell for each vertex points to a
// singly linked list of the neighboring vertices of that vertex.
// In this representation, the nodes of the singly linked list may be
// interpreted as edge objects; however, they do not store the full information
// about each edge (they only store one of the two endpoints of the edge) and
// in undirected graphs there will be two different linked list nodes for each edge
// (one within the lists for each of the two endpoints of the edge).


//we assume that vertices are numbers from zero on

void constructEdge(edge * e , int source , int dest , int weight){
    e->source = source;
    e->dest = dest;
    e->weight = weight;
}

void printArrayEdges(int E , edge* edges){
    for(int i = 0 ; i < E ; i++){
        printf("%d  src: %d  dest: %d\n" , edges[i].weight, edges[i].source , edges[i].dest);
    }
}

void addEdgetoResult(edge newEdge , edge ** result , int * resultLen){
    (*resultLen)++;
    *result = (edge*)realloc(*result, (*resultLen) * sizeof(edge));
    (*result)[(*resultLen)-1].source = newEdge.source;
    (*result)[(*resultLen)-1].dest = newEdge.dest;
    (*result)[(*resultLen)-1].weight = newEdge.weight;
}

graph* constructGraph(int V , int E){
    graph* g = (graph*)malloc(sizeof(graph));
    g->E = E;
    g->V = V;
    g->edges = (edge*)malloc(sizeof(edge) * E);
    return g;
}

resultMST* constructResultMST(linkedListEdge* solutionFirst, linkedListEdge* solutionLast, int calls){
    resultMST* r = (resultMST*)malloc(sizeof(resultMST));
    r->solutionFirst = solutionFirst;
    r->solutionLast = solutionLast;
    r->solLength = 0;
    r->calls = 1;
    return r;
}

void appendEdgeToResult(linkedListEdge** linkedListFirst , linkedListEdge** linkedListLast , edge e){
    linkedListEdge* newEdge = (linkedListEdge*)malloc(sizeof(linkedListEdge));
    newEdge->e = e;
    newEdge->next = NULL;
    if (*linkedListLast != NULL) {
        (*linkedListLast)->next = newEdge;
    }
    *linkedListLast = newEdge;
    if (*linkedListFirst == NULL) {
        *linkedListFirst = newEdge;
    }
}

void swapEdges(edge * edges , const int left , const int right){
    edge tmp = edges[left];
    edges[left] = edges[right];
    edges[right] = tmp;
    //constructEdge(&edges[left] , edges[right].source , edges[right].dest , edges[right].weight);
    //constructEdge(&edges[right] , tmp.source , tmp.dest , tmp.weight);
}

void mergeResultsMST(resultMST* left, resultMST* right){
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
    left->solLength = right->solLength;
    free(right);
}

void printLinkedListEdge(const linkedListEdge* linkedListFirst){
    printf("List of Edges in MST: \n");
    while (linkedListFirst != NULL){
        printf("%d --- %d ; weight: %d\n", linkedListFirst->e.source , linkedListFirst->e.dest , linkedListFirst->e.weight);
        linkedListFirst = linkedListFirst->next;
    }
    printf("\n");
}

void printResultMST(resultMST * result){
    printf("Result:\n");
    printf("Number of Calls: %d \n" , result->calls);
    printLinkedListEdge(result->solutionFirst);
}

void freeLinkedListEdge(linkedListEdge* linkedListFirst){
    while(linkedListFirst != NULL) {
        linkedListEdge* next = linkedListFirst->next;
        free(linkedListFirst);
        linkedListFirst = next;
    }
}

void freeResultMST(resultMST* r){
    freeLinkedListEdge(r->solutionFirst);
    free(r);
}

int quicksortMST(edge * edges , int left , int right){
    if(right <= left){
        return 1;
    }
    calls++;
    edge e = edges[left];
    int l = left;
    int r = right;
    while(l <= r){

        while(edges[l].weight < e.weight) l += 1;
        while(edges[r].weight > e.weight) r -= 1;
        if(l > r) break;
        swapEdges(edges , l , r);
        l += 1;
        r -= 1;
    }
    return quicksortMST(edges , left , r) + quicksortMST(edges , l , right);
}

node makeSet(int x){
    node n;
    n.parent = x;
    n.rank = 0;
    return n;
}

int findSet(int x , node *  forest){
    int newParent = forest[x].parent;
    if(x != newParent){
        newParent = findSet(newParent , forest);
    }
    return newParent;
}
void link(int x , int y , node * forest){
    int rankX = forest[x].rank;
    int rankY = forest[y].rank;
    if(rankX > rankY){
        forest[y].parent = x;
    }
    else{
        forest[x].parent = y;
        if( rankX == rankY ){
            forest[y].rank = rankY + 1;
        }
    }
}

void unionNodes(int x , int y , node * forest){
    link(findSet( x , forest ) , findSet( y , forest) , forest);
}

//vozlisca so podana kot integerji od 0 do stevila vozlisc - 1

void considerMST(resultMST* r , edge e , node* forest) {
    int u = e.dest;
    int v = e.source;
    if(findSet( u , forest)!= findSet(v , forest)){
        unionNodes(u , v , forest);
        appendEdgeToResult(&(r->solutionFirst), &(r->solutionLast) , e);
        r->solLength += 1;
    }
}

resultMST* MSTKruskal(graph* g){

    linkedListEdge* solutionFirst = NULL;
    linkedListEdge* solutionLast = NULL;

    node * forest = malloc( sizeof(node) * g->V );
    for(int i = 0 ; i < g->V ; i++){
        forest[i] = makeSet(i);
    }
    int calls = quicksortMST(g->edges , 0 , g->E - 1);
    /*izpise sortirana vozlisca
     * printArrayEdges(g->E , g->edges);
    */
    for(int i = 0 ; i < g->E ; i++){
        int v = g->edges[i].source;
        int u = g->edges[i].dest;
        if(findSet( u , forest)!= findSet(v , forest)){
            unionNodes(u , v , forest);
            appendEdgeToResult(&solutionFirst, &solutionLast, g->edges[i]);
            //addEdgetoResult(g.edges[i] , &result, &resultLen);
        }
    }
    free(forest);
    resultMST* result = constructResultMST(solutionFirst, solutionLast, calls);
    result->calls = calls;
    return result;
}
resultMST* MSTKruskalHybrid(graph* g , int left , int right, int solLen , node * forest){
    if(right < left){
        //calls = 1;
        return constructResultMST(NULL , NULL , 1);
    }
    edge e = g->edges[left];
    if(right == left){
        //calls = 1;
        resultMST* result = constructResultMST(NULL , NULL , 1);
        considerMST(result , e , forest);
        return result;
    }
    calls++;
    int l = left;
    int r = right;
    while(l <= r){
        while(g->edges[l].weight < e.weight) l += 1;
        while(g->edges[r].weight > e.weight) r -= 1;
        if(l > r) break;
        swapEdges(g->edges , l , r);
        l += 1;
        r -= 1;
    }
    resultMST* leftsol = MSTKruskalHybrid(g , left , r , solLen, forest);
    if(l - r == 2){
        considerMST(leftsol , e , forest);
    }
    if(leftsol->solLength >= g->V - 1) return leftsol;
    resultMST* rightsol = MSTKruskalHybrid(g , l , right , leftsol->solLength , forest);
    mergeResultsMST(leftsol, rightsol);
    //calls = leftsol->calls;
    return leftsol;
}

resultMST* callKruskalHybrid(graph* g){

    //we need to make a forest of nodes so that we can then compute a MSTree recursively
    node * forest = malloc( sizeof(node) * g->V );
    for(int i = 0 ; i < g->V ; i++){
        forest[i] = makeSet(i);
    }

    resultMST * result= MSTKruskalHybrid(g , 0 , g->E - 1 , 0 , forest);
    free(forest);
    return result;
}
