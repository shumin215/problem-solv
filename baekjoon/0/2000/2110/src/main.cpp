#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAX = 200000+1;
int N, C;
vector<int> list;

bool isValid(int interval)
{
    bool ret = false;
    int cnt = 1;
    int dist = 0;

    for (int i = 0; i < (int)list.size() - 1; i++) {
        dist += list[i+1] - list[i];
        if (dist >= interval) {
            dist = 0;
            cnt++;
        }
    }

    ret = (cnt >= C) ? true : false;

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
    cin >> N >> C;

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        list.push_back(num);
    }

    sort(list.begin(), list.end(), less<int>());

    int low = 1;
    int high = *prev(list.end(), 1) - *list.begin();
    doBS(low, high);

    return 0;
}
