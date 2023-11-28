#include <iostream>

using namespace std;

const int MAX = 30+1;
int T;
int dp[MAX][MAX];

/**
 * We can resolve this problem using combination formula.
 * We can the number of bridges that can be implemented by using combination.
 * 
 * Assume that there are 5 people and we have to select 3 people.
 * We can calculate the number of combination like 5C3.
 * There are a formula, nCr = n-1 C r-1 + n-1 C r.
 *                      5C3 = 4C2 + 4C3
 * 1. In case of selecting one person in advance.
 *  We do just select two people since we already selected one person.
 *  In that case, the formula should be 4C2.
 * 
 * 2. In case of not selecting one person in advance.
 *  We have to select 3 people among 4 people.
 * In that case, the formula should be 4C3.
 * 
 * Eventually, the number of combination will be 4C2 + 4C3.
*/
int getComb(int n, int r)
{
    // There already exist result.
    if (dp[n][r] > 0)
        return dp[n][r];
    // If the number of elements is same with combination to be selected, or the combination value is 0,
    // it will return 1.
    else if (n == r || r == 0)
        return 1;
    // The other common cases
    else {
        dp[n][r] = getComb(n-1, r-1) + getComb(n-1, r);
        return dp[n][r];
    }
}

int main()
{
    cin >> T;

    for (int i=0; i<T; i++) {
        int N, M;
        cin >> N >> M;

        printf("%d\n", getComb(M, N));
    }
    return 0;
}