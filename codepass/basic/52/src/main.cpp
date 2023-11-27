#include <iostream>
#include <vector>
#define MAX 7

using namespace std;

int N, M;
vector<int> list;

void doDFS(int sum, int cnt)
{
    if (cnt == N) {
        if (sum == M) {
            for (int i=0; i<N; i++) {
                printf("%d ", list[i]);
            }
            printf("\n");
        }

        return;
    }

    for (int i=1; i<=6; i++) {
        list.push_back(i);
        doDFS(sum + i, cnt + 1);
        list.pop_back();
    }
}

int main()
{
    cin >> N >> M;

    doDFS(0, 0);

    return 0;
}
