#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

constexpr int MAX = 100000 + 1;
constexpr int SQRT = 317;
vector<int> list;
map<int, int> cnt_list;
map<int, int> freq_list[SQRT];
int N, Q;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

#ifdef _FILE_STDIN
    freopen("input.txt", "r", stdin);
#endif
    cin >> N >> Q;
    // To make 1-base
    list.push_back(0);

    for (int i = 0; i < N; i++) {
        int id;
        cin >> id;
        list.push_back(id);
        
        if (cnt_list.find(id) != cnt_list.end()) {
            cnt_list[id]++;
        } else {
            cnt_list.insert({id, 1});
        }

        if (freq_list[i / SQRT].find(id) != freq_list[i / SQRT].end()) {
            freq_list[i / SQRT][id]++;
        } else {
            freq_list[i / SQRT].insert({id , 1});
        }
    }

    while (Q--) {
        int l, r;
        cin >> l >> r;
        map<int, int> res;
        // id, value
        pair<int, int> max_num = {0, 0};

        // Left
        while (l <= r && l % SQRT != 0) {
            int id = list[l];
            if (res.find(id) != res.end()) {
                res[id]++;
            } else {
                res.insert({id, 1});
            }

            if (res[id] > max_num.second) {
                max_num.first = id;
                max_num.second = res[id];
            }
            l++;
        }

        // Right
        while (l <= r && (r + 1) % SQRT != 0) {
            int id = list[r];
            if (res.find(id) != res.end()) {
                res[id]++;
            } else {
                res.insert({id, 1});
            }

            if (res[id] > max_num.second) {
                max_num.first = id;
                max_num.second = res[id];
            }
            r--;
        }

        // Else
        while (l <= r) {
            for (auto &elem : freq_list[l / SQRT]) {
                int id = elem.first;
                if (res.find(id) != res.end()) {
                    res[id] += elem.second;
                } else {
                    res.insert({id, elem.second});
                }
                if (res[id] > max_num.second) {
                    max_num.first = id;
                    max_num.second = res[id];
                }
            }
            l += SQRT;
        }

        printf("%d\n", max_num.first);
    }

    return 0;
}
