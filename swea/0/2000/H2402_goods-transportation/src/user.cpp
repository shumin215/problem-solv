/**
 *  Algorithm
 *  - N: 1000
 *  - K: 4000 -> 6000
 */

#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

struct Node
{
    int id, w;
    bool operator < (const Node& rhs) const {
        if (w != rhs.w)
            return w < rhs.w;
        else
            return id < rhs.id;
    }
};

constexpr int MAX = 1000+1;
int N, K;
vector<Node> edge_list[MAX];
int wtable[MAX];
bool visited[MAX];
priority_queue<Node, vector<Node>, less<Node>> pq;

void init(int mN, int mK, int sCity[], int eCity[], int mLimit[]) 
{
    N = mN;
    K = mK;
    for (int i = 0; i < N; i++)
        edge_list[i].clear();

    for (int i = 0; i < K; i++) {
        edge_list[sCity[i]].push_back({eCity[i], mLimit[i]});
    }
    return;
}
 
// Maximum 2,000
// Add each edge to each source ID's vector
void add(int sCity, int eCity, int mLimit) 
{
    edge_list[sCity].push_back({eCity, mLimit});
    return;
}
 
// Maximum 300
/**
 *  - Do dijkstra 
 *  - 
 */
int calculate(int sCity, int eCity) 
{
    int ret = -1;
    memset(visited, 0, sizeof(visited));
    memset(wtable, 0, sizeof(wtable));

    pq = {};
    pq.push({sCity, INT_MAX});

    while (!pq.empty()) {
        auto cur_v = pq.top();
        pq.pop();

        if (cur_v.id == eCity) {
            ret = cur_v.w;
            break;
        }

        if (visited[cur_v.id])
            continue;
        visited[cur_v.id] = true;

        for (auto &edge : edge_list[cur_v.id]) {
            if (wtable[edge.id] < min(cur_v.w, edge.w)) {
                wtable[edge.id] = min(cur_v.w, edge.w);

                pq.push({edge.id, wtable[edge.id]});
            }
        }
    }

    return ret;
}