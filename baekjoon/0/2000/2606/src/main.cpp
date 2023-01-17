#include <iostream>
#include <queue>
#define MAX 101

using namespace std;

int V, E;
bool graph[MAX][MAX];
bool visited[MAX];
int virus_num;
queue<int> q;

void doDFS(int _v)
{
    visited[_v] = true;
    
    for (int i=1; i<=V; i++) {
        if (graph[_v][i] && !visited[i]) {
            virus_num++;
            doDFS(i);
        }
    }
}

void doBFS(int _v)
{
    q.push(_v);
    visited[_v] = true;

    while(!q.empty()) {
        int next = q.front();
        q.pop();

        for (int i=1; i<=V; i++) {
            if (graph[next][i] && !visited[i]) {
                visited[i] = true;
                virus_num++;
                q.push(i);
            }
        }
    }
}

int main()
{
    cin >> V;
    cin >> E;

    for (int i=0; i<E; i++) {
        int s, d;
        cin >> s >> d;
        graph[s][d] = true;
        graph[d][s] = true;
    }

    doBFS(1);

    printf("%d\n", virus_num);

    return 0;
}


