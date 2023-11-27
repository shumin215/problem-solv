#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#define MAX 100000

using namespace std;

class Edge
{
public:
    Edge(int _src, int _dst, int _w): src(_src), dst(_dst), w(_w) {}
    int src;
    int dst;
    int w;
};

int N;
vector<Edge> edge_list;
vector<pair<int, int>> X;
vector<pair<int, int>> Y;
vector<pair<int, int>> Z;
vector<int> list;
bool visited[MAX];
int total_resource;
int g_table[MAX];

/*
int getDist(int src_idx, int dst_idx)
{
    int x_diff = abs(X[src_idx] - X[dst_idx]);
    int y_diff = abs(Y[src_idx] - Y[dst_idx]);
    int z_diff = abs(Z[src_idx] - Z[dst_idx]);

    int ret = min(x_diff, y_diff);
    ret = min(ret, z_diff);

    return ret;
}

void getEdgeList(int idx, int cnt)
{
    if (cnt == 2) {
        assert(list.size() == 2);
        int src_idx = list[0];
        int dst_idx = list[1];
        int dist = getDist(src_idx, dst_idx);
        edge_list.push_back({src_idx, dst_idx, dist});
        return;
    }

    for (int i=idx; i<N; i++) {
        if (visited[i])
            continue;

        visited[i] = true;
        list.push_back(i);
        getEdgeList(i, cnt+1);
        list.pop_back();
        visited[i] = false;
    }
}
*/

bool cmp(Edge e1, Edge e2)
{
    if (e1.w == e2.w)
        return e1.src < e2.src;
    else
        return e1.w < e2.w;
}

int getGrp(int val)
{
    if (val == g_table[val])
        return val;
    else {
        g_table[val] = getGrp(g_table[val]);
        return g_table[val];
    }
}

bool isSameGrp(int src, int dst)
{
    int src_g = getGrp(src);
    int dst_g = getGrp(dst);

    if (src_g == dst_g)
        return true;
    else
        return false;
}

void updateGtable(int src, int dst)
{
    int src_g = getGrp(src);
    int dst_g = getGrp(dst);

    if (src_g != dst_g) {
        g_table[src_g] = dst_g;
    }
}

void doMST(void)
{
    int edge_cnt = 0;
    for (int i=0; i<edge_list.size(); i++) {
        Edge e = edge_list[i];

        if (!isSameGrp(e.src, e.dst)) {
            updateGtable(e.src, e.dst);
            edge_cnt++;
            total_resource += e.w;

            if (edge_cnt == N - 1)
                return;
        }
    }
}

void print(void)
{
    cout << "################# Edge List ###################\n";
    for (int i=0; i<edge_list.size(); i++) {
        Edge e = edge_list[i];
        printf("[%d]-----(%d)-----[%d]\n", e.src, e.w, e.dst);
    }
}

void getOptEdgeList(void)
{
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    sort(Z.begin(), Z.end());

    for (int i=0; i<N-1; i++) {
        int x_diff = X[i+1].first - X[i].first;
        int y_diff = Y[i+1].first - Y[i].first;
        int z_diff = Z[i+1].first - Z[i].first;

        edge_list.push_back({X[i].second, X[i+1].second, x_diff});
        edge_list.push_back({Y[i].second, Y[i+1].second, y_diff});
        edge_list.push_back({Z[i].second, Z[i+1].second, z_diff});
    }
}

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        X.push_back({x, i});
        Y.push_back({y, i});
        Z.push_back({z, i});
        g_table[i] = i;
    }

//    getEdgeList(0, 0);
    getOptEdgeList();

    sort(edge_list.begin(), edge_list.end(), cmp);

#ifdef DEBUG
    print();
#endif

    doMST();

    cout << total_resource << "\n";

    return 0;
}
