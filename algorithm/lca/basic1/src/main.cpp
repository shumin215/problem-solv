#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
 
const int LM = 300005;
const int M = 300;    // sqrt(최대깊이)
/*
* 이 문제에서는 결과론적으로 깊이가 더 작기때문에 M을 작게 설정
* 이상적으로는 sqrt(300,000)이 맞음
*/
 
int parent[LM], parentM[LM], depth[LM];
vector<int> adj[LM];
bool visit[LM];
 
int getParentM(int v) {
    for (int i = 0; i < M; i++) {
        if (v == 1) break;
        v = parent[v];
    }
    return v;
}
 
// O(N * M)
void dfs(int v) {
    visit[v] = 1;
    for (int u : adj[v]) {
        if (visit[u]) continue;
        parent[u] = v;
        parentM[u] = getParentM(u);
        depth[u] = depth[v] + 1;
        dfs(u);
    }
}
 
int que[LM];
int head, tail;
void bfs(int start) {
    que[tail++] = start;
    visit[start] = 1;
 
    while (head < tail) {
        int pid = que[head++];
        for (int cid : adj[pid]) {
            if (visit[cid]) continue;
 
            parent[cid] = pid;
            parentM[cid] = getParentM(cid);
            depth[cid] = depth[pid] + 1;
 
            que[tail++] = cid;
            visit[cid] = 1;
        }
    }
}
 
// O(D)
void lca_depth(int a, int b) {
    // 0. a를 깊은 노드로 만든다.
    if (depth[a] < depth[b]) swap(a, b);
 
    // 1. a를 올려서 깊이를 맞춘다.
    while (depth[a] > depth[b]) a = parent[a];
 
    // 2. 같아질때까지 같이 올라간다.
    while (a != b) a = parent[a], b = parent[b];
 
    printf("%d\n", a);
}
 
void lca_sqrt_depth(int a, int b) {
    // 0. a를 깊은 노드로 만든다.
    if (depth[a] < depth[b]) swap(a, b);
 
    // 1. a를 올려서 깊이를 맞춘다.
    while (depth[a] - M >= depth[b]) a = parentM[a];
    while (depth[a] > depth[b]) a = parent[a];
 
    // 2. 같아질때까지 같이 올라간다.
    while (parentM[a] != parentM[b]) a = parentM[a], b = parentM[b];
    while (a != b) a = parent[a], b = parent[b];
 
    printf("%d\n", a);
}
 
int main() {
#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif
    int n, q;
    int a, b;
    scanf("%d", &n);
    for(int i=1; i<n; i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    //dfs(1);
    bfs(1);
 
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &a, &b);
        //lca_depth(a, b);
        lca_sqrt_depth(a, b);
    }
    return 0;
}