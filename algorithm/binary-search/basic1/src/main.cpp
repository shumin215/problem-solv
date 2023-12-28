/*
 *  Binary Search Basic Code
 */
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

using LL = long long;
constexpr int MAX = 100000 + 1;
int N, M;
int arr[MAX];

bool isValid(LL grp_size, int target)
{
    bool ret = false;

    LL sum = 0;
    int num_grp = 1;
    for (int i = 0; i < N; i++) {
        sum += arr[i];

        if (sum > grp_size) {
            sum = arr[i];
            num_grp++;
        }
    }

    // 만약 그룹 수가 목표값보다 적거나 같은 경우, 그룹 수를 늘리기 위해선 그룹 크기는 작아져야 함
    // 정답을 포함시키기 위해 = 을 포함함
    ret = (num_grp <= target) ? true : false;

    return ret;
}

void doBS(LL low, LL high, int target)
{
    LL ans = 0;
    while (low <= high) {
        LL mid = (low + high) / 2;

        // 최대 값이 "최소" 가 되도록 만들어야 하기 때문에, 작아지는 방향 <--- 으로 가야함
        if (isValid(mid, target)) {
            high = mid - 1;
            ans = mid;
        }
        else {
            low = mid + 1;
        }
    }

    printf("%lld\n", ans);
}

int main() {
#ifdef _WIN32
    freopen("input.txt", "r", stdin);
#endif // _WIN32
    cin.tie(nullptr);
    cin >> N >> M;

    int low = 0;
    LL high = 0;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        low = max(low, arr[i]);
        high += arr[i];
    }

    doBS(low, high, M);
    return 0;
}

