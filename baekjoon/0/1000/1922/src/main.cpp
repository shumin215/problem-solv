#include <iostream>
#include <algorithm>
#include <vector>

/*
 *  Idea
 *  1. Sort edge list in the weight order
 *  2. Select edge and update group table
 *  3. If the group ID are same, don't select the edge
 *  4. Exit if # of edges == # of vertexes + 1
 */

using namespace std;

int N, M;
int resource, edge_num;

class Edge
{
public:
    Edge(int _s, int _d, int _w): s(_s), d(_d), w(_w) {}

    int s;
    int d;
    int w;
};

vector<Edge> edge_list;


bool cmp (Edge e1, Edge e2)
{
    if (e1.w == e2.w)
        return e1.s < e2.s;
    else
        return e1.w < e2.w;
}

void updateGroupTable(int _s1, int _s2, int *group_table)
{
    int g1 = group_table[_s1];
    int g2 = group_table[_s2];
    int bigger = (g1 < g2) ? g2 : g1;
    int smaller = (g1 < g2) ? g1 : g2;

    for (int i=1; i<=N; i++) {
        if (group_table[i] == bigger)
            group_table[i] = smaller;
    }
}

void doMST(int *group_table)
{
    for (auto i=0; i<M; i++) {
        Edge e = edge_list[i];
        if (group_table[e.s] != group_table[e.d]) {
            resource += e.w;
            edge_num++;
            updateGroupTable(e.s, e.d, group_table);

            if (edge_num == N + 1)
                return;
        }
    }
}

int main()
{
    cin >> N;
    cin >> M;
    int group_table[N+1];

    for (int i=1; i<=N; i++)
        group_table[i] = i;

    for (int i=0; i<M; i++) {
        int s, d, w;
        cin >> s >> d >> w;
        edge_list.push_back(Edge(s, d, w));
    }

    sort(edge_list.begin(), edge_list.end(), cmp);

    doMST(group_table);

    printf("%d\n", resource);

    return 0;
}
