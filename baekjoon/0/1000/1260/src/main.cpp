#include <iostream>
#include <cstring>
#include <queue>
#define MAX 1001

using namespace std;

/*
 *  1. Idea
 *  
 *  - Create graph structure
 *  - Search graph using DFS with recursive function and BFS
 *  - If the edge is valid and the vertex is not visited, we call DFS
 *
 *  2. Data structure
 *
 *  Graph       : graph[][]
 *  Visit check : visited[]
 */
bool graph[MAX][MAX];
bool visited[MAX];
int v, e, start;
queue<int> q;

void doDFS(int _v)
{
    visited[_v] = true;
    printf("%d ", _v);

    for (int i=1; i<=v; i++) {
        if (graph[_v][i] == true && !visited[i])
            doDFS(i);
    }
}

void doBFS(int _v)
{
    visited[_v] = true;
    printf("%d ", _v);
    q.push(_v);

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        for (int i=1; i<=v; i++) {
            if(graph[vertex][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
                printf("%d ", i);
            }
        }
    }
    printf("\n");
}

int main()
{
    scanf("%d %d %d", &v, &e, &start);

    /*
     * Generate graph
     */
    for (int i=0; i<e; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        graph[s][e] = graph[e][s] = true;
    }

    doDFS(start);
    printf("\n");

    memset(visited, 0, sizeof(visited));
    
    doBFS(start);

    return 0;
}
