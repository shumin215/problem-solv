#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1000+1;
int N;
int res_map[MAX][MAX];
int gtable[MAX];

class Edge
{
public:
    Edge(int _s, int _d, int _r): s(_s), d(_d), r(_r) {}
    int s, d, r;
};

long long total_res = 0;
vector<Edge> edge_list;

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
            edge_cnt++;
            total_res += cur_edge.r;
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
    cin >> N;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> res_map[i][j];
        }
    }

    // Initialize gtable
    for (int i=0; i<N; i++) {
        gtable[i] = i;
    }

    // Make edge list
    for (int i=0; i<N; i++)
        for (int j=i; j<N; j++) {
            if (i != j) {
                edge_list.push_back({i, j, res_map[i][j]});
            }
        }
    
    // Sort edge list in lower resource order
    sort(edge_list.begin(), edge_list.end(), cmp);

    // Do MST
    doMST();

    printf("%lld\n", total_res);

    return 0;
}
