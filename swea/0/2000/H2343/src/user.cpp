/**
 *  Algorithm
 *  - 좌표의 정보를 renumbering을 해서 array에 저장
 *  - Hash를 통해 ID indexing을 해서 valid flag를 false로 만듬
 *  - 
 * 
 *  Time complexity
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>

using namespace std;

struct Data
{
    int id, x, y, c, dist;
};

constexpr int MAX = (4000 / 4);
int K, L;
vector<Data> V[MAX + 1][MAX + 1];
unordered_map<int, Data> hmap;

void init(int mK, int mL)
{
    K = mK;
    L = mL;
    hmap.clear();
    for (int i=0; i<(MAX + 1); i++) {
        for (int j=0; j<(MAX + 1); j++) {
            V[i][j].clear();
        }
    }

	return;
}

// Maximum 20,000
void addSample(int mID, int mX, int mY, int mC)
{
    V[mY / L][mX / L].push_back({mID, mX, mY, mC, 0});
    hmap.insert({mID, {mID, mX, mY, mC, 0}});
	return;
}

// Maximum 1,000
void deleteSample(int mID)
{
    auto coord = hmap[mID];
    hmap.erase({mID});
    auto &v = V[coord.y / L][coord.x / L];
    auto it = v.begin();

    for (; it != v.end(); it++) {
        if (it->id == mID) {
            it->c = 0;
        }
    }

	return;
}

int getDist(int sx, int sy, int ex, int ey)
{
    return abs(sx - ex) + abs(sy - ey);
}

bool comp(const Data &lhs, const Data &rhs)
{
    if (lhs.dist != rhs.dist)
        return lhs.dist < rhs.dist;
    else if (lhs.x != rhs.x)
        return lhs.x < rhs.x;
    else
        return lhs.y < rhs.y;
}

// Maximum 10,000
int predict(int mX, int mY)
{
    int ret = -1;
    int g_sx = max(mX / L - 1, 0);
    int g_sy = max(mY / L - 1, 0);
    int g_ex = min(mX / L + 1, 4000 / L);
    int g_ey = min(mY / L + 1, 4000 / L);

    vector<Data> result;
    for (int i=g_sy; i<=g_ey; i++) {
        for (int j=g_sx; j<=g_ex; j++) {
            auto &v = V[i][j];
            int size = v.size();
            for (int k=0; k<size; k++) {
                // If deleted
                if (v[k].c == 0)
                    continue;

                int dist = getDist(v[k].x, v[k].y, mX, mY);
                // If the distance is far
                if (dist > L)
                    continue;

                v[k].dist = dist;
                result.push_back(v[k]);
            }
        }
    }

    if ((int)result.size() < K)
        return ret;

    partial_sort(result.begin(), result.begin() + K, result.end(), comp);

    int cat_cnt[11];
    int num_max_cat = 0;
    memset(cat_cnt, 0, sizeof(cat_cnt));

    for (int i=0; i<K; i++) {
        auto &p = result[i];
        cat_cnt[p.c]++;
        if (cat_cnt[p.c] > num_max_cat) {
            num_max_cat = cat_cnt[p.c];
        }
    }

    for (int i=1; i<=10; i++) {
        if (cat_cnt[i] == num_max_cat) {
            ret = i;
            break;
        }
    }

	return ret;
}
