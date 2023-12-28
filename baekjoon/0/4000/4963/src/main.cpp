#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
using pii = pair<int, int>;

constexpr int MAX = 50 + 1;
int m[MAX][MAX];
int visited[MAX][MAX];
queue<pii> q;
int W, H;
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void doBFS(int row, int col)
{
    visited[row][col] = true;
    q.push({row, col});

    while (!q.empty()) {
        auto top = q.front();
        q.pop();

        for (int i=0; i<8; i++) {
            int nr = top.first + dr[i];
            int nc = top.second + dc[i];

            if (nr < 0 || nr > H || nc < 0 || nc > W)
                continue;
            if (visited[nr][nc])
                continue;
            if (m[nr][nc] == 0)
                continue;

            visited[nr][nc] = true;
            q.push({nr, nc});
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
    while(true) {
        cin >> W >> H;

        if (W == 0 && H == 0) {
            break;
        }

        memset(m, 0, sizeof(m));
        memset(visited, 0, sizeof(visited));
        int num_land = 0;

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> m[i][j];
            }
        }

        for (int i=0; i<H; i++) {
            for (int j=0; j<W; j++) {
                if (!visited[i][j] && m[i][j] == 1) {
                    doBFS(i, j);
                    num_land++;
                }
            }
        }
        printf("%d\n", num_land);
    }

    return 0;
}
