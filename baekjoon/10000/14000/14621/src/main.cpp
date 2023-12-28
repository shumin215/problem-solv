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
int N, M;
char univ[MAX];
vector<Edge> edge_list;
int dist_sum = 0;
int gtable[MAX];

int getGroup(int v)
{
    if (v == gtable[v])
        return v;
    else {
        gtable[v] = getGroup(gtable[v]);
        return gtable[v];
    }
}

bool isDiffGroup(int src, int dst)
{
    int s_g = getGroup(src);
    int d_g = getGroup(dst);

    if (s_g != d_g)
        return true;
    else
        return false;
}

void updateGroup(int src, int dst)
{
    int s_g = getGroup(src);
    int d_g = getGroup(dst);

    if (s_g != d_g) {
        gtable[d_g] = s_g;
    }
}

void doMST()
{
    int edge_num = 0;
    for (auto &edge : edge_list) {
        if (univ[edge.src] == univ[edge.dst])
            continue;

        if (isDiffGroup(edge.src, edge.dst)) {
            edge_num++;
            updateGroup(edge.src, edge.dst);
            dist_sum += edge.dist;

            if (edge_num + 1 == N)
                return;
        }
    }

    dist_sum = -1;

    return;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif

    cin >> N >> M;

    for (int i=1; i<=N; i++) {
        cin >> univ[i];
    }

    for (int i=1; i<=N; i++) {
        gtable[i] = i;
    }

    for (int i=0; i<M; i++) {
        int src, dst, dist;
        cin >> src >> dst >> dist;
        edge_list.push_back({src, dst, dist});
    }

    sort(edge_list.begin(), edge_list.end(), less<Edge>());

    doMST();

    printf("%d\n", dist_sum);

    return 0;
}
