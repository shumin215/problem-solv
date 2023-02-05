#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 10001

using namespace std;

int N, M;
vector<int> list, ans_list;
bool visited[MAX];

void print(void)
{
    for (int i=0; i<ans_list.size(); i++) {
        cout << ans_list[i] << " ";
    }
    cout << "\n";
}

void doDFS(int idx, int cnt)
{
    if (cnt == M) {
        print();
        return;
    }

    for (int i=idx; i<list.size(); i++) {
        int num = list[i];
        if (visited[num])
            continue;

        visited[num] = true;
        ans_list.push_back(num);
        doDFS(i, cnt+1);
        ans_list.pop_back();
        visited[num] = false;
    }
}

int main()
{
    cin >> N >> M;

    for (int i=0; i<N; i++) {
        int val;
        cin >> val;
        list.push_back(val);
    }
    sort(list.begin(), list.end());

    doDFS(0, 0);

    return 0;
}
