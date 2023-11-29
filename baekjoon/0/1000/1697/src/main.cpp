#include <iostream>
#include <queue>
#include <climits>

using namespace std;

const int MAX = 100000+1;
int N, K;
int min_time = INT_MAX;
queue<pair<int, int>> q;
bool visited[MAX];

void doBFS(int idx, int time)
{
    q.push({idx, time});
    visited[idx] = true;

    while(!q.empty()) {
        int cur_idx = q.front().first;
        int cur_time = q.front().second;
        q.pop();

        if (cur_idx == K) {
            if (min_time > cur_time) {
                min_time = cur_time;
            }

            return;
        }

        // x2
        if (cur_idx * 2 <= 100000 && !visited[cur_idx * 2]) {
            q.push({cur_idx * 2, cur_time + 1});
            visited[cur_idx * 2] = true;
        }

        // +1
        if (cur_idx + 1 <= 100000 && !visited[cur_idx + 1]) {
            q.push({cur_idx + 1, cur_time + 1});
            visited[cur_idx + 1] = true;
        }

        // -1
        if (cur_idx - 1 >= 0 && !visited[cur_idx - 1]) {
            q.push({cur_idx - 1, cur_time + 1});
            visited[cur_idx - 1] = true;
        }
    }

}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> K;

    doBFS(N, 0);

    printf("%d\n", min_time);

    return 0;
}
