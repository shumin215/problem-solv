#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 49 + 1;
const int TARGET_NUM = 6;
int T = 2;
vector<int> input_list, comb_list;
bool visited[MAX];
int N;

void print()
{
    for (int i=0; i<comb_list.size(); i++) {
        printf("%d ", comb_list[i]);
    }
    printf("\n");
}

void doDFS(int idx, int cnt)
{
    if (cnt == TARGET_NUM) {
        print();
        return;
    }

    for (int i=idx; i<input_list.size(); i++) {
        int num = input_list[i];
        if (visited[num])
            continue;
        
        visited[num] = true;
        comb_list.push_back(num);
        doDFS(i, cnt+1);
        comb_list.pop_back();
        visited[num] = false;
    }
}

int main()
{
    while (true) {
        cin >> N;

        if (N == 0)
            return 0;

        input_list.clear();
        memset(visited, 0, sizeof(visited));

        for (int i=0; i<N; i++) {
            int num;
            cin >> num;
            input_list.push_back(num);
        }

        doDFS(0, 0);
        printf("\n");
    }

    return 0;
}
