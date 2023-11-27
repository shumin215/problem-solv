#include <iostream>
#include <vector>
#define MAX 7

using namespace std;

int N, M;
vector<int> list;
bool visited[MAX];

void doM1(int cnt)
{
    if (cnt == N) {
        for (int i=0; i<N; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");

        return;
    }

    for (int i=1; i<=6; i++) {
        list.push_back(i);
        doM1(cnt+1);
        list.pop_back();
    }
}

void doM2(int idx, int cnt)
{
    if (cnt == N) {
        for (int i=1; i<=N; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");

        return;
    }

    for (int i=list[idx-1]; i<=6; i++) {
        list.push_back(i);
        doM2(idx+1, cnt+1);
        list.pop_back();
    }
}

void doM3(int cnt)
{
    if (cnt == N) {
        for (int i=0; i<N; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");

        return;
    }

    for (int i=1; i<=6; i++) {
        if (visited[i])
            continue;

        visited[i] = true;
        list.push_back(i);
        doM3(cnt+1);
        list.pop_back();
        visited[i] = false;
    }
}

int main()
{
    cin >> N >> M;

    if (M == 1) {
        doM1(0);
    } else if (M == 2) {
        list.push_back(1);
        doM2(1, 0);
    } else if (M == 3) {
        doM3(0);
    }

    return 0;
}
