#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge
{
public:
    Edge(int _s, int _d, int _w): s(_s), d(_d), w(_w) {}

    int s, d, w;
};

const int MAX = 1000+1;
int N, M;
vector<Edge> edge_list;
int gtable[MAX];
int resource = 0;

int getGroup(int v)
{
    if (v == gtable[v]) {
        return v;
    } else {
        gtable[v] = getGroup(gtable[v]);
        return gtable[v];
    }
}

bool isDiffEdge(int src, int dst)
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

    if (s_g != d_g)
        gtable[s_g] = d_g;
}

void doMST()
{
    int edge_cnt = 0;
    for (int i=0; i<edge_list.size(); i++) {
        Edge cur_e = edge_list[i];
        if (isDiffEdge(cur_e.s, cur_e.d)) {
            resource += cur_e.w; 
            edge_cnt++;

            updateGtable(cur_e.s, cur_e.d);

            if (edge_cnt == N + 1)
                return;
        }
    }
}

bool cmp(Edge e1, Edge e2)
{
    if (e1.w == e2.w)
        return e1.s < e2.s;
    else
        return e1.w < e2.w;
}

int main()
{
    cin >> N >> M;

    for (int i=0; i<M; i++) {
        int src, dst, weight;
        cin >> src >> dst >> weight;
        edge_list.push_back({src, dst, weight});
    }

    // Initialize gorup table
    for (int i=1; i<=N; i++) {
        gtable[i] = i;
    }

    // Sort edge list in lower weight order
    sort(edge_list.begin(), edge_list.end(), cmp);

    doMST();

    printf("%d\n", resource);

    return 0;
}