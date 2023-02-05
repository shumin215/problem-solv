#include <iostream>
#include <vector>
#define MAX 51

using namespace std;

int N;
vector<pair<int, int>> info_list;
int res[MAX];

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        int w, h;
        cin >> w >> h;
        info_list.push_back({w, h});
    }

    for (int i=0; i<N; i++)
        res[i] = 1;

    for (int i=0; i<N; i++) {
        int cur_weight = info_list[i].first;
        int cur_height = info_list[i].second;

        for (int j=0; j<N; j++) {
            if (i == j)
                continue;

            if (cur_weight < info_list[j].first && cur_height < info_list[j].second)
                res[i]++;
        }
    }

    for (int i=0; i<N; i++) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
