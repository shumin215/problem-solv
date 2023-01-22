#include <iostream>
#include <queue>
#define MAX 100+1

using namespace std;

int N, M;
queue<pair<int, int>> q;
char map[MAX][MAX];
bool visited[MAX][MAX];
int step[MAX][MAX];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void doBFS(void)
{
    q.push(make_pair(0, 0));
    visited[0][0] = true;
    step[0][0] = 1;

    while(!q.empty()) {
        pair<int, int> start = q.front();
        q.pop();

        int x = start.first;
        int y = start.second;

        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                if (map[ny][nx] != '0' && !visited[ny][nx]) {
                    step[ny][nx] = step[y][x] + 1;
                    visited[ny][nx] = true;

                    if (ny == N-1 && nx == M-1)
                        return;

                    q.push(make_pair(nx, ny));
                }
            }
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

    doBFS();

    printf("%d\n", step[N-1][M-1]);

    return 0;
}
