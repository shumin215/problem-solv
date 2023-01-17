#include <iostream>
#include <climits>
#define MAX 10+1

using namespace std;

/*
 *  Idea
 *
 *  1. Analysis: Get each coordinate of islands and give ID number to it
 *  2. Collect them and put them to vector
 *  3. Make bridge: Get all combinations among different island and sort them to find out shortest path
 *  4. Do MST?
 */
int N, M;
int origin_map[MAX][MAX];
int map[MAX][MAX];
bool visited[MAX][MAX];
int min_bridge_num = INT_MAX;
int island_num;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

class IslandInfo
{
public:
    IslandInfo(int _x1, int _x2, int _y1, int _y2, int _id):
        x1(_x1), x2(_x2), y1(_y1), y2(_y2), id(_id) {}
    int x1, x2, y1, y2;
    int id;
};

/*
 *  Get island information
 */
void doDFS(int x, int y)
{
    map[y][x] = island_num;

    for (int i=0; i<4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
            if (origin_map[ny][nx] != 0 && !visited[ny][nx]) {
                visited[ny][nx] = true;
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
            cin >> origin_map[i][j];
        }

    // Get island information
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            if (origin_map[i][j] == 1 && !visited[i][j]) {
                visited[i][j] = 1;
                island_num++;
                doDFS(j, i);
            }
        }

    printf("%d\n", min_bridge_num);

    return 0;
}
