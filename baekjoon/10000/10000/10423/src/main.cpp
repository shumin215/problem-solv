#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int src, dst, dist;
    bool operator < (const Edge &rhs) const {
        if (dist != rhs.dist)
            return dist < rhs.dist;
        else if (src != rhs.src)
            return src < rhs.src;
        else
            return dst < rhs.dst;
    }
};

constexpr int MAX = 1000+1;
int N, M, K;
vector<Edge> edge_list;
bool power[MAX];
int gtable[MAX];

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif

    cin >> N >> M >> K;
    
    for (int i = 0; i < K; i++) {
        int num;
        cin >> num;
        power[num] = true;
    }

    for (int i = 0; i < M; i++) {
        int src, dst, dist;
        cin >> src >> dst >> dist;
        edge_list.push_back({src, dst, dist});
    }

    for (int i = 0; i < N; i ++) {

    }

    sort(edge_list.begin(), edge_list.end(), less<Edge>());

    return 0;
}
