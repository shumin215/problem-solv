#include <iostream>
#include <vector>
#define MAX 9

using namespace std;

int N;
vector<int> list;
bool visited[MAX];

void print(void)
{
    for (auto i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << "\n";
}

void doDFS(int cnt)
{
    if (cnt == N) {
        print();
        return;
    }
    for (int i=1; i<=N; i++) {
        if (visited[i])
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

    doDFS(0);

    return 0;
}
