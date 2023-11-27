#include <iostream>
#include <queue>
#define MAX 20001
#define INF 9999999

using namespace std;

int dist[MAX];
// {destination, distance}
vector<pair<int, int>> edge_list[MAX];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

int V, E;

void doDijkstra(int start)
{
    pq.push({0, start});
    dist[start] = 0;

    while(!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_v = pq.top().second;
        pq.pop();

        if (dist[cur_v] < cur_dist)
            continue;

        for (auto e: edge_list[cur_v]) {
            int dst = e.first;
            int local_dist = e.second;

            if (dist[dst] > dist[cur_v] + local_dist) {
                dist[dst] = dist[cur_v] + local_dist;
                pq.push({dist[dst], dst});
            }
        }
    }
}

int main()
{
    cin >> V >> E;
    int start;
    cin >> start;

    for (int i=0; i<E; i++) {
        int src, dst, dist;
        cin >> src >> dst >> dist;
        edge_list[src].push_back({dst, dist});
    }

    for (int i=1; i<=V; i++)
        dist[i] = INF;

    doDijkstra(start);

    for (int i=1; i<=V; i++) {
        if (dist[i] == INF)
            cout << "INF\n";
        else
            cout << dist[i] << "\n";
    }

    return 0;
}
