#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 9999999;
const int MAX = 20000+1;
int V, E, start;

/**
 * Edge List
 * 
 * | Src | Dest | Dist |
 * | 0   | 2    | 12   |
 * | 1   | 0    | 4    |
 * | ... | ...  | ...  |
*/
vector<pair<int, int>> edge_list[MAX];

/**
 * This is distance table
*/
int dist_table[MAX];

/**
 * <Type, Container style, Order>
 * pair<Distance, Destination>
 * pq is used for ordering distances of next vertex in greater order.
 * It contains next vertex connected to current vertex.
*/
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

void doDijkstra(int v)
{
    // Initial setting to push start vertex and update dist_table
    pq.push({0, v});
    dist_table[v] = 0;

    // Keep popping by the end of tracking vertex
    while(!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_v = pq.top().second;
        pq.pop();

        // Lookup edges connected to current vertex
        for (auto edge: edge_list[cur_v]) {
            int n_dst = edge.first;
            int n_dist = edge.second;

            // If another path is shorter than previous one, update it
            if (dist_table[n_dst] > dist_table[cur_v] + n_dist) {
                dist_table[n_dst] = dist_table[cur_v] + n_dist;
                pq.push({dist_table[n_dst], n_dst});
            }
        }
    }
}

int main()
{
    cin >> V >> E;
    cin >> start;

    for (int i=1; i<=E; i++) {
        int src, dst, dist;
        cin >> src >> dst >> dist;
        edge_list[src].push_back({dst, dist});
    }

    for (int i=1; i<=V; i++) {
        dist_table[i] = INF;
    }

    doDijkstra(start);

    for (int i=1; i<=V; i++) {
        if (dist_table[i] == INF) {
            printf("INF\n");
        } else {
            printf("%d\n", dist_table[i]);
        }
    }

    return 0;
}