#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

constexpr int MAX = 3000 + 1;

using pii = pair<int, int>;

struct Hole
{
    int r, c;
    bool valid;
    int round;

    int operator-(const Hole &rhs) const {
        // Same row
        if (r == rhs.r)
            return abs(c - rhs.c) * 10;
        // Same col
        else if (c == rhs.c)
            return abs(r - rhs.r) * 10;
        // Diag
        else
            return abs(r - rhs.r) * 14;
    }
};

// <upper, bottom>
pii r_diag_info[MAX * 2], l_diag_info[MAX * 2];
vector<int> rows[MAX];
vector<int> cols[MAX];
vector<int> r_diag[MAX * 2], l_diag[MAX * 2];
vector<int> r_diag_eff[MAX * 2], l_diag_eff[MAX * 2];
Hole holes[MAX];
int hid;
int N;

void init(int mN)
{
    hid = 0;
    N = mN;
    memset(r_diag_info, 0, sizeof(r_diag_info));
    memset(l_diag_info, 0, sizeof(l_diag_info));
    for (int i = 1; i <= N; i++) {
        rows[i].clear();
        cols[i].clear();
    }
    for (int i = 0; i <= N * N; i++) {
        r_diag[i].clear();
        l_diag[i].clear();
        r_diag_eff[i].clear();
        l_diag_eff[i].clear();
    }
}

/**
 * Maximum 3,000 
 * 
 */
void addDiagonal(int mARow, int mACol, int mBRow, int mBCol)
{
    if (mARow > mBRow) {
        swap(mARow, mBRow);
        swap(mACol, mBCol);
    }

    bool is_r_diag = (mACol > mBCol) ? true : false;
    int r_idx = mARow + mACol;
    int l_idx = N - mARow + mACol;

    // Diag 정보 업데이트
    if (is_r_diag) {
        r_diag_info[r_idx] = {mARow, mBRow};
    } else {
        l_diag_info[l_idx] = {mARow, mBRow};
    }

    // 기존 hole 중 해당되는게 있는지 확인 후 추가
    for (int r = mARow; r <= mBRow; r++) {
        
    }
}

/**
 * Maximum 30,000 
 * 
 */
void addHole(int mRow, int mCol, int mID)
{
}

/**
 * Maximum 3,000 
 * 
 */
void eraseHole(int mRow, int mCol)
{
}

/**
 * Maximum 10,000 
 * 
 */
int hitMarble(int mRow, int mCol, int mK)
{
	return 0;
}
