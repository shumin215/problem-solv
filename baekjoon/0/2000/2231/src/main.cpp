#include <iostream>

using namespace std;

int N;
int ans;

int getRemainder(int _val)
{
    int ret = 0;
    if ((_val / 10) == 0) {
        return _val;
    }

    ret = getRemainder(_val / 10) + (_val % 10);
    return ret;
}

void doBF(void)
{
    for (int i=1; i<=N; i++) {
        int remainder = getRemainder(i);
        int sum = i + remainder;

        if (sum == N) {
            ans = i;
            return;
        }
    }
}

int main()
{
    cin >> N;

    doBF();

    cout << ans << endl;

    return 0;
}
