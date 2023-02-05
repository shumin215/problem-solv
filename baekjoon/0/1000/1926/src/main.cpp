#include <iostream>
#define MAX 501

using namespace std;

bool map[MAX][MAX];
bool visited[MAX][MAX];

int N, M;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
int pic_num;
int max_size;
int local_size;

void doDFS(int _x, int _y)
{
    for (int i=0; i<4; i++) {
        int nx = _x + dx[i];
        int ny = _y + dy[i];

        if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
            if (map[ny][nx] && !visited[ny][nx]) {
                visited[ny][nx] = true;
                local_size++;

                doDFS(nx, ny);
            }
        }
    }
}

int main()
{
    cin >> N >> M;

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            int v;
            cin >> v;
            map[i][j] = v;
        }

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            if (map[i][j] && !visited[i][j]) {
                visited[i][j] = true;
                pic_num++;
                local_size = 1;
                doDFS(j, i);
                if (max_size < local_size)
                    max_size = local_size;
            }
        }

    cout << pic_num << endl;
    cout << max_size << endl;

    return 0;
}
