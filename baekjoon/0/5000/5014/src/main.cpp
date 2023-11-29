#include <iostream>
#include <climits>
#include <queue>

using namespace std;

const int MAX_FLOOR = 1000000;
int loop_floor, cur_floor, dst_floor, U, D;
int min_cnt = INT_MAX;
bool visited[MAX_FLOOR+1];
queue<pair<int, int>> q;

bool isImpossible(void)
{
    bool ret = false;

    if (U == 0 && D != 0) {
        if (cur_floor < dst_floor)
            ret = true;
    } else if (D == 0 && U != 0) {
        if (cur_floor > dst_floor)
            ret = true;
    } else if (D != 0 && U != 0) {
        if ((cur_floor + U > loop_floor) && (cur_floor - D < 1)) {
            ret = true;
        }
    }

    return ret;
}

void doBFS(int floor)
{
    q.push({floor, 0});
    visited[floor] = true;

    while(!q.empty()) {
        int cur_floor = q.front().first;
        int cur_cnt = q.front().second;
        q.pop();

        if (cur_floor == dst_floor) {
            min_cnt = cur_cnt;
            return;
        }

        // Up side
        if (cur_floor + U <= loop_floor && !visited[cur_floor + U]) {
            q.push({cur_floor + U, cur_cnt+1});
            visited[cur_floor + U] = true;
        }
        // Down side
        if (cur_floor - D >= 1 && !visited[cur_floor - D]) {
            q.push({cur_floor - D, cur_cnt+1});
            visited[cur_floor - D] = true;
        }
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> loop_floor >> cur_floor >> dst_floor >> U >> D;

    if (cur_floor == dst_floor) {
        printf("0\n");
        return 0;
    }

    if (isImpossible()) {
        printf("use the stairs\n");
        return 0;
    }

    doBFS(cur_floor);

    if (visited[dst_floor]) {
        printf("%d\n", min_cnt);
    } else {
        printf("use the stairs\n");
    }
    

    return 0;
}
