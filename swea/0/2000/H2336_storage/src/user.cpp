#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;

constexpr int MAX = 100000+1;
constexpr int SQRT = 320;
int global_max_idx;
int N;
int arr[MAX];
int max_idx_arr[SQRT + 1];

void init(int mN)
{
    global_max_idx = 0;
    N = mN;
    for (int i = 0; i <= N; i++)
        arr[i] = 0;
    // DEBUG: Block마다 초기 값은 block 내부의 index 값으로 해야함
    for (int i = 0; i <= N; i+= SQRT) {
        max_idx_arr[i / SQRT] = i;
    }

	return;
}

void update(int idx, int box)
{
    arr[idx] += box;

    int bidx = idx / SQRT;
    int l = bidx * SQRT;
    // DEBUG: 업데이트 boundary를 현재 사용하고자 하는 N 범위까지만 해야함
    int r = min(l + SQRT - 1, N);
    // Current block
    for (int i = l; i <= r; i++) {
        if (arr[max_idx_arr[bidx]] < arr[i]) {
            max_idx_arr[bidx] = i;
        }
    }

    // All blocks
    for (int i = 0; i <= (N / SQRT); i++) {
        int max_idx = max_idx_arr[i];
        if (arr[global_max_idx] < arr[max_idx]) {
            global_max_idx = max_idx;
        }
    }
    return;
}

int getMaxIdx(int l, int r)
{
    if (l == r)
        return l;
    else if (l > r)
        assert(false);
    
    int max_num = 0;
    int max_idx = 0;
    // Left side
    while (l <= r && l % SQRT != 0) {
        if (max_num < arr[l]) {
            max_num = arr[l];
            max_idx = l;
        }
        l++;
    }

    // Right side
    while (l <= r && (r + 1) % SQRT != 0) {
        if (max_num < arr[r]) {
            max_num = arr[r];
            max_idx = r;
        }
        r--;
    }

    // Else
    while (l <= r) {
        int blk_max_idx = max_idx_arr[l / SQRT];
        if (max_num < arr[blk_max_idx]) {
            max_num = arr[blk_max_idx];
            max_idx = blk_max_idx;
        }
        l += SQRT;
    }

    // assert(max_idx != 0 && max_num != 0);
    return max_idx;
}

int stock(int mLoc, int mBox)
{
    // Update box info
    update(mLoc, mBox);

    // Max position
    int ret = arr[global_max_idx];

    // Left side
    int l = 1, r = global_max_idx - 1;
    while (l <= r) {
        int max_idx = getMaxIdx(l, r);
        if (max_idx == 0)
            break;
        ret += arr[max_idx] * (r - max_idx + 1);
        r = max_idx - 1;
    }

    // Right side
    l = min(global_max_idx + 1, N + 1), r = N;
    while (l <= r) {
        int max_idx = getMaxIdx(l, r);
        if (max_idx == 0)
            break;
        ret += arr[max_idx] * (max_idx - l + 1);
        l = max_idx + 1;
    }

	return ret;
}

int ship(int mLoc, int mBox)
{
	return stock(mLoc, -mBox);
}

int getHeight(int mLoc)
{
	return arr[mLoc];
}
