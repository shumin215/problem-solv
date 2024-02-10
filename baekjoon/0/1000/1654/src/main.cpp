#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
using LL = long long;

constexpr int MAX = 10000+1;
int K, N;
LL lane[MAX];

bool isValid(LL size)
{
    LL lane_cnt = 0;
    bool ret = false;

    for (int i = 0; i < K; i++) {
        lane_cnt += lane[i] / size;
    }

    ret = (lane_cnt >= N) ? true : false;

    return ret;
}

void doBS(LL low, LL high)
{
    LL ans = 0;
    while(low <= high) {
        LL mid = (low + high) / 2;

        if (isValid(mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%lld\n", ans);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif
    cin >> K >> N;

    for (int i = 0; i < K; i++) {
        cin >> lane[i];
    }

    LL low = 1;
    LL high = *max_element(lane, lane+K);

    doBS(low, high);

    return 0;
}
