/*
 *  This is implemented using DFS
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX (25+1)

using namespace std;

/*
 *  1. Idea
 *  - 2-level for using DFS
 *
 *  2. Data structure
 *  - Graph: graph 
 *  - Check visited: visited
 *  - Result: result
 */

bool graph[MAX][MAX];
bool visited[MAX][MAX];
vector<int> result;

int N;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int cnt;

void doDFS(int x, int y)
{
    cnt++;

    for (int i=0; i<4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N)
            if (graph[ny][nx] && !visited[ny][nx]) {
                visited[ny][nx] = true;
                doDFS(nx, ny);
            }
    }
}

int main()
{
    scanf("%d", &N);
    
    // Initialize graph
    for (int i=0; i<N; i++) {
        string str;
        cin >> str;

        for (int j=0; j<N; j++) {
            if (str[j] == '1') {
                graph[i][j] = true;
            }
        }
    }

    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++) {
            if (graph[i][j] == true && visited[i][j] == false) {
                cnt = 0;
                visited[i][j] = true;
                doDFS(j, i);
                result.push_back(cnt);
            }
        }

    sort(result.begin(), result.end());

    printf("%d\n", (int)result.size());
    for (auto i=0; i<result.size(); i++)
        printf("%d\n", result[i]);

    return 0;
}

/*
 *  This is implemented using BFS
 */
#if 0
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX (25 + 1)

using namespace std;

/*
 *  1. Idea
 *  - Initialize graph
 *  - Traverse graph sequentially and if not visited is detected, do DFS or BFS
 *  - Counter is increased when new node is touched, and then eventually counter is reset when new node is faced
 *
 *  2. Data structure
 *  - Graph         : graph with 2-level
 *  - Check visit   : bool 2-level demention
 *  - Result        : int vector
 */

bool graph[MAX][MAX];
bool visited[MAX][MAX];
vector<int> result;

class Coord
{
public:
    Coord(int _x, int _y): x(_x), y(_y) { }

    int x;
    int y;
};

int cnt;
queue<Coord> q;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
int N;

void doBFS(int x, int y)
{
    q.push(Coord(x, y));
    cnt++;

    while(!q.empty()) {
        Coord coord = q.front();
        q.pop();

        // Local traverse
        for (int i=0; i<4; i++) {
            int nx = coord.x + dx[i];
            int ny = coord.y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N)
                if (graph[ny][nx] && !visited[ny][nx]) {
                    q.push(Coord(nx, ny));
                    visited[ny][nx] = true;
                    cnt++;
                }
        }
    }

}

int main()
{
    scanf("%d", &N);

    // Initialize graph
    for (int i=0; i<N; i++) {
        string str;
        cin >> str;

        for (int j=0; j<N; j++) {
            if (str[j] == '1') {
                graph[i][j] = true;
            }
        }
    }

    // Global traverse
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++) {
            if (graph[i][j] && !visited[i][j]) {
                cnt = 0;
                visited[i][j] = true;
                doBFS(j, i);
                result.push_back(cnt);
            }
        }

    sort(result.begin(), result.end());

    printf("%d\n", (int)result.size());

    for (auto i=0; i<(int)result.size(); i++)
        printf("%d\n", result[i]);
    return 0;
}
#endif
