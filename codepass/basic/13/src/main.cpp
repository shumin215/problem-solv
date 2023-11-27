#include <iostream>
#define MAX 101

using namespace std;

int arr[MAX][MAX];

int main()
{
    int n;
    int num = 1;
    cin >> n;
    int len = n;
    int x = -1, y = 0;

    while (len > 0) {
        // Right
        for (int i=0; i<len; i++) {
            arr[y][++x] = num++;
        }
        len--;
        // Down
        for (int i=0; i<len; i++) {
            arr[++y][x] = num++;
        }
        // Left
        for (int i=0; i<len; i++) {
            arr[y][--x] = num++;
        }
        len--;
        // Up
        for (int i=0; i<len; i++) {
            arr[--y][x] = num++;
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
