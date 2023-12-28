#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

constexpr int MAX = 1000000 + 1;

int N, M;
int arr[MAX];
int ans;

bool isValid(int mid)
{
    int ret = false;
    long long sum = 0;

    for (int i=0; i<N; i++) {
        if (arr[i] > mid)
            sum += arr[i] - mid;

        if (sum >= M) {
            ret = true;
            break;
        }
    }

    return ret;
}

void doBS()
{
    int left = 0, right = INT_MAX;

    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (isValid(mid)) {
            ans = mid;
            left = mid;
        } else {
            right = mid;
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    freopen("input.txt", "r", stdin);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    doBS();

    printf("%d\n", ans);

    return 0;
}
