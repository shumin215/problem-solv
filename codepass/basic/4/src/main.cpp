#include <iostream>

using namespace std;

int main()
{
    int a, b;
    int cnt = 1;
    cin >> a >> b;

    for (int i=0; i<a; i++) {
        if (i % 2 == 0) {
            for (int j=0; j<b; j++) {
                printf("%d ", cnt);
                cnt++;
            }
        } else {
            for (int j=0; j<b; j++) {
                if (j == 0) {
                    cnt += (b - 1);
                }
                printf("%d ", cnt);
                cnt--;
                if (j == b - 1) {
                    cnt += b + 1;
                }
            }
        }

        printf("\n");
    }

    return 0;
}
