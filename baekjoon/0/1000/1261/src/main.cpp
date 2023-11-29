#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> Pos; // {y, x}
const int INF = 9999999;
const int MAX = 100+1;
int N, M;
// Priority queue, pair<Distance, Position>
priority_queue< pair<int, Pos>, vector<pair<int, Pos>>, greater<pair<int, Pos>> > pq;
// Distance map
int dist_map[MAX][MAX];
int map[MAX][MAX];
// Unit direction
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void doDijkstra(int y, int x)
{
    pq.push({0, {y, x}});
    dist_map[y][x] = 0;

    while(!pq.empty()) {
        auto cur_pos = pq.top().second;
        pq.pop();

        for (int i=0; i<4; i++) {
            int nx = cur_pos.second + dx[i];
            int ny = cur_pos.first + dy[i];

            if (nx >= 1 && nx <= M && ny >= 1 && ny <= N) {
                int dist = 0;
                if (map[ny][nx] == 0) {
                    dist = 0;
                } else {
                    dist = 1;
                }

                if (dist_map[ny][nx] > dist_map[cur_pos.first][cur_pos.second] + dist) {
                    dist_map[ny][nx] = dist_map[cur_pos.first][cur_pos.second] + dist;

                    pq.push({dist_map[ny][nx], {ny, nx}});
                }
            }
        }
    }
}

int main()
{
    cin >> M >> N;

    for (int i=1; i<=N; i++) {
        for (int j=1; j<=M; j++) {
            scanf("%1d", &map[i][j]);
            dist_map[i][j] = INF;
        }
    }

    doDijkstra(1, 1);

    printf("%d\n", dist_map[N][M]);

    return 0;
}
