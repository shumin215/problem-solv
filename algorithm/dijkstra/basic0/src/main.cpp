/*
18_최단경로2
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

constexpr int MAX = 100000 + 1;
constexpr int INF = INT_MAX;
struct Edge
{
    int dst, dist;
    bool operator> (const Edge rhs) const {
        return dist > rhs.dist;
    }
};
int N, M;
vector<Edge> edge_list[MAX];
int dtable[MAX];
bool visited[MAX];

void doDijkstra(int start)
{
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push({ start, 0 });
    dtable[start] = 0;

    while (!pq.empty()) {
        auto cur_v = pq.top();
        pq.pop();

        if (visited[cur_v.dst])
            continue;

        visited[cur_v.dst] = true;

        for (auto edge : edge_list[cur_v.dst]) {
            if (dtable[edge.dst] > dtable[cur_v.dst] + edge.dist) {
                dtable[edge.dst] = dtable[cur_v.dst] + edge.dist;
                pq.push({ edge.dst, dtable[edge.dst] });
            }
        }
    }
}

int main() {
#ifdef _WIN32
    freopen("18.txt", "r", stdin);
#endif // _WIN32
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        int src, dst, dist;
        cin >> src >> dst >> dist;
        edge_list[src].push_back({ dst, dist });
    }

    for (int i = 1; i <= N; i++) {
        dtable[i] = INF;
    }

    doDijkstra(1);

    printf("%d\n", dtable[N]);

    return 0;
}

