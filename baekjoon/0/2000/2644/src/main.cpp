#include <iostream>
#include <queue>
#define MAX 101

using namespace std;

int N;
bool cptable[MAX][MAX];
int rel_table[MAX];
bool visited[MAX];
queue<int> q;
int result = -1;

void doBFS(int src, int dst)
{
    q.push(src);
    visited[src] = true;

    while(!q.empty()) {
        int base = q.front();
        q.pop();
        
        for (int i=1; i<=N; i++) {
            if (cptable[base][i] && !visited[i]) {
                rel_table[i] = rel_table[base] + 1;
                q.push(i);
                visited[i] = true;

                if (i == dst) {
                    result = rel_table[i];
                    return;
                }
            }
        }
    }
}

int main()
{
    cin >> N;

    int a, b;
    cin >> a >> b;

    int num;
    cin >> num;

    for (int i=1; i<=num; i++) {
        int parent, child;
        cin >> parent >> child;

        cptable[child][parent] = true;
        cptable[parent][child] = true;
    }

    doBFS(a, b);

    cout << result << "\n";

    return 0;
}
