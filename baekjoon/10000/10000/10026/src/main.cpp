#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 100+1;

char graph[MAX][MAX];
bool visited[MAX][MAX];
int N;
int num_color = 0;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void doDFS(int y, int x)
{
    visited[y][x] = true;

    for (int i=0; i<4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (graph[y][x] == graph[ny][nx] && !visited[ny][nx]) {
            doDFS(ny, nx);
        }
    }
}

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> graph[i][j];
        }
    }

    // This is for non-red-green eye person
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (!visited[i][j]) {
                doDFS(i, j);
                num_color++;
            }
        }
    }
    printf("%d\n", num_color);

    num_color = 0;
    memset(visited, 0, sizeof(visited));

    // This is for red-green eye person
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++) {
            if (graph[i][j] == 'R')
                graph[i][j] = 'G';
        }
    
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (!visited[i][j]) {
                doDFS(i, j);
                num_color++;
            }
        }
    }
    printf("%d\n", num_color);

    return 0;
}
