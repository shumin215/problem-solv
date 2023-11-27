#include <iostream>
#define MAX 101

using namespace std;

int arr[MAX][MAX];

int main()
{
    int n;
    int cnt = 1;
    cin >> n;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            arr[j][i] = cnt;
            cnt++;
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
