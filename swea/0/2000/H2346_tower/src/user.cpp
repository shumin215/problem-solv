
/**
 * @brief 감시탑
 * 
 * Algorithm
 * 
 * Time complexity
 * 
 */
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;
using pii = pair<int, int>;

constexpr int NUM_COLORS = 5 + 1;
constexpr int MAX = 5000 + 1;
int N;

struct Tower
{
    int row, col, color;
    bool valid;
};

vector<int> towers[NUM_COLORS][MAX];
int num_towers[NUM_COLORS];

// Max number of towers per single color -> 11,000
void init(int mN)
{
    N = mN;
    memset(num_towers, 0, sizeof(num_towers));
    for (int i=0; i<NUM_COLORS; i++) {
        for (int j=0; j<=N; j++) {
            towers[i][j].clear();
        }
    }
}

// Maximum 50,000 
void buildTower(int mRow, int mCol, int mColor)
{
    towers[mColor][mRow].push_back(mCol);
    towers[0][mRow].push_back(mCol);
    num_towers[mColor]++;
    num_towers[0]++;
}

// Maximum 1,000
void removeTower(int mRow, int mCol)
{
    for (int i=0; i<NUM_COLORS; i++) {
        auto &v = towers[i][mRow];
        auto it = find(v.begin(), v.end(), mCol);
        if (it != v.end()) {
            v.erase(it);
            num_towers[i]--;
        }
    }

    return;
}

// Maximum 10,000
int countTower(int mRow, int mCol, int mColor, int mDis)
{
    int tcnt = 0;
    int sr = max(mRow - mDis, 1);
    int sc = max(mCol - mDis, 1);
    int er = min(mRow + mDis, N);
    int ec = min(mCol + mDis, N);

    for (int i=sr; i<=er; i++) {
        auto &v = towers[mColor][i];
        for (int j=0; j<(int)v.size(); j++) {
            if (sc <= v[j] && v[j] <= ec) {
                tcnt++;
            }
        }
        // NOTE: find 함수는 시간을 많이 잡아먹는다.
        // for (int j=sc; j<=ec; j++) {
            
        //     auto it = find(v.begin(), v.end(), j);
        //     if (it != v.end()) {
        //         tcnt++;
        //     }
        // }
    }

	return tcnt;
}

int getDist(int sr, int sc, int er, int ec)
{
    return abs(sr - er) + abs(sc - ec);
}

// Maximum 5,000
int getClosest(int mRow, int mCol, int mColor)
{
    int ret = -1;
    int min_dist = INT_MAX;

    if (num_towers[mColor] == 0)
        return ret;

    // Upper
    for (int i=0; i<mRow; i++) {
        if (i >= min_dist)
            break;

        int r = mRow - i;
        auto &v = towers[mColor][r];
        int size = v.size();
        for (int j=0; j<size; j++) {
            int c = v[j];
            int dist = getDist(r, c, mRow, mCol);
            if (min_dist > dist) {
                min_dist = dist;
            }
        }
    }

    // Bottom
    for (int r=mRow+1; r<=N; r++) {
        if ((r - mRow) >= min_dist)
            break;

        auto &v = towers[mColor][r];
        int size = v.size();
        for (int j=0; j<size; j++) {
            int c = v[j];
            int dist = getDist(r, c, mRow, mCol);
            if (min_dist > dist) {
                min_dist = dist;
            }
        }
    }

    ret = min_dist;

	return ret;
}