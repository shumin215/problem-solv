#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using LL = long long;
using namespace std;

vector<int> list;
int N;

void doBS(int low, int high)
{
    int ans0 = 0, ans1 = 0;
    LL min_val = INT_MAX;
    while(low < high) {
        LL sum = list[low] + list[high];
        if (min_val > abs(sum)) {
            min_val = abs(sum);
            ans0 = list[low];
            ans1 = list[high];

            if (sum == 0)
                break;
        }

        if (sum < 0) {
            low++;
        } else {
            high--;
        }
    }

    printf("%d %d\n", ans0, ans1);
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
        int num;
        cin >> num;
        list.push_back(num);
    }
    sort(list.begin(), list.end());

    int low = 0;
    int high = N - 1;

    doBS(low, high);

    return 0;
}
