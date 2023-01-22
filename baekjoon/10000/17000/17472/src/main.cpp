#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#define MAX 10+1
#define MAX_DIST 9999

using namespace std;

/*
 *  Idea
 *
 *  1. Analysis: Get each coordinate of islands and give ID number to it
 *  2. Collect them and put them to vector
 *  3. Make bridge: Get all combinations among different island and sort them to find out shortest path
 *  4. Do MST with union-find algorithm
 */
int N, M;
int origin_map[MAX][MAX];
int map[MAX][MAX];
bool visited[MAX][MAX];
int island_num, bridge_num;
int max_island;
int dist[MAX][MAX];
vector< pair <pair<int, int>, int> > bridge_list;
int min_bsize;
int group_table[MAX];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

vector< pair<int, int> > island_list[MAX];

/*
 *  Get island information
 */
void doDFS(int x, int y)
{
    map[y][x] = island_num;
    island_list[island_num].push_back(make_pair(x, y));

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

/*
 *  This is for debug
 */
void printMap(int _map[][MAX])
{
    printf("################ Map for Debugging #################\n");
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            printf("%d ", _map[i][j]);
        }
        printf("\n");
    }
}

void doBridgeDFS(int x, int y, int dir, int bsize, int s, int d)
{
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (nx < 0 || nx >= M || ny < 0 || ny >= N)
        return;
    
    if (map[ny][nx] == 0)
        doBridgeDFS(nx, ny, dir, bsize+1, s, d);
    else {
        if (map[ny][nx] == d) {
            if (bsize >= 2) {
                if (dist[s][d] > bsize) {
                    dist[s][d] = bsize;
                    dist[d][s] = bsize;
                }
            } else {

            }
        }
    }
}

/*
 *  Traverse area without direction change
 */
void traverseIsland(int s, int d)
{
    for (int i=0; i<island_list[s].size(); i++) {
        int x = island_list[s][i].first;
        int y = island_list[s][i].second;

        for (int j=0; j<4; j++) {
            int nx = x + dx[j];
            int ny = y + dy[j];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                if (map[ny][nx] == 0) {
                    doBridgeDFS(nx, ny, j, 1, s, d);
                }
            }
        }
    }
}

/*
 *  All combination among islands is used to get shortest distance
 */
void getBridge(void)
{
    for (int i=1; i<=max_island; i++) {
        for (int j=i+1; j<=max_island; j++) {
            traverseIsland(i, j);

            if (dist[i][j] == MAX_DIST)
                continue;

            bridge_list.push_back(make_pair(make_pair(i, j), dist[i][j]));
        }
    }
}

void printDist(void)
{
    printf("##################### Distance Information ###################\n");
    for (int i=1; i<=max_island; i++) {
        for (int j=i+1; j<=max_island; j++) {
            printf("[%d]---(%d)---[%d]\n", i, dist[i][j], j);
        }
    }
}

bool cmp(pair<pair<int, int>, int> b1, pair<pair<int, int>, int> b2)
{
    if (b1.second == b2.second)
        return b1.first.first < b2.first.first;
    else
        return b1.second < b2.second;
}

int getParent(int val)
{
    if (val == group_table[val])
        return val;
    else {
        group_table[val] = getParent(group_table[val]);
        return group_table[val];
    }
}

bool isDiffIsland(int src, int dst)
{
    int src_g = getParent(src);
    int dst_g = getParent(dst);

    if (src_g != dst_g)
        return true;
    else
        return false;
}

void unionBridge(int src, int dst)
{
    int src_g = getParent(src);
    int dst_g = getParent(dst);

    if (src_g != dst_g) {
        group_table[src_g] = dst_g;
    }
}

void doMST(void)
{
    for (int i=1; i<=max_island; i++)
        group_table[i] = i;

    sort(bridge_list.begin(), bridge_list.end(), cmp);
    int sel = 0;

    for (int i=0; i<bridge_list.size(); i++) {
        auto bridge = bridge_list[i];
        int src = bridge.first.first;
        int dst = bridge.first.second;

        if (isDiffIsland(src, dst)) {
            sel++;
            min_bsize += bridge.second; 
            bridge_num++;

            unionBridge(src, dst);

            if (sel == max_island + 1)
                return;
        }
    }
}

int main()
{
    cin >> N >> M;

    for (int i=0; i<MAX; i++)
        for (int j=0; j<MAX; j++)
            dist[i][j] = MAX_DIST;

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            cin >> origin_map[i][j];
        }

#ifdef DEBUG
    printMap(origin_map);
#endif

    // Get island information
    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            if (origin_map[i][j] == 1 && !visited[i][j]) {
                visited[i][j] = 1;
                island_num++;
                doDFS(j, i);
            }
        }
    max_island = island_num;

    // Get shortest path
    getBridge();

#ifdef DEBUG
    printMap(map);
    printDist();
#endif

    doMST();

    if (min_bsize == 0 || bridge_num < max_island - 1)
        min_bsize = -1;

    printf("%d\n", min_bsize);

    return 0;
}
