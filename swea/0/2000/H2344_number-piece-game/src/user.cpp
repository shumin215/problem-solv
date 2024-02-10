#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstring>

#define MAX_ROW 40
#define MAX_COL 30

using namespace std;

constexpr int NUM_BLKS = 5;
int (*cell)[MAX_COL];
int R, C;
int base_tn;

struct Cell
{
    int row, col, tn;
};

unordered_map<int, vector<Cell>> hmap[NUM_BLKS];

struct Result{
    int row;
    int col;
};

int dr[5] = {-999, 0, 1, 0, -1};
int dc[5] = {-999, 1, 0, -1, 0};
// 1: right, 2: down
int ddir[NUM_BLKS][5] = { {1}, {1, 1}, {2, 2}, {1, 2, 1}, {2, 1, 1, 2}};
int used[40+1][30+1];

void preprocess(int r, int c, int blk_num)
{
    int idx = 0;
    int code = 0;
    int pre_val = cell[r][c];
    int nr = r, nc = c;
    
    while (ddir[blk_num][idx] > 0) {
        int ndir = ddir[blk_num][idx];
        nr = nr + dr[ndir];
        nc = nc + dc[ndir];
        // Boundary check
        if (nr < 0 || nr >= R || nc < 0 || nc >= C)
            return;
        
        int diff = pre_val - cell[nr][nc] + 4;
        code = (code * 10) + diff;
        pre_val = cell[nr][nc];
        idx++;
    }

    hmap[blk_num][code].push_back({r, c, 0});

    return;
}

void init(int mRows, int mCols, int mCells[MAX_ROW][MAX_COL])
{
    base_tn = 1;
    R = mRows;
    C = mCols;
    cell = mCells;
    // DEBUG: make sure initialization is very important
    memset(used, 0, sizeof(used));

    // DEBUG: make sure initialization is very important
    for (int i = 0; i < NUM_BLKS; i++) {
        hmap[i].clear();
    }

    // Preprocessing to make key-map for each block
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            for (int k = 0; k < NUM_BLKS; k++) {
                preprocess(i, j, k);
            }
        }
    }
}

bool isUsed(Cell c, int blk_num)
{
    bool ret = false;
    int idx = 0;
    int nr = c.row, nc = c.col;
    if (used[c.row][c.col] == base_tn)
        return true;

    while (ddir[blk_num][idx] > 0) {
        int ndir = ddir[blk_num][idx];
        nr = nr + dr[ndir];
        nc = nc + dc[ndir];

        // DEBUG: make sure type is int not bool
        if (used[nr][nc] == base_tn) {
            ret = true;
            break;
        }
        idx++;
    }

    return ret;
}

void mark(Cell c, int blk_num)
{
    used[c.row][c.col] = base_tn;
    int nr = c.row, nc = c.col;
    for (int i = 0; ddir[blk_num][i] > 0; i++) {
        int ndir = ddir[blk_num][i];
        nr = nr + dr[ndir];
        nc = nc + dc[ndir];
        assert(used[nr][nc] != base_tn);
        used[nr][nc] = base_tn;
    }
}

Result putPuzzle(int mPuzzle[3][3])
{
    Result ret = {-1, -1};
    
    // Get block number
    int blk_num = -1;
    if (mPuzzle[2][2] > 0)
        blk_num = 4;
    else if (mPuzzle[1][2] > 0)
        blk_num = 3;
    else if (mPuzzle[2][0] > 0)
        blk_num = 2;
    else if (mPuzzle[0][2] > 0)
        blk_num = 1;
    else if (mPuzzle[0][1] > 0)
        blk_num = 0;
    else
        assert(false);

    // Get code
    int r = 0, c = 0;
    int code = 0;
    int idx = 0;
    int pre_val = mPuzzle[r][c];
    while (ddir[blk_num][idx] > 0) {
        int ndir = ddir[blk_num][idx];
        r = r + dr[ndir];
        c = c + dc[ndir];
        int diff = pre_val - mPuzzle[r][c] + 4;
        code = (code * 10) + diff;
        pre_val = mPuzzle[r][c];
        idx++;
    }

    auto &v = hmap[blk_num][code];
    Cell target_blk;
    bool found = false;
    for (int i = 0; i < (int)v.size(); i++) {
        target_blk = v[i];
        // Check if it is used block
        // if (target_blk.tn == base_tn)
        //     continue;

        // Check if there is used cell
        if (isUsed(target_blk, blk_num))
            continue;
        
        found = true;
        break;
    }

    // Mark used block and cell
    if (found) {
        // target_blk.tn = base_tn;
        mark(target_blk, blk_num);
        ret = {target_blk.row, target_blk.col};
    }

    return ret;
}

void clearPuzzles()
{
    base_tn++;

    return;
}
