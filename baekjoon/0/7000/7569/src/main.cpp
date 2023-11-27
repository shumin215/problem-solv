#include <iostream>
#include <queue>
#define MAX 101

using namespace std;

class Coord
{
public:
    Coord(int _z, int _y, int _x, int _d): z(_z), y(_y), x(_x), d(_d) {}
    int z, y, x, d;
};

int M, N, H;
int map[MAX][MAX][MAX];
bool visited[MAX][MAX][MAX];
int day, tomato_cnt, seed_cnt;
queue<Coord> q;

int dx[6] = {1, 0, -1, 0, 0, 0};
int dy[6] = {0, 1, 0, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

void doBFS()
{
    while(!q.empty()) {
        Coord coord = q.front();
        q.pop();

        for (int i=0; i<6; i++) {
            int nx = coord.x + dx[i];
            int ny = coord.y + dy[i];
            int nz = coord.z + dz[i];
            int nd = coord.d + 1;

            if (nx >= 0 && nx < M && ny >= 0 && ny < N && nz >= 0 && nz < H)
                if (map[nz][ny][nx] == 0 && !visited[nz][ny][nx]) {
                    tomato_cnt++;
                    visited[nz][ny][nx] = true;
                    q.push({nz, ny, nx, nd});

                    if (nd > day)
                        day = nd;
                }
        }

        if (tomato_cnt == seed_cnt) {
            return;
        }
    }
}

int main()
{
    cin >> M >> N >> H;

    for (int i=0; i<H; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<M; k++) {
                int val;
                cin >> val;
                map[i][j][k] = val;

                if (val == 0)
                    seed_cnt++;
            }
        }
    }

    for (int i=0; i<H; i++) {
        for (int j=0; j<N; j++) {
            for (int k=0; k<M; k++) {
                if (!visited[i][j][k] && map[i][j][k] == 1) {
                    visited[i][j][k] = true;
                    q.push({i, j, k, 0});
                }
            }
        }
    }

    doBFS();

    if (tomato_cnt != seed_cnt)
        cout << "-1\n";
    else
        cout << day << "\n";

    return 0;
}
