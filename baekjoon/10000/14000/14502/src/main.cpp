#include <iostream>
#include <queue>
#include <vector>
#include <cassert>
#include <cstring>
#define MAX 8
#define MAX_WALL_NUM 3

using namespace std;

int N, M;
int map[MAX][MAX], map_cached[MAX][MAX];
int max_save_area;
bool visited[MAX][MAX];
bool map_tracked[MAX][MAX];
vector<pair<int, int>> list;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void updateMap()
{
    assert(list.size() == MAX_WALL_NUM);

    for (int i=0; i<MAX_WALL_NUM; i++) {
        map_cached[list[i].first][list[i].second] = 1;
    }
}

int doBFS(int row, int col)
{
    int cnt = 0;
    queue<pair<int, int>> q;
    q.push({row, col});
    map_tracked[row][col] = true;

    if (map_cached[row][col] == 0)
        cnt++;

    while(!q.empty()) {
        int x = q.front().second;
        int y = q.front().first;
        q.pop();

        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                if (!map_tracked[ny][nx] && map_cached[ny][nx] == 0) {
                    map_tracked[ny][nx] = true;
                    cnt++;
                    q.push({ny, nx});
                }
            }
        }
    }

    return cnt;
}

int getSaveAreaSize(void)
{
    memset(map_tracked, 0, sizeof(map_tracked));
    int area_size = 0;

    // Generate virus
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            if (!map_tracked[i][j] && map_cached[i][j] == 2) {
                doBFS(i, j);
            }
        }

    // Get save area size
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            if (!map_tracked[i][j] && map_cached[i][j] == 0) {
                area_size += doBFS(i, j);
            }
        }

    return area_size;
}

void getWallComb(int cnt)
{
    if (cnt == MAX_WALL_NUM) {
        memcpy(map_cached, map, sizeof(map));
        updateMap();
        int area = getSaveAreaSize();

        if (area > max_save_area)
            max_save_area = area;

        return;
    }

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            if (visited[i][j] || map[i][j] != 0)
                continue;

            visited[i][j] = true;
            list.push_back({i, j});
            getWallComb(cnt+1);
            list.pop_back();
            visited[i][j] = false;
        }
    }
}

int main()
{
    cin >> N >> M;

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            cin >> map[i][j];
        }

    getWallComb(0);

    cout << max_save_area << "\n";

    return 0;
}
