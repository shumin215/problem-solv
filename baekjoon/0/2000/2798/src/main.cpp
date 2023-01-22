#include <iostream>
#include <stack>

#define MAX 100+1
#define MAX_CARD_NUM 3

using namespace std;

int N, M;
int num[MAX];
bool visited[MAX];
int res = 0;

void getSum(int _cnt, int _sum)
{
    if (_sum > M)
        return;

    if (_cnt == MAX_CARD_NUM) {
        if (_sum > M)
            return;
        else {
            if (res < _sum) {
                res = _sum;
            }

            return;
        }
    }

    for (int i=0; i<N; i++) {
        if (!visited[i]) {
            visited[i] = true;
            getSum(_cnt+1, _sum+num[i]);
            visited[i] = false;
        }
    }
}

int main()
{
    cin >> N >> M;

    for (int i=0; i<N; i++) {
        cin >> num[i];
    }

    getSum(0, 0);

    cout << res << endl;

    return 0;
}
