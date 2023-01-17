#include <iostream>

#define MAX 16+1

using namespace std;

int N;
bool map[MAX][MAX];
int cnt;

bool canMove(int h_x, int h_y, int t_x, int t_y)
{
    bool ret = true;

    // Horizontal
    if (h_y == t_y) {
        if (h_x + 1 >= N)
            ret = false;
        if (map[h_y][h_x+1])
            ret = false;
    }
    // Vertical
    if (h_x == t_x) {
        if (h_y + 1 >= N)
            ret = false;
        if (map[h_y+1][h_x])
            ret = false;
    }

    return ret;
}

void doDFS(int h_x, int h_y, int t_x, int t_y)
{
#ifdef DEBUG
    printf("[DEBUG] H (%d, %d) - T (%d, %d)\n", h_x, h_y, t_x, t_y);
#endif
    // 1. Exit condition
    // 1) Reach destination
    // 2) Can't move pipe no more
    if ((h_x == N-1) && (h_y == N-1)) {
        cnt++;
        return;
    } else if (!canMove(h_x, h_y, t_x, t_y)) {
        return;
    }
    // 2. In case of horizontal
    if (h_y == t_y) {
        // Move right
        doDFS(h_x+1, h_y, t_x+1, t_y);
        // Move diagonal
        if (!map[h_y+1][h_x] && !map[h_y+1][h_x+1])
            doDFS(h_x+1, h_y+1, t_x+1, t_y);
    }
    // 3. In case of vertical
    else if (h_x == t_x) {
        // Move down
        doDFS(h_x, h_y+1, t_x, t_y+1);
        // Move diagonal
        if (!map[h_y][h_x+1] && !map[h_y+1][h_x+1])
            doDFS(h_x+1, h_y+1, t_x, t_y+1);
    }
    // 4. In case of diagonal
    else {
        // Move right
        if (h_x+1 < N && !map[h_y][h_x+1])
            doDFS(h_x+1, h_y, t_x+1, t_y+1);
        // Move down
        if (h_y+1 < N && !map[h_y+1][h_x])
            doDFS(h_x, h_y+1, t_x+1, t_y+1);
        // Move diagonal
        if (h_x+1 < N && h_y+1 < N)
            if (!map[h_y][h_x+1] &&
                !map[h_y+1][h_x] &&
                !map[h_y+1][h_x+1])
                doDFS(h_x+1, h_y+1, t_x+1, t_y+1);
    }
}

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            char c;
            cin >> c;
            if (c == '1') {
                map[i][j] = true;
            }
        }
    }

    doDFS(1, 0, 0, 0);

    printf("%d\n", cnt);

    return 0;
}
