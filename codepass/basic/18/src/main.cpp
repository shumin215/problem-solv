#include <iostream>
#include <cmath>
#include <algorithm>
#define MAX 256

using namespace std;

int N;

int main()
{
    int sq; 
    int arr[10000], cnt=0;
    cin >> N;
    sq = (int)sqrt(N);
    for (int i = 1; i <= sq; i++)
    {
        if (N % i == 0)
        {
            arr[cnt++] = i;
            if (N / i != i)
                arr[cnt++] = N / i;
        }
    }

    sort(arr, arr+cnt);

    for (int i=0; i<cnt; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
