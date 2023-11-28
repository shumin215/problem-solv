#include <iostream>
#include <queue>

using namespace std;

const int MAX = 1000+1;

queue<int> q;
bool graph[MAX][MAX];
bool visited[MAX];
int cnt = 0;
int v, e;

void doBFS(int cur_v)
{
    q.push(cur_v);
    visited[cur_v] = true;

    while (!q.empty()) {
        int next_v = q.front();
        q.pop();

        for (int i=1; i<=v; i++) {
            if (graph[next_v][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main()
{
    cin >> v >> e;

    for (int i=0; i<e; i++) {
        int src, dst;
        cin >> src >> dst;
        graph[src][dst] = graph[dst][src] = true;
    }

    for (int i=1; i<=v; i++) {
        if (!visited[i]) {
            doBFS(i);
            cnt++;
        }
    }

    printf("%d\n", cnt);

    return 0;
}
