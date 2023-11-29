#include <iostream>
#include <queue>

using namespace std;

const int MAX = 300000+1;
const int INF = 99999999;
int N, M, K, X;
priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
int dist_map[MAX];
vector<pair<int, int>> edge_list[MAX];

void doDijkstra(int start)
{
    pq.push({0, start});
    dist_map[start] = 0;

    while(!pq.empty()) {
        int cur_v = pq.top().second;
        pq.pop();

        for (auto edge: edge_list[cur_v]) {
            int n_v = edge.second;
            int n_dist = edge.first;

            if (dist_map[n_v] > dist_map[cur_v] + n_dist) {
                dist_map[n_v] = dist_map[cur_v] + n_dist;

                pq.push({dist_map[n_v], n_v});
            }
        }
    }
}

int main()
{
    cin >> N >> M >> K >> X;

    for (int i=0; i<M; i++) {
        int src, dst;
        cin >> src >> dst;
        edge_list[src].push_back({1, dst});
    }

    for (int i=1; i<=N; i++) {
        dist_map[i] = INF;
    }

    doDijkstra(X);

    int cnt = 0;
    for (int i=1; i<=N; i++) {
        if (dist_map[i] == K) {
            cnt++;
            printf("%d\n", i);
        }
    }

    if (cnt == 0)
        printf("-1\n");

    return 0;
}
