/*
22_구간의합
*/
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;
constexpr int MAX = 1000000 + 1;
constexpr int sq = 1024;
constexpr int mod = sq - 1;
int N, M;
int arr[MAX];
ll sum_arr[sq + 1];

void update(int idx, int val)
{
    int gidx = idx / sq;

    int prev = arr[idx];
    arr[idx] = val;
    sum_arr[gidx] += val - prev;
}

void print(int l, int r)
{
    ll ret = 0;
    // Left
    while (l <= r && l % sq != 0) {
        ret += arr[l];
        l++;
    }

    // Right
    while (l <= r && (r + 1) % sq != 0) {
        ret += arr[r];
        r--;
    }

    // Else
    while (l <= r) {
        ret += sum_arr[l / sq];
        l += sq;
    }

    printf("%lld\n", ret);
    return;
}

int main() {
#ifdef _WIN32
    freopen("input.txt", "r", stdin);
#endif // _WIN32
    cin.tie(nullptr);
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        sum_arr[i / sq] += arr[i];
    }

    cin >> M;

    while (M--) {
        int cmd;
        cin >> cmd;

        if (cmd == 1) {
            int a, b;
            cin >> a >> b;

            update(a - 1, b);
        }
        else {
            int s, e;
            cin >> s >> e;

            print(s - 1, e - 1);
        }
    }

    return 0;
}

