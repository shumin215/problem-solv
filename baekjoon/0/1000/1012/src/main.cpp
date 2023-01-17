#include <iostream>
#include <vector>
#include <cstring>

#define MAX 50+1

using namespace std;

bool graph[MAX][MAX];
bool visited[MAX][MAX];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
vector<int> result;

void doDFS(int x, int y, int max_x, int max_y)
{
    for (int i=0; i<4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < max_x && ny >= 0 && ny < max_y) {
            if (graph[ny][nx] && !visited[ny][nx]) {
                visited[ny][nx] = true;
                doDFS(nx, ny, max_x, max_y);
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;

    for (int i=0; i<T; i++) {
        int M, N, K;
        cin >> M >> N >> K;
        int j_num = 0;

        // Initialize
        memset(graph, 0, sizeof(graph));
        memset(visited, 0, sizeof(visited));

        for (int i=0; i<K; i++) {
            int x, y;
            cin >> x >> y;
            graph[y][x] = true;
        }

        for (int i=0; i<N; i++)
            for (int j=0; j<M; j++) {
                if (graph[i][j] && !visited[i][j]) {
                    j_num++;
                    visited[i][j] = true;
#ifdef DEBUG
                    printf("[DEBUG] X=%d Y=%d\n", j, i);
#endif
                    doDFS(j, i, M, N);
                } 
            }
        result.push_back(j_num);
    }

    for (int i=0; i<T; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}

