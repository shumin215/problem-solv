#include <iostream>
#include <vector>
#define MAX 9

using namespace std;

int N, M;
vector<int> list;

void print()
{
    for (int i=0; i<list.size(); i++)
        cout << list[i] << " ";
    cout << "\n";
}

void doDFS(int cnt)
{
    if (cnt == M) {
        print();
        return;
    }

    for (int i=1; i<=N; i++) {
        list.push_back(i);
        doDFS(cnt+1);
        list.pop_back();
    }
}

int main()
{
    cin >> N >> M;

    doDFS(0);

    return 0;
}
