#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define MAX 101

using namespace std;

class EdgeInfo
{
public:
    EdgeInfo(int _s, int _d, float _dist): s(_s), d(_d), dist(_dist) {}
    int s, d;
    float dist;
};

pair<float, float> coord[MAX];
vector<EdgeInfo> edge_list;
int ptable[MAX];
float ans;
int N;

void getDist(void)
{
    for (int i=0; i<N; i++)
        for (int j=i+1; j<N; j++) {
            float res = sqrt(pow(coord[i].first - coord[j].first, 2) + pow(coord[i].second - coord[j].second, 2));
            edge_list.push_back(EdgeInfo(i, j, res));
        }
}

int getParent(int vertex)
{
    if (vertex == ptable[vertex])
        return vertex;
    else {
        ptable[vertex] = getParent(ptable[vertex]);
        return ptable[vertex];
    }
}

bool isDiffParent (int s, int d)
{
    int s_g = getParent(s);
    int d_g = getParent(d);

    if (s_g != d_g)
        return true;
    else
        return false;
}

void updateParent(int s, int d)
{
    int s_g = getParent(s);
    int d_g = getParent(d);

    if (s_g != d_g) {
        ptable[s_g] = d_g;
    }
}

void doMST(void)
{
    int edge_cnt = 0;
    for (auto i=0; i<(int)edge_list.size(); i++) {
        EdgeInfo e = edge_list[i];

        if (isDiffParent(e.s, e.d)) {
            ans += e.dist;
            edge_cnt++;

            updateParent(e.s, e.d);

            if (edge_cnt == N + 1)
                return;
        }
    }
}

bool cmp (EdgeInfo e1, EdgeInfo e2)
{
    if (e1.dist == e2.dist)
        return e1.s < e2.s;
    else
        return e1.dist < e2.dist;
}

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        float a, b;
        cin >> a >> b;
        coord[i] = {a, b};
    }

    for (int i=0; i<=N; i++)
        ptable[i] = i;

    getDist();

    sort(edge_list.begin(), edge_list.end(), cmp);

    doMST();

    cout << fixed;
    cout.precision(2);
    cout << ans << endl;

    return 0;
}
