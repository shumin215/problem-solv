#include <iostream>
#include <cstdio>
#include <algorithm>
#include <climits>

using namespace std;

constexpr int MAX = 100000 + 1;
constexpr int MAX_NODE = MAX * 4;

int N, M;
int arr[MAX];

struct SegTree
{
    // [0] = max, [1] = min
    int tree[MAX_NODE][2];

    void init(int s, int e, int node) {
        if (s == e) {
            tree[node][0] = tree[node][1] = arr[s];
            return;
        }

        int left = node * 2, right = left + 1, mid = (s + e) / 2;

        init(s, mid, left);
        init(mid + 1, e, right);

        tree[node][0] = max(tree[left][0], tree[right][0]);
        tree[node][1] = min(tree[left][1], tree[right][1]);
    }

    int queryMax(int s, int e, int qs, int qe, int node) {
        if (e < qs || qe < s) {
            return 0;
        }
        if (qs <= s && e <= qe) {
            return tree[node][0];
        }
        int mid = (s + e) / 2;

        int left = queryMax(s, mid, qs, qe, node * 2);
        int right = queryMax(mid + 1, e, qs, qe, node * 2 + 1);

        return max(left, right);
    }
    int queryMin(int s, int e, int qs, int qe, int node) {
        if (e < qs || qe < s) {
            return INT_MAX;
        }
        if (qs <= s && e <= qe) {
            return tree[node][1];
        }
        int mid = (s + e) / 2;

        int left = queryMin(s, mid, qs, qe, node * 2);
        int right = queryMin(mid + 1, e, qs, qe, node * 2 + 1);

        return min(left, right);
    }
};

SegTree st;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    st.init(1, N, 1);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        int max_num = st.queryMax(1, N, a, b, 1);
        int min_num = st.queryMin(1, N, a, b, 1);
        printf("%d %d\n", min_num, max_num);
    }

    return 0;
}
