#include <iostream>
#include <algorithm>
#include <queue>
#include <cassert>
#include <cstring>
#define MAX 15+1
#define ARCHER_NUM 3

using namespace std;

int N, M, D;
bool map[MAX][MAX];
int max_res;

struct TargetInfo
{
    pair<int, int> coord;
    int dist;
};

int getDist(pair<int, int> s, pair<int, int> d)
{
    return abs(s.first - d.first) + abs(s.second - d.second);
}

bool cmp (TargetInfo a, TargetInfo b)
{
    if (a.dist == b.dist)
        return a.coord.first < b.coord.first;
    else
        return a.dist < b.dist;
}

void doBFS(vector<int> &pos)
{
    assert(pos.size() == ARCHER_NUM);
    bool tmp_map[MAX][MAX];
    memcpy(tmp_map, map, sizeof(map));
    int target_cnt = 0;

    // Row update
    for (int i=0; i<N; i++) {
        vector<pair<int, int>> fixed_target_list;

        // Archer change
        for (int j=0; j<ARCHER_NUM; j++) {
            vector<TargetInfo> target_list;

            // Search target from bottom to top
            for (int row=N-1-i; row>=0; row--) {
                // Search target from left to right
                for (int col=0; col<M; col++) {
                    pair<int, int> t_coord = {col, row};
                    pair<int, int> a_coord = {pos[j], N-i};
                    int dist = getDist(t_coord, a_coord);
                    if (tmp_map[row][col] && (dist <= D)) {
                        target_list.push_back({t_coord, dist});
                    }
                }
            }

            if (target_list.size() == 0)
                continue;

            // Sort target list in the distance order
            sort(target_list.begin(), target_list.end(), cmp);
            pair<int, int> target = target_list.front().coord;
            fixed_target_list.push_back(target);
        }
        // Update target to the map
        for (auto &t: fixed_target_list) {
            // We need to consider overlapped target from archers
            if (tmp_map[t.second][t.first]) {
                tmp_map[t.second][t.first] = false;
                target_cnt++;
            }
        }
    }

    max_res = max(max_res, target_cnt);
}

int main()
{
    cin >> N >> M >> D;
    vector<int> archer_pos;

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) {
            char c;
            cin >> c;
            if (c == '1')
                map[i][j] = true;
        }

    for (int i=0; i<M; i++) {
        archer_pos.push_back(i);
        for (int j=i+1; j<M; j++) {
            archer_pos.push_back(j);
            for (int k=j+1; k<M; k++) {
                archer_pos.push_back(k);
                doBFS(archer_pos);
                archer_pos.pop_back();
            }
            archer_pos.pop_back();
        }
        archer_pos.pop_back();
    }
    
    printf("%d\n", max_res);

    return 0;
}
