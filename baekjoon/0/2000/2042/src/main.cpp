#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

constexpr int MAX = 1000000 + 1;
constexpr int MAX_NODE = MAX * 4;
using ll = long long;

int N, M, K;
ll arr[MAX];

struct SegTree
{
    ll tree[MAX_NODE];
    void init(ll s, ll e, ll node)
    {
        if (s == e) {
            tree[node] = arr[s];
            return;
        }

        ll left = node * 2, right = left + 1, mid = (s + e) / 2;
        init(s, mid, left);
        init(mid + 1, e, right);

        tree[node] = tree[left] + tree[right];
    }
    void update(ll s, ll e, ll node, ll target)
    {
        if (s >= e) {
            tree[node] = arr[target];
            assert(s == target);
            return;
        }

        ll left = node * 2, right = left + 1, mid = (s + e) / 2;
        if (target <= mid)
            update(s, mid, left, target);
        else
            update(mid + 1, e, right, target);
        
        tree[node] = tree[left] + tree[right];
    }
    ll querySum(ll s, ll e, ll sq, ll eq, ll node)
    {
        // 1. Tree 범위와 query 범위랑 겹치지 않는 경우
        if (e < sq || eq < s) {
            return 0;
        }
        // 2. Tree 범위가 query 범위에 완전히 포함되는 경우
        if (sq <= s && e <= eq) {
            return tree[node];
        }
        // 3. 부분적으로 겹치는 경우 
        ll mid = (s + e) / 2;
        
        ll left = querySum(s, mid, sq, eq, node * 2);
        ll right = querySum(mid + 1, e, sq, eq, node * 2 + 1);
        return left + right;
    }
};

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    SegTree st;
    st.init(1, N, 1);

    for (int i = 0; i < M + K; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            arr[b] = c;
            st.update(1, N, 1, b);
        } else if (a == 2) {
            ll res = st.querySum(1, N, b, c, 1);
            printf("%lld\n", res);
        } else {
            assert(false);
        }
    }

    return 0;
}
