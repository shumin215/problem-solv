#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
using LL = long long;

constexpr int MAX = 10000+1;
int N, M;
int arr[MAX];

bool isValid(int budget)
{
    LL sum = 0;
    for (int i = 0; i < N; i++) {
        sum += min(arr[i], budget);
    }

    bool ret = (sum <= M) ? true : false;
    return ret;
}

void doBS(int low, int high)
{
    int ans = 0;
    while(low <= high) {
        int mid = (low + high) / 2;

        if (isValid(mid)) {
            low = mid + 1;
            ans = mid;
        } else {
            high = mid - 1;
        }
    }
    printf("%d\n", ans);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    cin >> M;

    int low = 1;
    int high = *max_element(arr, arr+N);

    doBS(low, high);

    return 0;
}
