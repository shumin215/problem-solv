#include <iostream>
#define MAX 21

using namespace std;

int N;
int sub_prob, order;
int ans[MAX];
long long fact[MAX];

void initFact(int val)
{
    for (int i=1; i<val; i++) {
        fact[i] = fact[i-1] * i;
    }
}

void getPerm(int order)
{

}

void getOrder()
{
}

int main()
{
    cin >> N;
    cin >> sub_prob;

    fact[0] = 1;
    initFact(MAX);

    if (sub_prob == 1) {
        cin >> order;

        getPerm(order);
    } else {
        for (int i=0; i<N; i++) {
            cin >> ans[i];
        }

        getOrder();
    }

    return 0;
}



#if 0
#include <iostream>
#include <vector>
#define MAX 21

using namespace std;

int N;
int sub_prob, order, perm_order;
int ans[MAX];
vector<int> list;
bool visited[MAX];

void print(void)
{
    for (int i=0; i<list.size(); i++)
        cout << list[i] << " ";
    cout << "\n";
}

bool samePerm(void)
{
    bool ret = true;
    for (int i=0; i<N; i++) {
        if (list[i] != ans[i]) {
            ret = false;
            break;
        }
    }

    return ret;
}

void doDFS(int cnt)
{
    if (cnt == N) {
        perm_order++;

        if (sub_prob == 1 && perm_order == order) {
            print();
        }

        if (sub_prob == 2 && samePerm()) {
            cout << perm_order << "\n";
        }

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
    cin >> sub_prob;

    if (sub_prob == 1) {
        cin >> order;
    } else {
        for (int i=0; i<N; i++) {
            cin >> ans[i];
        }
    }

    doDFS(0);

    return 0;
}
#endif
