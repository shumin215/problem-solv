/**
 *  1. 시간복잡도
 *  - O()
 *  - N: 600
 *  2. Algorithm
 *  - Dijkstra로 단순하게 처리
 */
#include <vector>
#include <cassert>
#include <cstring>
#include <unordered_map>
#include <climits>
#include <queue>

using namespace std;

struct Edge
{
    int id, dist;
    bool operator > (const Edge &rhs) const {
        if (dist != rhs.dist)
            return dist > rhs.dist;
        else
            return id > rhs.dist;
    }
};

constexpr int MAX = 600+1;
constexpr int INF = INT_MAX;
vector<Edge> edge_list[MAX];
// DEBUG: reverse edge graph를 따로 만들어서 왕복 거리를 빠르게 구해준다.
vector<Edge> edge_list_rev[MAX];
unordered_map<int, int> hmap;
int id;
int dtable_out[MAX];
int dtable_in[MAX];
int dtable[MAX];
bool visited[MAX];
priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

int init(int mN, int sCity[], int eCity[], int mCost[]) 
{
    id = 0;
    hmap.clear();
    for (int i = 0; i < MAX; i++) {
        edge_list[i].clear();
        edge_list_rev[i].clear();
    }

    for (int i = 0; i < mN; i++) {
        if (hmap.find(sCity[i]) == hmap.end()) {
            hmap[sCity[i]] = id++;
        }
        if (hmap.find(eCity[i]) == hmap.end()) {
            hmap[eCity[i]] = id++;
        }
        int sid = hmap[sCity[i]];
        int eid = hmap[eCity[i]];

        edge_list[sid].push_back({eid, mCost[i]});
        edge_list_rev[eid].push_back({sid, mCost[i]});
    }
    return id;
}
 
// Maximum 50
void add(int sCity, int eCity, int mCost) 
{
    int sid = hmap[sCity];
    int eid = hmap[eCity];
    edge_list[sid].push_back({eid, mCost});
    edge_list_rev[eid].push_back({sid, mCost});
}
 
 // Maximum 50
 // 우선 hub에서 모든 node에 대해서 distance를 구한다.
 // 다음 hub를 제외한 node에서 hub까지의 거리를 구한다.
int doDijkstra(int start, bool forward)
{
    for (int i = 0; i < id; i++) {
        dtable[i] = INF;
        visited[i] = false;
    }
    auto &list = (forward) ? edge_list : edge_list_rev;
    int ret = 0;
    pq = {};
    dtable[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        auto cur_v = pq.top();
        pq.pop();

        if (visited[cur_v.id])
            continue;
        visited[cur_v.id] = true;
        // DEBUG: 이미 방문한 곳의 거리는 더하지 않음
        ret += cur_v.dist;

        for (auto &v : list[cur_v.id]) {
            if (dtable[v.id] > dtable[cur_v.id] + v.dist) {
                dtable[v.id] = dtable[cur_v.id] + v.dist;

                pq.push({v.id, dtable[v.id]});
            }
        }
    }
    return ret;
}

int cost(int mHub) 
{
    int ret = doDijkstra(hmap[mHub], true) + doDijkstra(hmap[mHub], false);

    return ret;
}
