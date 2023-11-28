#include <iostream>

using namespace std;

const int MAX = 10+1;

int N, K;
int dp[MAX][MAX];

int getComb(int n, int r)
{
    if (dp[n][r] > 0)
        return dp[n][r];
    else if (n == r || r == 0)
        return 1;
    else {
        dp[n][r] = getComb(n-1, r-1) + getComb(n-1, r);
        return dp[n][r];
    }
}

int main()
{
    cin >> N >> K;

    printf("%d\n", getComb(N, K));

    return 0;
}
