#include <algorithm>
#include <cstring>

using namespace std;
using LL = long long;

constexpr int MAX = 100000+1;
constexpr int TYPE_MAX = 1000+1;
constexpr int SQ = 317;
int N, M;
int type[MAX];
int time[MAX];
int time_sum[SQ + 1];
int typetime[TYPE_MAX];

void init(int mN, int mM, int mType[], int mTime[])
{
    N = mN;
    M = mM;

    memset(time_sum, 0, sizeof(time_sum));

    for (int i = 0; i < N-1; i++) {
        type[i] = mType[i];
        time[i] = mTime[i];
        time_sum[i / SQ] += mTime[i];
    }
}

void destroy()
{

}

// Maximum 10,000
void update(int mID, int mNewTime)
{
    time_sum[mID / SQ] = time_sum[mID / SQ] - time[mID] + mNewTime;
    time[mID] = mNewTime;
}

// Maximum 200
int updateByType(int mTypeID, int mRatio256)
{
    int ret = 0;

    for (int i = 0; i < N - 1; i++) {
        if (type[i] == mTypeID) {
            LL updated_time = ((LL) time[i] * (LL) mRatio256) / 256;
            time_sum[i / SQ] = time_sum[i / SQ] - time[i] + updated_time;
            time[i] = updated_time;
            ret += updated_time;
        }
    }

	return ret;
}

// Maximum 100,000
int calculate(int mA, int mB)
{
    int ret = 0;
    if (mA > mB)
        swap(mA, mB);
    int l = mA, r = mB - 1;
    
    // Left
    while(l <= r && l % SQ != 0) {
        ret += time[l];
        l++;
    }

    // Right
    while(l <= r && (r + 1) % SQ != 0) {
        ret += time[r];
        r--;
    }

    // Else
    while(l <= r) {
        ret += time_sum[l / SQ];
        l += SQ;
    }

	return ret;
}