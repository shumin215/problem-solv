#include <iostream>
#define MAX 101

using namespace std;

char arr[MAX][MAX];

int main()
{
    int a;
    char cnt = 'A';
    cin >> a;

    for (int i=0; i<a; i++) {
        for (int j=0; j<(a-i); j++) {
            arr[j+i][a-j-1] = cnt;
            cnt++;

            if (cnt == 'Z' + 1)
                cnt -= 26;
        }
    }

    for (int i=0; i<a; i++) {
        for (int j=0; j<a; j++) {
            if (arr[i][j] >= 'A' && arr[i][j] <= 'Z')
                printf("%c ", arr[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }

    return 0;
}
