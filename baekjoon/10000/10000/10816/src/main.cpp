#include <iostream>
#include <vector>
#include <map>

using namespace std;

int N, M;
map<int, int> m;
vector<int> list;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;

    for (int i=0; i<N; i++) {
        int num;
        cin >> num;
        if (m.find(num) == m.end()) {
            m.insert({num, 1});
        } else {
            m[num]++;
        }
    }

    cin >> M;

    for (int i=0; i<M; i++) {
        int num;
        cin >> num;
        list.push_back(num);
    }

    for (int i=0; i<list.size(); i++) {
        printf("%d ", m[list[i]]);
    }

    return 0;
}
