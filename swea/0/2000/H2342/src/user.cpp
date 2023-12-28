#include <queue>
#include <algorithm>
#include <cstring>
#include <cassert>
#define MAX_N 30

using namespace std;
using pii = pair<int, int>;

struct Coord
{
    int r, c, dir, dist;
};

int N;
int m[MAX_N+1][MAX_N+1];
bool visited[MAX_N+1][MAX_N+1][4];
bool local_visited[MAX_N+1][MAX_N+1];
queue<Coord> q, local_q;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
int ddir[4] = {2, 3, 0, 1};

void init(int mN, int mMap[MAX_N][MAX_N])
{
    N = mN;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = mMap[i][j];
        }
    }
	return;
}

bool isMovable(pii cur, pii nxt, pii stone)
{
    if (nxt.first == stone.first && nxt.second == stone.second)
        return true;

    memset(local_visited, 0, sizeof(local_visited));
    local_q = {};
    local_q.push({cur.first, cur.second, 0, 0});
    local_visited[cur.first][cur.second] = true;
    local_visited[stone.first][stone.second] = true;

    while(!local_q.empty()) {
        auto cur_pos = local_q.front();
        local_q.pop();

        if (cur_pos.r == nxt.first && cur_pos.c == nxt.second) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur_pos.r + dr[i];
            int nc = cur_pos.c + dc[i];
            int ndist = cur_pos.dist + 1;
            
            if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                continue;
            if (m[nr][nc] == 1)
                continue;
            if (local_visited[nr][nc])
                continue;
            
            local_q.push({nr, nc, 0, ndist});
            local_visited[nr][nc] = true;
        }
    }

    return false;
}

int push(int mRockR, int mRockC, int mDir, int mGoalR, int mGoalC)
{
    int ret = -1;
    memset(visited, 0, sizeof(visited));
    q = {};
    q.push({mRockR, mRockC, mDir, 0});

    while(!q.empty()) {
        auto cur = q.front();
        q.pop();

        if (cur.r == mGoalR && cur.c == mGoalC) {
            ret = cur.dist;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            int ndir = ddir[i];
            int ndist = cur.dist + 1;

            int cur_user_r = cur.r + dr[cur.dir];
            int cur_user_c = cur.c + dc[cur.dir];
            int nxt_user_r = cur.r + dr[ndir];
            int nxt_user_c = cur.c + dc[ndir];

            // Out of bound
            if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                continue;
            // Check wall
            if (m[nr][nc] == 1)
                continue;
            // Check visited
            if (visited[nr][nc][ndir])
                continue;
            // Check whether stone is movable
            if (!isMovable({cur_user_r, cur_user_c}, {nxt_user_r, nxt_user_c}, {cur.r, cur.c}))
                continue;
            
            q.push({nr, nc, ndir, ndist});
            visited[nr][nc][ndir] = true;
        }
    }

    assert(ret > 0);

	return ret;
}