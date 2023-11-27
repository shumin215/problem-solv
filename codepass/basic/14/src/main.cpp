#include <iostream>
#define MAX 101

using namespace std;

int arr[MAX][MAX];

int main()
{
    int n;
    int num = 0;
    cin >> n;
    int len = n;
    int x = -1, y = -1;

    while (len > 0) {
        // Right and down
        for (int i=0; i<len; i++) {
            arr[++y][++x] = num++;
        }
        len--;
        // Left
        for (int i=0; i<len; i++) {
            arr[y][--x] = num++;
        }
        len--;
        // Up
        for (int i=0; i<len; i++) {
            arr[--y][x] = num++;
        }
        len--;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<i+1; j++) {
            printf("%d ", arr[i][j] % 10);
        }
        printf("\n");
    }

    return 0;
}
