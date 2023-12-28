#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

struct Data
{
    int r, c, cnt;
};

int T, N;
int sr, sc, er, ec;
constexpr int MAX = 300 + 1;
int m[MAX][MAX];
bool visited[MAX][MAX];

int dr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void doBFS(int row, int col)
{
    if (row == er && col == ec) {
        printf("0\n");
        return;
    }
    queue<Data> q;
    q.push({row, col, 0});
    visited[row][col] = true;

    while (!q.empty()) {
        auto cur_pos = q.front();
        q.pop();

        for (int i=0; i<8; i++) {
            int nr = cur_pos.r + dr[i];
            int nc = cur_pos.c + dc[i];
            int n_cnt = cur_pos.cnt + 1;

            if (nr == er && nc == ec) {
                printf("%d\n", n_cnt);
                return;
            }

            if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                continue;
            if (visited[nr][nc])
                continue;
            
            visited[nr][nc] = true;;
            q.push({nr, nc, n_cnt});
        }        
    }
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

//    freopen("input.txt", "r", stdin);
//    string hello_str, world_str;
//    cin >> hello_str >> world_str;
    cin >> T;

    while (T--) {
        N = 0;
        memset(m, 0, sizeof(m));
        memset(visited, 0, sizeof(visited));
        cin >> N;
        cin >> sr >> sc;
        cin >> er >> ec;

        doBFS(sr, sc);
    }

    return 0;
}
