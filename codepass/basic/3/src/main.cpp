#include <iostream>

using namespace std;

int main()
{
    int a, b;
    int cnt = 1;
    cin >> a >> b;

    for (int i=0; i<a; i++) {
        for (int j=0; j<b; j++) {
            printf("%d ", cnt);
            cnt++;
        }
        printf("\n");
    }

    return 0;
}
