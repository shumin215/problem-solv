#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge
{
public:
    Edge(int _s, int _d, int _r): s(_s), d(_d), r(_r) {}
    int s, d, r;
};

const int MAX = 200000+1;
int N, M;
long long sum_res, total_res;
vector<Edge> edge_list;
int gtable[MAX];

int getGroup(int v)
{
    if (gtable[v] == v) {
        return v;
    } else {
        gtable[v] = getGroup(gtable[v]);
        return gtable[v];
    }
}

bool isDiffGroup(int src, int dst)
{
    int s_g = getGroup(src);
    int d_g = getGroup(dst);

    if (s_g != d_g) {
        return true;
    } else {
        return false;
    }
}

void updateGtable(int src, int dst)
{
    int s_g = getGroup(src);
    int d_g = getGroup(dst);

    if (s_g != d_g) {
        gtable[d_g] = s_g;
    }
}

void doMST()
{
    int edge_cnt = 0;

    for (int i=0; i<edge_list.size(); i++) {
        Edge cur_edge = edge_list[i];

        if (isDiffGroup(cur_edge.s, cur_edge.d)) {
            sum_res += cur_edge.r;
            edge_cnt++;

            updateGtable(cur_edge.s, cur_edge.d);

            if (edge_cnt == N + 1) {
                return;
            }
        }
    }
}

bool cmp(Edge e1, Edge e2)
{
    if (e1.r == e2.r) {
        return e1.s < e2.s;
    } else {
        return e1.r < e2.r;
    }
}

int main()
{
    while (true) {
        cin >> N >> M;

        if (N == 0 && M == 0)
            return 0;

        sum_res = total_res = 0;
        edge_list.clear();
        for (int i=0; i<N; i++) {
            gtable[i] = i;
        }

        for (int i=0; i<M; i++) {
            int src, dst, res;
            cin >> src >> dst >> res;
            edge_list.push_back({src, dst, res});
            total_res += res;
        }

        sort(edge_list.begin(), edge_list.end(), cmp);

        doMST();

        printf("%lld\n", total_res - sum_res);
    }

    return 0;
}
