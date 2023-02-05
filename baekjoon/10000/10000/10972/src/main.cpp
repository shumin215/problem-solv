#include <iostream>
#include <vector>
#include <cstring>
#define MAX 10001

using namespace std;

int N;
int ans[MAX], finalPerm[MAX];
vector<int> list;
bool isNextPerm, done;
bool visited[MAX];


void print(void)
{
    for (int i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << "\n";
}

void doDFS(int cnt)
{
    if (done)
        return;

    if (cnt == N) {
        if (isNextPerm) {
            print();
            done = true;
            return;
        }

        isNextPerm = true;

        return;
    }

    for (int i=1; i<=N; i++) {
        if (visited[i])
            continue;
        if (!isNextPerm && i != ans[cnt])
            continue;

        visited[i] = true;
        list.push_back(i);
        doDFS(cnt+1);
        list.pop_back();
        visited[i] = false;
    }
}

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        cin >> ans[i];
    }

    for (int i=0; i<=N; i++) {
        finalPerm[i] = N-i;
    }

    if (memcmp(ans, finalPerm, sizeof(ans)) == 0) {
        cout << "-1" << "\n";
        return 0;
    }

    doDFS(0);

    return 0;
}
