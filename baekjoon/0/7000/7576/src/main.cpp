#include <iostream>
#include <queue>
#define MAX 1001

using namespace std;

int map[MAX][MAX];
bool visited[MAX][MAX];
int N, M;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int max_day = -1;

class Info
{
public:
    Info(int _x, int _y, int _day): x(_x), y(_y), day(_day) {}
    int x, y, day;
};
queue<Info> q;

void doBFS(void)
{
    while(!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int day = q.front().day;
        q.pop();

        if (max_day < day)
            max_day = day;

        for (int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                if (!visited[ny][nx]) {
                    visited[ny][nx] = true;
                    if (map[ny][nx] == 0) {
                        q.push(Info(nx, ny, day+1));
                    }
                }
            }
        }
    }
}

void checkNotVisited(void)
{
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            if (!visited[i][j] && map[i][j] == 0) {
                max_day = -1;
#ifdef DEBUG
                printf("[ERROR] x=%d y=%d\n", j, i);
#endif
                return;
            }
        }
}

int main()
{
    cin >> M >> N;

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin >> map[i][j];
        }
    }

    // Initial value is pushed to queue
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            if (map[i][j] == 1) {
                visited[i][j] = true;
                q.push(Info(j, i, 0));
            }
        }

    doBFS();

    checkNotVisited();

    cout << max_day << endl;

    return 0;
}
