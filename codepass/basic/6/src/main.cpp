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
        for (int j=0; j<a; j++) {
            arr[a-j][a-i] = cnt;
            cnt++;

            if (cnt == 'Z' + 1)
                cnt -= 26;
        }
    }

    for (int i=1; i<=a; i++) {
        for (int j=1; j<=a; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
