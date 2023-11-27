#include <iostream>
#define MAX 101

using namespace std;

char arr[MAX][MAX];

int main()
{
    int a;
    char cnt = 'A';
    cin >> a;

    if (a == 0 || a % 2 == 0 || a > 100) {
        printf("INPUT ERROR\n");
        return 0;
    }

    int key_num = a / 2 + 1;
    int ii = 1;

    for (int i=0; i<key_num; i++) {
        for (int j=0; j<ii; j++) {
            arr[key_num - 1 - i + j][key_num - 1 - i] = cnt;
            cnt++;

            if (cnt == 'Z' + 1)
                cnt -= 26;
        }
        ii += 2;
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
