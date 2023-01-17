#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_NUM 100000+1

using namespace std;

class Edge
{
public:
    Edge(int _s, int _d, int _w): s(_s), d(_d), w(_w) {}
    int s, d, w;
};

int N, M;
vector<Edge> edge_list;
int weight_sum;
int group_table[MAX_NUM];
int max_weight;

/*
 *  0. Initialize group table
 *  1. Sort edges in the weight order
 *  2. Select edge and if the groups are different
 *  3. And update group table to smaller
 */

bool cmp(Edge e1, Edge e2)
{
    if (e1.w == e2.w) {
        return e1.s < e2.s;
    } else {
        return e1.w < e2.w;
    }
}

int getParent(int v)
{
    if (v == group_table[v])
        return v;
    else {
        group_table[v] = getParent(group_table[v]);
        return group_table[v];
    }
}

void updateGT(int s, int d)
{
    int a = getParent(s);
    int b = getParent(d);

    if (a != b) {
        group_table[a] = b;
    }
}

bool isDiffParent(int s, int d)
{
    s = getParent(s);
    d = getParent(d);

    if (s != d)
        return true;
    else
        return false;
}

void doMST()
{
    int sel = 0;
    for (int i=0; i<M; i++) {
        Edge e = edge_list[i];

        if (isDiffParent(e.s, e.d)) {
            sel++;
            weight_sum += e.w;

            updateGT(e.s, e.d);

            if (max_weight < e.w)
                max_weight = e.w;

            if (sel == N + 1)
                return;
        }
    }
}

int main()
{
    cin >> N >> M;

    for (int i=1; i<=N; i++)
        group_table[i] = i;

    for (int i=0; i<M; i++) {
        int s, d, w;
        cin >> s >> d >> w;
        edge_list.push_back(Edge(s, d, w));
    }

    sort(edge_list.begin(), edge_list.end(), cmp);

    doMST();

    printf("%d\n", weight_sum - max_weight);

    return 0;
}
