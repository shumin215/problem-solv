#include <unordered_map>
#include <vector>
#include <cstring>
 
using namespace std;
 
struct Edge
{
    int id, time;
};
 
constexpr int MAX = 10000 + 1;
int id;
unordered_map<int, int> hmap;
vector<Edge> edge_list[MAX];
bool visited[MAX];
 
void init(int mDevice)
{
    for (int i = 0; i < MAX; i++) {
        edge_list[i].clear();
    }
    hmap.clear();
    id = 1;
 
    hmap[mDevice] = id;
    id++;
 
    return;
}
 
// 10,000회 이하
void connect(int mOldDevice, int mNewDevice, int mLatency)
{
    int old_id = hmap[mOldDevice];
    hmap[mNewDevice] = id;
    id++;
    int new_id = hmap[mNewDevice];
     
    edge_list[old_id].push_back({ new_id, mLatency });
    edge_list[new_id].push_back({ old_id, mLatency });
 
    return;
}
 
void doDFS(int src, int dst, int lat, int &res)
{
    int size = edge_list[src].size();
    for (int i = 0; i < size; i++) {
        int next_device = edge_list[src][i].id;
        int lat_sum = edge_list[src][i].time + lat;
 
        if (visited[next_device])
            continue;
 
        if (next_device == dst) {
            res = lat_sum;
            return;
        }
 
        visited[next_device] = true;
        doDFS(next_device, dst, lat_sum, res);
        visited[next_device] = false;
    }
}
 
// 1,000회 이하
int measure(int mDevice1, int mDevice2)
{
    memset(visited, 0, sizeof(visited));
    int src_id = hmap[mDevice1];
    int dst_id = hmap[mDevice2];
    visited[src_id] = true;
    int lat = 0;
    doDFS(src_id, dst_id, 0, lat);
 
    return lat;
}
 
void getLatency(int src, int lat, int &max_lat)
{
    if (max_lat < lat)
        max_lat = lat;
 
    int size = edge_list[src].size();
 
    for (int i = 0; i < size; i++) {
        int next_id = edge_list[src][i].id;
        int next_lat = edge_list[src][i].time + lat;
 
        if (visited[next_id])
            continue;
 
        visited[next_id] = true;
        getLatency(next_id, next_lat, max_lat);
        visited[next_id] = false;
    }
}
 
// 100회 이하
int test(int mDevice)
{
    int src_id = hmap[mDevice];
    memset(visited, 0, sizeof(visited));
    int max1_lat = 0, max2_lat = 0;
    visited[src_id] = true;
 
    for (auto e : edge_list[src_id]) {
        int lat = 0;
        visited[e.id] = true;
        getLatency(e.id, e.time, lat);
 
        if (max1_lat < lat) {
            max2_lat = max1_lat;
            max1_lat = lat;
        }
        else if (max2_lat < lat) {
            max2_lat = lat;
        }
    }
 
    int ret = max1_lat + max2_lat;
 
    return ret;
}