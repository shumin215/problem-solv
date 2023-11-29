#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int N;
const int MAX = 10000+1;
int init_num[MAX], final_num[MAX];
vector<int> list;
bool done = false;
bool isNextPerm = false;
bool visited[MAX];

void print()
{
    for (int i=0; i<list.size(); i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

void doDFS(int cnt)
{
    // Found answer already
    if (done)
        return;

    if (cnt == N) {
        if (isNextPerm) {
            print();
            done = true;
            return;
        }

        // Have to get next permutation number
        isNextPerm = true;
        return;
    }

    for (int i=1; i<=N; i++) {
        if (visited[i])
            continue;
        // Skip the different number but we have to keep going in case of printing next permutation.
        else if (!isNextPerm && init_num[cnt] != i)
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
        cin >> init_num[i];
    }

    for (int i=0; i<N; i++) {
        final_num[i] = N - i;
    }

    if (memcmp(init_num, final_num, sizeof(init_num)) == 0) {
        printf("-1\n");
        return 0;
    }

    doDFS(0);

    return 0;
}