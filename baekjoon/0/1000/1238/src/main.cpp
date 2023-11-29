#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Goal is to get minimum distance between specific vertex (X).
 * 
 * To achieve the minimum distance, we can use two graphs.
 * 1) Forward direction: minimum distance of each vertex from X
 * 2) Reverse direction, minimum distance of each vertex to X
 * 
 * And then, results in minimum distance of sum of two directions.
*/

const int INF = 9999999;
const int MAX = 1000+1;
int N, M, X;
int for_dist_table[MAX], rev_dist_table[MAX];
priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
vector<pair<int, int>> for_edge_list[MAX], rev_edge_list[MAX];

void doDijkstra(bool reverse, int start)
{
    int *dist_table = nullptr;
    vector<pair<int, int>> *edge_list;

    if (!reverse) {
        dist_table = for_dist_table;
        edge_list = for_edge_list;
    } else {
        dist_table = rev_dist_table;
        edge_list = rev_edge_list;
    }

    pq.push({0, start});
    dist_table[start] = 0;
    
    while(!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_v = pq.top().second;
        pq.pop();

        for (auto edge: edge_list[cur_v]) {
            int n_v = edge.first;
            int n_dist = edge.second;

            if (dist_table[n_v] > dist_table[cur_v] + n_dist) {
                dist_table[n_v] = dist_table[cur_v] + n_dist;
                pq.push({dist_table[n_v], n_v});
            }
        }
    }
}

int main()
{
    cin >> N >> M >> X;
    int max_dist = 0;

    for (int i=1; i<=M; i++) {
        int src, dst, dist;
        cin >> src >> dst >> dist;
        for_edge_list[src].push_back({dst, dist});
        rev_edge_list[dst].push_back({src, dist});
    }

    // Initialize dist_table
    for (int i=1; i<=N; i++) {
        for_dist_table[i] = INF;
        rev_dist_table[i] = INF;
    }

    // To X
    doDijkstra(true, X);

    // From X
    doDijkstra(false, X);

    for (int i=1; i<=N; i++) {
        if (max_dist < for_dist_table[i] + rev_dist_table[i]) {
            max_dist = for_dist_table[i] + rev_dist_table[i];
        }
    }

    printf("%d\n", max_dist);

    return 0;
}
